#include "Trip.h"

using namespace std;

Trip::Trip(int id, Point* source, Point* destination, int numOfPassengers,
           double tariff, int clockTimeTrip) {
    this->id = id;
    this->startPoint = source;
    this->endPoint = destination;
    this->tariff = tariff;
    this->numOfPassengers = numOfPassengers;
    this->clockTimeTrip = clockTimeTrip;
}
Trip::Trip(int currentId, Point* source, Point* destination, double tariff,
           vector <Passenger*> currentPassengers) {
    this->id = currentId;
    this->startPoint = source;
    this->endPoint = destination;
    this->tariff = tariff;
    this->currentPassengers = currentPassengers;
    this->numOfPassengers = currentPassengers.size();
    this->clockTimeTrip = -1;
}
double Trip::getTripCost(){
    return this->tariff;
}
Point* Trip::getStartPoint() {
    return this->startPoint;
}
Point* Trip::getEndPoint() {
    return this->endPoint;
}
int Trip::getId() {
    return this->id;
}
void Trip::setPath(vector <NodePoint*> newPath) {
    this->path = newPath;
}
void Trip::setStartPoint() {
    this->startPoint = this->getPath()[0]->getPoint();
}
void Trip::setEndPoint() {
    this->endPoint = this->getPath()[this->getPath().size()-1]->getPoint();
}
vector <NodePoint*> Trip::getPath() {
    return this->path;
}
int Trip::getNumOfPassengers() {
    return this->numOfPassengers;
}
int Trip::passengersSendScore() {
    int totalScore = 0;
    for (int i = 0; i < this->numOfPassengers; i++) {
        totalScore += this->currentPassengers[i]->sendRandomScore();
    }
    return totalScore;
}
int Trip::getClockTimeTrip() {
    return this->clockTimeTrip;
}
void Trip::deleteTripInClient() {
    //deleting the nodepoints in the path
    int sizeOfTrip = path.size();
    for (int i = 0; i < sizeOfTrip; ++i) {
        delete path[i];
    }
}