#ifndef AP_EX1_PASSENGER_H
#define AP_EX1_PASSENGER_H
#include "Point.h"
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
#include <boost/serialization/access.hpp>

using namespace std;
using namespace boost::archive;
/**
 * this class is in charge of the passengers that exist in the trips
 */
class Passenger {
private:
    Point *source, *destination;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & source;
        ar & destination;
    }
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