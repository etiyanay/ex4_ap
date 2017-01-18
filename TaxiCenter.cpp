#include "TaxiCenter.h"

using namespace std;
vector <pthread_t> tripsThreads;


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
Driver TaxiCenter::findClosestDriver(Point* sourcePoint) {
    //default id
}
void TaxiCenter::addNewDriver(Driver newDriver, int index) {
    CabFactory* matchingCab = this->findCabById(newDriver.getCabId());
    newDriver.setCab(matchingCab);
    newDriver.setLocation(dim->getPtrGrid()[0]);
    this->drivers[index] = newDriver;
    this->availableToReceiveData[index] = true;
}
void TaxiCenter::addNewCab(CabFactory* newCab){
    this->cabs.push_back(newCab);
}
void TaxiCenter::getCall(Point* sourcePoint, Point* destination){
    /*
     * Trip newTrip = Trip(id, sourcePoint, destination, tariff);
    this->findClosestDriver(sourcePoint).setNewTrip(newTrip);
     */
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
}
void TaxiCenter::addNewTrip(Trip newTrip){
    //pthread_mutex_lock(&list);

    this->trips.push_back(newTrip);
    TripData *data = new TripData();
    int size = this->trips.size();
    data->trip = &(this->trips[size-1]);
    data->bfs = this->currentBfs;
    //data->mutex = this->calculatePath;
    //resize
    tripsThreads.resize(tripsThreads.size() + 1);
    this->threadFlagIfJoin.push_back(false);
    //create new thread that runs the calculatePath func
    pthread_create(&(tripsThreads[tripsThreads.size()-1]), NULL, Bfs::calculatePath,(void*)data);
    //pthread_mutex_unlock(&list);
    //cout << "num of threads: " << tripsThreads.size() <<endl;
    for (int i = 0; i < tripsThreads.size(); ++i) {
        if (threadFlagIfJoin[i] == false) {
            pthread_join(tripsThreads[i], NULL);
            threadFlagIfJoin[i] = true;
            //cout << "last print"<<endl;

        }
    }

    //initializing the grid with no visited nodes- as in the beginning



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
    int i, indexOfRelevantTrip = -1;
        for(i = 0; i < this->getNumOfTrips(); i++) {
            //check if the trip starts where the driver is
            if ((this->drivers[currentDriverIndex].getLocationInGrid()->getPoint()->equals
                    (trips[i].getPath()[0]->getPoint())) &&
                    ((this->trips[i].getClockTimeTrip() == this->timeIs()))) {
                indexOfRelevantTrip = i;
                break;
            }
    }
    //if we did find a correct trip - assign it
    if (indexOfRelevantTrip != -1) {
        //serializing
        this->trips[indexOfRelevantTrip].setStartPoint();
        this->trips[indexOfRelevantTrip].setEndPoint();
        Trip *newTrip;
        newTrip = &this->trips[indexOfRelevantTrip];
        string serial_trip;
        boost::iostreams::back_insert_device<std::string> inserter(serial_trip);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newTrip;
        s.flush();
        //attach the trip to the driver
        cout << "driver: "<<currentDriverIndex << " get trip: "<<trips[indexOfRelevantTrip].getId()<<endl;
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
void TaxiCenter::moveAllDriversOneStep(Socket* tcp, int index) {
        char buffer[8096];
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

void TaxiCenter::sendCloseToClients(Socket *tcp) {
    int sizeOfClients = this->clientsSd.size();
    for (int i = 0; i < sizeOfClients; ++i) {
        tcp->sendData("close", this->clientsSd[i]);
    }
}
void TaxiCenter::setNewClientSd(int newClientSd) {
    this->clientsSd.push_back(newClientSd);
}
void TaxiCenter::resizeDriversVec(int numOfDrivers) {
    this->drivers.resize(this->drivers.size() + numOfDrivers);
    this->availableToReceiveData.resize(this->availableToReceiveData.size() + numOfDrivers);
}
void TaxiCenter::pushObstacleToMap(NodePoint* obstacleNodePoint){
    this->dim->pushObstacleToVec(obstacleNodePoint);
}