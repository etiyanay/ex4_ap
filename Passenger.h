#ifndef AP_EX1_PASSENGER_H
#define AP_EX1_PASSENGER_H

#include "Point.h"
#include <iostream>

/**
 * this class is in charge of the passengers that exist in the trips
 */
class Passenger {
private:
    Point *source, *destination;
public:
    Passenger(){};
    /**
    * constructor
    * @param source
    * @param destination
    * @return
    */
    Passenger(Point* sourcePoint, Point* destinationPoint);
    /**
     * dtor
     */
    ~Passenger(){};
    /**
     * @return the source point of the pass
     */
    Point* getSourcePoint();
    /**
     * @return the destination point of the pass
     */
    Point* getDestinationPoint();
    /**
     * @return num between 1-5 of the satisfaction from the driver
     */
    int sendRandomScore();
};

#endif //AP_EX1_PASSENGER_H