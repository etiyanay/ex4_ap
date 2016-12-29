#ifndef AP_EX1_DRIVER_H
#define AP_EX1_DRIVER_H

#include <iostream>
#include <vector>
#include "CabFactory.h"
#include "Passenger.h"
#include "Trip.h"
#include "Grid.h"

using namespace std;
enum Marital {SINGLE = 'S',MARRIED = 'M',DIVORCED = 'D',WIDOWED = 'W'};
/**
 * this is the class of the Driver, in charge of creating the a driver, manage his location,
 * setting his map/ trip and etc..
 */
class Driver {
private:
    int id, age, yearsOfExperience, cabId;
    double satisfactionAvg, totalScore, numOfPassengers;
    Marital status;
    CabFactory* taxiCab;
    //will be given by trip
    Trip currentTrip;
    NodePoint* location;
    Grid* map;
public:
    /**
     * default constructor
     * @return driver
     */
    Driver();
    /**
     * constructor
     * @return new driver
     */
    Driver(int id, int age, Marital status, int yearsOfExperience,int cabId);
    /**
     * dtor
     */
    ~Driver(){};
    /**
     * @return the avg satisfaction that the passengers give
     */
    double evaluateSatisfaction();
    /**
     * ask the passenger to send you satisfaction score
     */
    void getScoreFromCurrentPassenger();
    /**
     * @param newTrip the trip that the driver will have
     */
    void setNewTrip(Trip newTrip);
    /**
     * @return the total cost of the ride
     */
    double calculateTripCost();
    /**
     * @return the trip path of the driver
     */
    Trip getTrip();
    /**
     * @param taxiCab is the cab to attach the driver
     */
    void setCab(CabFactory* taxiCab);
    /**
     * @return the cab that is attached to the driver
     */
    CabFactory* getCab();
    /**
     * @return the sum of all the satisfactions that have been sent
     */
    double getTotalScore();
    /**
     * @return the counter of all the passengeres that have drives with the driver
     */
    double getNumOfPassengers();
    /**
     * @return the specific location point of the driver on the grid
     */
    NodePoint* getLocationInGrid();
    /**
     * @param newLocation is the new current location of the driver
     */
    void setLocation(NodePoint* newLocation);
    /**
     * @return id number of the driver
     */
    int getId();
    /**
     * @param map is the map of the grid to set in the driver
     */
    void setMap(Grid* map);
    int getCabId();
};

#endif //AP_EX1_DRIVER_H