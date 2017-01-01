#include "TaxiCenter.h"

using namespace std;

TaxiCenter::TaxiCenter(Grid* dim, Bfs* currentBfs){
    this->dim = dim;
    this->currentBfs = currentBfs;
    this->clock = 0;
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
    return this->clock;
}

void TaxiCenter::advenceTime() {
    this->clock = this->clock + 1;
}

void TaxiCenter::assignTripToDriver(Driver currentDriver) {
    /*
     * פונקציה שצריכה לעבור על כל הטריפס ובמידה והטריפ מתאים לשמור את האינדקס שלו

     * נמשיך בלולאה ואם נמצא עוד טריפ שמתחיל באותה נקודה אך מתחיל בזמן מוקדם יותר
     * change isAvailable to false
     * delete trip from trips in taxiCenter
     */
}
void TaxiCenter::MoveOneStep() {
    int i;
    int theXstep = 0;
    int numOfDrivers = this->getNumOfDrivers();
    for (i = 0; i < numOfDrivers; i++) {
        if (this->drivers[i].getIsAvailable() == false) {
            if (this->drivers[i].getTrip().getClockTimeTrip() >= this->timeIs()) {
                //move logic to driver
                if (drivers[i].getCab()->getSpeed() == 1) {
                    theXstep = this->timeIs() - (this->drivers[i].getTrip().getClockTimeTrip());
                    this->drivers[i].setLocation(this->drivers[i].getTrip().getPath()[theXstep]);
//ובנוסף שולח בסוקט את המיקום החדש של הנהג
                } else if (drivers[i].getCab()->getSpeed() == 2) {
                    /********************************************************/
                    /*can be theXstep*2 but not always move 2 steps*/
                }
                if (this->drivers[i].getTrip().getPath().size() - 1 == theXstep) {
                    //delete the trip from **driver** and from trip list?
                    //not good in set new trip if we have some drivers and some of them didnt funush their path
                    //i think if we deleting in up 'if'- we doesnt need to do nothing anymore here
                    this->drivers[i].setIsAvailable();
                }
            }
        } else {
            this->assignTripToDriver(this->drivers[i]);
//     ובנוסף שולח לקליינט בסוקט את הTRIP של הנהג
        }
    }
    /*לולאת פור על כל הנהגים, לכל נהג נבדוק:
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