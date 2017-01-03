#include "Driver.h"

using namespace std;

Driver::Driver() {
    this->numOfPassengers =0;
    this->satisfactionAvg =0;
    this->totalScore = 0;
}
Driver::Driver(int id, int age, Marital status, int yearsOfExperience, int cabId) {
    this->id = id;
    this->age = age;
    this->status = status;
    this->yearsOfExperience = yearsOfExperience;
    this->numOfPassengers =0;
    this->satisfactionAvg =0;
    this->totalScore = 0;
    this->cabId = cabId;
    this->isAvailable = true;
}
double Driver::evaluateSatisfaction() {
    return this->totalScore / this->numOfPassengers;
}
void Driver::getScoreFromCurrentPassenger(){
    this->totalScore += this->getTrip().passengersSendScore();
}
void Driver::setNewTrip(Trip newTrip){
    this->currentTrip = newTrip;
    this->numOfPassengers += newTrip.getNumOfPassengers();
}
double Driver::calculateTripCost() {
    return (this->taxiCab->getTariff() * this->currentTrip.getTripCost());
}
Trip Driver::getTrip() {
    return this->currentTrip;
}
CabFactory* Driver::getCab() {
    return this->taxiCab;
}
void  Driver::setCab(CabFactory* taxiCab) {
    this->taxiCab = taxiCab;
}
double Driver::getTotalScore() {
    return this->totalScore;
}
double Driver::getNumOfPassengers() {
    return this->numOfPassengers;
}
NodePoint* Driver::getLocationInGrid() {
    return this->location;
}
void Driver::setLocation(NodePoint* newLocation) {
    this->location = newLocation;
}
int Driver::getId() {
    return this->id;
}
int Driver::getCabId() {
    return this->cabId;
}
bool Driver::setIsAvailable(bool flag) {
    this->isAvailable = flag;
}
bool Driver::getIsAvailable() {
    return this->isAvailable;
}

void Driver::moveOneStep(int time){
    int pathIndex = time - (this->getTrip().getClockTimeTrip());
    int cabType = this->getCab()->getSpeed();
    int tripSize = this->getTrip().getPath().size();
    if (cabType == 1) {
        this->setLocation(this->getTrip().getPath()[pathIndex]);
        //if (cabType == 2) is luxuryCab
    } else {
        //if we arrive to the end point
        if (pathIndex * 2 >= tripSize -1)
            this->setLocation(this->getTrip().getPath()[tripSize - 1]);
            //if we are still on ride
        else
            this->setLocation(this->getTrip().getPath()[pathIndex * 2]);
    }
    //maybe send GO to client
    if (this->getLocationInGrid()->getPoint()->equals
            (this->getTrip().getPath()[tripSize - 1]->getPoint())) {
        this->setIsAvailable(true);
    }
}
