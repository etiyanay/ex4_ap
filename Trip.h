#ifndef AP_EX1_TRIP_H
#define AP_EX1_TRIP_H
#include <vector>
#include "Point.h"
#include "NodePoint.h"
#include "Passenger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
using namespace boost::archive;


/**
 * this class is in charge of the trip object that is given to the drivers
 */
class Trip {
private:
    int id, metersPassed, numOfPassengers, clockTimeTrip;
    Point *startPoint, *endPoint;
    double tariff;
    vector <NodePoint*> path;
    vector <Passenger*> currentPassengers;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & metersPassed;
        ar & numOfPassengers;
        ar & clockTimeTrip;
        ar & startPoint;
        ar & endPoint;
        ar & tariff;
        ar & path;
        ar & currentPassengers;
    }
public:
    /**
     * default ctor
     * @return a new trip
     */
    Trip(){};
    /**
     * ctor
     * @param id the trip's id
     * @param source the trip's start point
     * @param destination the trip's destination point
     * @param numOfPassengers the num of the passengers in the current trip
     * @param tariff the cost of the trip
     * @return a new trip
     */
    Trip(int id, Point* source, Point* destination, int numOfPassengers, double tariff,
         int clockTimeTrip);
    /**
     * ctor
     * @param id the trip's id
     * @param source the trip's start point
     * @param destination the trip's destination point
     * @param tariff the cost of the trip
     * @param currentPassengers the vector of the passengers
     * @return
     */
    Trip(int id, Point* source, Point* destination, double tariff,
         vector <Passenger*> currentPassengers);
    /**
     * dtor
     */
    ~Trip(){};
    /**
     * @return the id of the trip
     */
    int getId();
    /**
     * @return the cost(tariff) of the trip
     */
    double getTripCost();
    /**
     * @return the start point of the trip
     */
    Point* getStartPoint();
    /**
     * @return the destination point of the trip
     */
    Point* getEndPoint();
    void setStartPoint();
    void setEndPoint();
    /**
     * @param newPath the path of the trip (the nodePoints by order) to the destination
     */
    void setPath(vector <NodePoint*> newPath);
    /**
     * @return the vector of all the nodes on the way to the destination (by order)
     */
    vector <NodePoint*> getPath();
    /**
     * @return the number of the passengers in the current trip
     */
    int getNumOfPassengers();
    /**
     * @return the total sum of the satisfaction score from all the passengers in the current trip
     */
    int passengersSendScore();
    /**
     *
     * @return the time that the trip should start
     */
    int getClockTimeTrip();
    /**
     * the func delete the trip info in the client
     */
    void deleteTripInClient();
};
#endif //AP_EX1_TRIP_H