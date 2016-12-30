#ifndef AP_EX1_LUXURYCAB_H
#define AP_EX1_LUXURYCAB_H
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
#include "CabFactory.h"

using namespace std;
using namespace boost::archive;
/**
 * this is the class of the Luxury cab- derives from CabFactory
 */
class LuxuryCab : public CabFactory {
private:
    int id;
    double numOfkm;
    Manufacturer manuName;
    Color currentColor;
    double tariff;
    int speed;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<CabFactory>(*this);
        ar & id;
        ar & numOfkm;
        ar & manuName;
        ar & currentColor;
        ar & tariff;
        ar & speed;
    }
public:
    /**
     * default constructor
     * @return new StandardCab
     */
    LuxuryCab(){};
    /**
     *constructor
     * @param id the cab's id
     * @param manuName the cab's manufacturer
     * @param currentColor the cab's color
     * @return a new luxury cab
     */
    LuxuryCab(int id ,Manufacturer manuName, Color currentColor);
    /**
     * dtor
     */
    ~LuxuryCab(){};
    /**
     * @return num of km passed
     */
    double howManyKm();
    /**
     * @return cab's tariff
     */
    double getTariff();
    /**
     * @return cab's speed- in this case is 2
     */
    int getSpeed();
    /**
     * @param meters meters passed to update the current km passed
     */
    void updateKm(double meters);
    /**
     * @return the manufacturer
     */
    Manufacturer getManufacturer();
    /**
     * @return cab's color
     */
    Color getColor();
    /**
     * @return cab's id
     */
    int getID();
};


#endif //AP_EX1_LUXURYCAB_H