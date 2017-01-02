#include "TaxiCenter.h"

using namespace std;

TaxiCenter::TaxiCenter(Grid* dim, Bfs* currentBfs){
    this->dim = dim;
    this->currentBfs = currentBfs;
    this->time = Clock(0);
    this->firstTripFlag = false;
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
    newDriver.setClock(this->time);
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
        drivers[i].advanceClockOfDriver();
    }
}

void TaxiCenter::assignTripToDriver(int currentDriverIndex) {
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
        //attach the trip to the driver
        this->drivers[currentDriverIndex].setNewTrip(trips[indexOfRelevantTrip]);
        //delete the trip that has been set to the driver
        this->trips.erase(this->trips.begin() + indexOfRelevantTrip);
        this->drivers[currentDriverIndex].setIsAvailable(false);
    }
}
void TaxiCenter::moveAllDriversOneStep() {
    int i;
    int numOfDrivers = this->getNumOfDrivers();
    for (i = 0; i < numOfDrivers; i++) {
        if (this->drivers[i].getIsAvailable() == false) {
            drivers[i].moveOneStep();
        } else {
                this->assignTripToDriver(i);
        }
    }   /*לולאת פור על כל הנהגים, לכל נהג נבדוק:
    האם הממבר 'זמין' שלו שווה לאפס(כלומר זמין):
     אם זמין נזמן ASSIGNTRIPTODRIVER ונשלח בפונק את הנהג של איטרציה זו
     ובנוסף שולח לקליינט בסוקט את הTRIP של הנהג
אם הממבר 'זמין' שלו שווה לאחד (כלומר לא זמין):
     נקדם את הנהג בצעד (BFS ב*זמן נוכחי פחות זמן ההתחלה של הטריפ*)
     אם הגענן לסוף הטריפ נעדכן את 'זמין' להיות אפס
     ובנוסף שולח בסוקט את המיקום החדש של הנהג
גם בקליינט אם הגענו לסוף הטריפ נעדכן את 'זמין' להיות אפס
     */
        //לבדוק שזה הזמן להתחיל לזוז
     //זמין בדרייבר
    //הוספת ממבר של זמן התחלה לכל טריפ
//-1 in fictive constructor of trip
    //contructor of driver (the first)
}