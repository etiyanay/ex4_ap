#include "TaxiCenter.h"

using namespace std;

TaxiCenter::TaxiCenter(Grid* dim, Bfs* currentBfs){
    this->dim = dim;
    this->currentBfs = currentBfs;
    this->time = Clock(0);
    this->firstTripFlag = false;
    this->availableToReceiveData = true;
}
TaxiCenter::~TaxiCenter() {
    delete this->dim;
    for (int i = 0; i < this->cabs.size(); ++i) {
        delete this->cabs[i];
    }
}
Driver TaxiCenter::findClosestDriver(Point* sourcePoint) {
    //default id
}
void TaxiCenter::addNewDriver(Driver newDriver) {
    CabFactory* matchingCab = this->findCabById(newDriver.getCabId());
    newDriver.setCab(matchingCab);
    //newDriver.setMap(this->dim);
    newDriver.setLocation(dim->getPtrGrid()[0]);
    this->drivers.push_back(newDriver);
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
void TaxiCenter::assignTripsToDrivers() {
    int i,j;
    int numOfDrivers = getNumOfDrivers();
    for(i = 0; i < numOfDrivers; i++) {
        for(j = 0; j < getNumOfTrips(); j++) {
            //check if the trip starts where the driver is
            if (drivers[i].getLocationInGrid()->getPoint()->equals
                    (trips[j].getPath()[0]->getPoint())) {
                //attach the trip to the driver
                this->drivers[i].setNewTrip(trips[j]);
                //delete the trip that has been set to the driver
                this->trips.erase(this->trips.begin() + j);
                //step to the next driver
                break;
            }
        }
    }
}
void TaxiCenter::addNewTrip(Trip newTrip){
    vector <NodePoint*> path = this->currentBfs->runBfs(newTrip.getStartPoint(),
                                                        newTrip.getEndPoint());
    newTrip.setPath(path);
    //initializing the grid with no visited nodes- as in the beginning
    this->dim->initializeGrid();
    this->trips.push_back(newTrip);
}
void TaxiCenter::startDriving() {
    int i;
    int numOfDrivers = this->getNumOfDrivers();
    int sizeOfPath;
    for (i = 0; i < numOfDrivers; i++) {
        sizeOfPath = this->drivers[i].getTrip().getPath().size();
        this->drivers[i].setLocation(this->drivers[i].getTrip().getPath()[sizeOfPath - 1]);
    }
}
int TaxiCenter::timeIs() {
    return this->time.timeIs();
}

void TaxiCenter::advanceTime() {
    this->time.advanceTime();
    for(int i=0; i< this->drivers.size(); i++){
        //drivers[i].advanceClockOfDriver();
    }
}

void TaxiCenter::setReceiveDataFlag(bool flag) {
    this->availableToReceiveData = flag;
}
bool TaxiCenter::getReceiveDataFlag(){
    return this->availableToReceiveData;
}

void TaxiCenter::assignTripToDriver(int currentDriverIndex, Socket* udp) {
    int i, indexOfRelevantTrip = -1;
        for(i = 0; i < this->getNumOfTrips(); i++) {
            //check if the trip starts where the driver is
            if ((this->drivers[currentDriverIndex].getLocationInGrid()->getPoint()->equals
                    (trips[i].getPath()[0]->getPoint())) &&
                    ((this->trips[i].getClockTimeTrip() == this->timeIs()))) {
                indexOfRelevantTrip = i;
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
        this->drivers[currentDriverIndex].setNewTrip(trips[indexOfRelevantTrip]);
        //delete the trip that has been set to the driver
        this->trips.erase(this->trips.begin() + indexOfRelevantTrip);
        this->drivers[currentDriverIndex].setIsAvailable(false);
        //sending the serialized cab to client
        udp->sendData(serial_trip);
        this->setReceiveDataFlag(true);
    }
}
void TaxiCenter::moveAllDriversOneStep(Socket* udp) {
    int i;
    int numOfDrivers = this->getNumOfDrivers();
    for (i = 0; i < numOfDrivers; i++) {
        char buffer[1024];
        if (this->getReceiveDataFlag()) {
            //receiveData- want trip/want go
            udp->reciveData(buffer, sizeof(buffer));
            this->setReceiveDataFlag(false);
        }
        if (this->drivers[i].getIsAvailable() == false) {
            drivers[i].moveOneStep(this->timeIs());

            //serializing and sending new location of driver - to client
            NodePoint *newLocation = this->drivers[i].getLocationInGrid();
            string serial_driverNewLocation;
            boost::iostreams::back_insert_device<std::string> inserter(serial_driverNewLocation);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << newLocation;
            s.flush();
            udp->sendData(serial_driverNewLocation);
            this->setReceiveDataFlag(true);

        } else {
                this->assignTripToDriver(i, udp);
        }
    }
}