#include "Trip.h"
#include "Point2D.h"

using namespace std;

Trip::Trip(int id, Point* source, Point* destination, int numOfPassengers, double tariff) {
    this->id = id;
    this->startPoint = source;
    this->endPoint = destination;
    this->tariff = tariff;
    this->numOfPassengers = numOfPassengers;
}
Trip::Trip(int currentId, Point* source, Point* destination, double tariff,
           vector <Passenger*> currentPassengers) {
    this->id = currentId;
    this->startPoint = source;
    this->endPoint = destination;
    this->tariff = tariff;
    this->currentPassengers = currentPassengers;
    this->numOfPassengers = currentPassengers.size();
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