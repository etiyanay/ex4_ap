#ifndef AP_EX1_DRIVER_H
#define AP_EX1_DRIVER_H

#include <iostream>
#include <vector>
#include "CabFactory.h"
#include "Passenger.h"
#include "Trip.h"
#include "Grid.h"
#include "Clock.h"
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
    bool isAvailable;
    Clock time;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & yearsOfExperience;
        ar & cabId;
        ar & satisfactionAvg;
        ar & totalScore;
        ar & numOfPassengers;
        ar & status;
        ar & taxiCab;
        ar & currentTrip;
        ar & location;
        ar & isAvailable;
        ar & time;
    }
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
     *
     * @return
     */
    int getCabId();
    bool setIsAvailable();
    bool getIsAvailable();
};

#endif //AP_EX1_DRIVER_H