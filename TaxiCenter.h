#ifndef AP_EX1_TAXICENTER_H
#define AP_EX1_TAXICENTER_H

#include <iostream>
#include "Driver.h"
#include "Grid.h"
#include "Bfs.h"
#include "Socket.h"

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
    Clock time;
    vector <bool> availableToReceiveData;
    vector <int> clientsSd;
    pthread_mutex_t assignTripMutex;
    vector <bool> threadFlagIfJoin;

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
     * @return the num of trips in the taxi center
     */
    int getNumOfTrips();
    /**
     * advance the taxi clock time in 1
     */
    void advanceTime();
    /**
     * @return the time of the taxi center
     */
    int timeIs();
    /**
     * @param currentDriverIndex the index of the driver we are going to assign a trip to him
     * @param udp the socket to send the trip to client through
     */
    void assignTripToDriver(int currentDriverIndex, Socket* udp);
    /**
     * @param udp the socket to send the trip/new location to client through
     */
    void moveDriverOneStep(Socket* udp, int index);
    /**
     * the func change the flag to true if the taxi center has to process a new recieving data
     * @param flag the new condition of the taxi center
     */
    void setReceiveDataFlag(bool flag,int driverIndex);
    /**
     * @return true if the taxi center is busy to get applies, else return false
     */
    bool getReceiveDataFlag(int driverIndex);
    /**
     * the func gets new client socket descriptor and save it in the sd vec
     * @param newClientSd that we got in accept func of "hand shake"
     */
    void setNewClientSd(int newClientSd);
    /**
     * the func get a nodePoint obstacle- and set that node as "visited"
     * @param obstacleNodePoint
     */
    void pushObstacleToMap(NodePoint* obstacleNodePoint);
    /**
     *
     * @param indexOfDriver index of driver
     * @return the socket descriptor of the driver
     */
    int getNewClientSd(int indexOfDriver);
    /**
     *
     * @param currentDriverIndex the current driver to check if has a trip to assign
     * @param lastDriverIndex the last index that we gave him the trip, instead of taking it
     * @return trip's index we are giving up on
     */
    int tripsPriority(int currentDriverIndex, int lastDriverIndex);
};
/**
 * the struct that contains the info we are sending to the threads that calculate the trips paths
 */
struct TripData
{
    Trip *trip;
    Bfs *bfs;
};

#endif //AP_EX1_TAXICENTER_H