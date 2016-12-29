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
void Driver::setMap(Grid* map) {
    this->map = map;
}
int Driver::getCabId() {
    return this->cabId;
}