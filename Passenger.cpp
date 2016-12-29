#include "Passenger.h"
#include <iostream>

using namespace std;

Passenger::Passenger(Point* sourcePoint, Point* destinationPoint) {
    this->source = sourcePoint;
    this->destination = destinationPoint;
};
int Passenger::sendRandomScore() {
    //operate random func to get a satisfaction score num between 1-5
    return 1;
};
Point* Passenger::getSourcePoint() {
    return source;
}
Point* Passenger:: getDestinationPoint() {
    return destination;
}
