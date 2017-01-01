//
// Created by naama on 01/01/17.
//

#ifndef AP_EX1_CLOCK_H
#define AP_EX1_CLOCK_H
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

class Clock {
private:
    int time;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & time;
    }
public:
    Clock(int startTime);
    Clock(){};
    ~Clock(){};
    void advanceTime();
    int timeIs();
};


#endif //AP_EX1_CLOCK_H
