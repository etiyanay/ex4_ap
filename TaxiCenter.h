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
    bool firstTripFlag;
    vector <bool> availableToReceiveData;
    vector <int> clientsSd;
    pthread_mutex_t calculatePath;
    int numOfMutex;

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
    void moveAllDriversOneStep(Socket* udp);
    /**
     * the func change the flag to true if the taxi center has to process a new recieving data
     * @param flag the new condition of the taxi center
     */
    void setReceiveDataFlag(bool flag,int driverIndex);
    /**
     * @return true if the taxi center is busy to get applies, else return false
     */
    bool getReceiveDataFlag(int driverIndex);
    void sendCloseToClients(Socket *tcp);
    void setNewClientSd(int newClientSd);
    };
struct TripData
{
    Trip *trip;
    Bfs *bfs;
    //pthread_mutex_t mutex;
};

#endif //AP_EX1_TAXICENTER_H