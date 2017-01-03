#ifndef AP_EX1_CABFACTORY_H
#define AP_EX1_CABFACTORY_H
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
#include <boost/serialization/base_object.hpp>

using namespace std;
using namespace boost::archive;

enum Manufacturer {HONDA = 'H',SUBARO = 'S',TSELA = 'T',FIAT = 'F'};
enum Color {RED = 'R',BLUE= 'B',GREEN = 'G',PINK = 'P',WHITE = 'W'};
/**
 * this is the class of the abstract class that create the cabs
 */
class CabFactory {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {}
public:
    /**
     * @return new cab
     */
    CabFactory(){};
    /**
     * dtor
     */
    virtual ~CabFactory(){};
    /**
     * @return num of km passed
     */
    virtual double howManyKm() = 0;
    /**
     * @return cab's tariff
     */
    virtual double getTariff() = 0;
    /**
     * @return cab's speed
     */
    virtual int getSpeed() = 0;
    /**
     * @param meters meters passed to update the current km passed
     */
    virtual void updateKm(double meters) =0;
    /**
     * @return the manufacturer
     */
    virtual Manufacturer getManufacturer()=0;
    /**
     * @return cab's color
     */
    virtual Color getColor()=0;
    /**
     * @return the id of the current cab
     */
    virtual int getID()=0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(CabFactory)



#endif //AP_EX1_CABFACTORY_H
