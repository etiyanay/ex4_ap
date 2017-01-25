#include "TaxiCenter.h"
#include "ThreadPool.h"

using namespace std;

TaxiCenter::TaxiCenter(Grid* dim, Bfs* currentBfs){
    this->dim = dim;
    this->currentBfs = currentBfs;
    this->time = Clock(0);
    pthread_mutex_init(&assignTripMutex,0);
}
TaxiCenter::~TaxiCenter() {
    pthread_mutex_destroy(&assignTripMutex);
    delete this->dim;
    for (int i = 0; i < this->cabs.size(); ++i) {
        delete this->cabs[i];
    }
}
void TaxiCenter::addNewDriver(Driver newDriver) {
    CabFactory* matchingCab = this->findCabById(newDriver.getCabId());
    newDriver.setCab(matchingCab);
    newDriver.setLocation(dim->getPtrGrid()[0]);
    this->drivers.push_back(newDriver);
    //setting available flag of driver i as available.
    this->availableToReceiveData.push_back(true);
}
void TaxiCenter::addNewCab(CabFactory* newCab){
    this->cabs.push_back(newCab);
}
int TaxiCenter::getNumOfDrivers() {
    return this->drivers.size();
}
int TaxiCenter::getNumOfCabs() {
    return this->cabs.size();
}
int TaxiCenter::getNumOfTrips() {
    return this->trips.size();
}
CabFactory* TaxiCenter::findCabById(int id) {
    int numOfCabs = this->getNumOfCabs();
    for (int i = 0; i < numOfCabs; i++) {
        if (this->cabs[i]->getID() == id)
            return this->cabs[i];
    }
}
Point* TaxiCenter::findDriverLocationById(int id) {
    int numOfDrivers = this->getNumOfDrivers();
    for (int i = 0; i < numOfDrivers; i++) {
        if (this->drivers[i].getId() == id)
            return this->drivers[i].getLocationInGrid()->getPoint();
    }
    return NULL;
}
void TaxiCenter::addNewTrip(Trip newTrip, ThreadPool *pool) {
    this->trips.push_back(newTrip);
    TripData *data = new TripData();
    int size = this->trips.size();
    data->trip = &(this->trips[size - 1]);
    data->bfs = this->currentBfs;
    //create new thread that runs the calculatePath func
    Job* job = new Job(Bfs::calculatePath, (void*) data);
    pool->addJob(job);
    //waiting for threads to finish calculating and setting the new trip
    for (int i = 0; i < this->trips.size(); ++i) {
        while (!this->trips[i].getPathInit()) {
            sleep(1);
        }
    }
    int numOfDeletedTrips = 0;
    int tripsSize = this->trips.size();
    for (int i = 0; i < tripsSize; ++i) {
        if (NULL == this->trips[i-numOfDeletedTrips].getPath()[0]) {
            this->trips.erase(this->trips.begin() + i-numOfDeletedTrips);
            numOfDeletedTrips++;
        }
    }
}
int TaxiCenter::timeIs() {
    return this->time.timeIs();
}
void TaxiCenter::advanceTime() {
    this->time.advanceTime();
}
void TaxiCenter::setReceiveDataFlag(bool flag, int driverIndex) {
    this->availableToReceiveData[driverIndex] = flag;
}
bool TaxiCenter::getReceiveDataFlag(int driverIndex){
    return this->availableToReceiveData[driverIndex];
}
void TaxiCenter::assignTripToDriver(int currentDriverIndex, Socket* tcp) {
    pthread_mutex_lock(&assignTripMutex);
    int flagPriority = -1;
    int i, indexOfRelevantTrip = -1;
    for(i = 0; i < this->getNumOfTrips(); i++) {
        //check if the trip starts where the driver is
        if ((this->drivers[currentDriverIndex].getLocationInGrid()->getPoint()->equals
                (trips[i].getPath()[0]->getPoint())) &&
            ((this->trips[i].getClockTimeTrip() == this->timeIs()))) {
            flagPriority = this->tripsPriority(currentDriverIndex, flagPriority);
            if (flagPriority == -2) {
                indexOfRelevantTrip = i;
                break;
            }
        }
    }
    //if we did find a correct trip - assign it
    if (indexOfRelevantTrip != -1) {
        //serializing
        this->trips[indexOfRelevantTrip].setStartPoint();
        this->trips[indexOfRelevantTrip].setEndPoint();
        Trip newTrip = this->trips[indexOfRelevantTrip];
        int newTripSize = newTrip.getPath().size();
        string serial_trip;
        boost::iostreams::back_insert_device<std::string> inserter(serial_trip);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newTripSize;
        s.flush();
        //attach the trip to the driver
        this->drivers[currentDriverIndex].setNewTrip(trips[indexOfRelevantTrip]);
        //delete the trip that has been set to the driver
        this->trips.erase(this->trips.begin() + indexOfRelevantTrip);
        this->drivers[currentDriverIndex].setIsAvailable(false);
        //sending the serialized cab to client
        tcp->sendData(serial_trip, this->clientsSd[currentDriverIndex]);
        this->setReceiveDataFlag(true, currentDriverIndex);
    }
    pthread_mutex_unlock(&assignTripMutex);
}
void TaxiCenter::moveDriverOneStep(Socket* tcp, int index) {
    char buffer[2048];
    if (this->getReceiveDataFlag(index)) {
        //receiveData- we get "want trip" or "want go"
        tcp->reciveData(buffer, sizeof(buffer), this->clientsSd[index]);
        this->setReceiveDataFlag(false,index);
    }
    if (this->drivers[index].getIsAvailable() == false) {
        drivers[index].moveOneStep(this->timeIs());
        //serializing and sending new location of driver - to client
        NodePoint *newLocation = this->drivers[index].getLocationInGrid();
        string serial_driverNewLocation;
        boost::iostreams::back_insert_device<std::string> inserter(serial_driverNewLocation);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newLocation;
        s.flush();
        tcp->sendData(serial_driverNewLocation, this->clientsSd[index]);
        this->setReceiveDataFlag(true,index);
    } else {
        //if driver isn't on ride - check if it's time to assign him a trip
        this->assignTripToDriver(index, tcp);
    }
}
void TaxiCenter::setNewClientSd(int newClientSd) {
    this->clientsSd.push_back(newClientSd);
}
void TaxiCenter::pushObstacleToMap(NodePoint* obstacleNodePoint){
    this->dim->pushObstacleToVec(obstacleNodePoint);
}
int TaxiCenter::getNewClientSd(int indexOfDriver) {
    return this->clientsSd[indexOfDriver];
}
int TaxiCenter::tripsPriority(int currentDriverIndex, int lastDriverIndex) {
    Point* currentLocation = this->drivers[currentDriverIndex].getLocationInGrid()->getPoint();
    for (int i = lastDriverIndex + 1; i < currentDriverIndex; ++i) {
        if ((this->drivers[i].getLocationInGrid()->getPoint()->equals(currentLocation)) &&
            (this->drivers[i].getIsAvailable()))
            return i;
    }
    return -2;
}
Point* TaxiCenter::getMapSize() {
    return this->dim->getGridSize();
}