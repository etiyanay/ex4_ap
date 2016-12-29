#ifndef AP_EX1_TAXICENTER_H
#define AP_EX1_TAXICENTER_H

#include <iostream>
#include "Driver.h"
#include "Grid.h"
#include "Bfs.h"

using namespace std;
/**
 * this is the class of the taxi center that manages all the calls and send taxis for passengers
 */
class TaxiCenter {
private:
    vector <Driver> drivers;
    vector <CabFactory*> cabs;
    vector <Trip> trips;
    Bfs* currentBfs;
    Grid* dim;
public:
    /**
     * default constructor
     * @return a new taxi center
     */
    TaxiCenter(){};
    /**
     * @param dim the map
     * @param currentBfs the current BFS
     * @return a new taxi center
     */
    TaxiCenter(Grid* dim, Bfs* currentBfs);
    /**
     * dtor
     */
    ~TaxiCenter();
    /**
     * @param sourcePoint the source point of a passenger
     * @return the closest driver to the passenger
     */
    Driver findClosestDriver(Point* sourcePoint);
    /**
     * the func adds a driver to the drivers in the taxi center.
     * for each driver- set the map from the taxi center
     * @param newDriver is the new driver to add to the taxi center
     */
    void addNewDriver(Driver newDriver);
    /**
     * @param newCab is the new cab to add to the taxi center
     */
    void addNewCab(CabFactory* newCab);
    /**
     * getting from prosseced input- start and end points for creating the trip
     * @param sourcePoint is the start point
     * @param destination is the destination of the passenger
     */
    void getCall(Point* sourcePoint, Point* destination);
    /**
     * @return the num of drivers in the taxi center
     */
    int getNumOfDrivers();
    /**
     * @return the num of the cabs in the taxi center
     */
    int getNumOfCabs();
    /**
     * @param id the id of the cab we want to find
     * @return the cab that has this id
     */
    CabFactory* findCabById(int id);
    /**
     * @param id the id of the driver that we want to find his location
     * @return the pointer to his location (x,y)
     */
    Point* findDriverLocationById(int id);
    /**
     * @param newTrip is the new trip to add to the taxi center
     */
    void addNewTrip(Trip newTrip);
    /**
     * the func make the drivers "drive" to their end points
     */
    void startDriving();
    /**
     * the func assigning the trips (by the order we get them) to the drivers
     */
    void assignTripsToDrivers();
    /**
     * @return the num of trips in the taxi center
     */
    int getNumOfTrips();
    };

#endif //AP_EX1_TAXICENTER_H