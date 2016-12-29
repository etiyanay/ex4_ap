#ifndef AP_EX1_POINT2D_H
#define AP_EX1_POINT2D_H

#include "Point.h"
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

using namespace std;
using namespace boost::archive;
/**
 * this class derives from the abstract class - "Point"
 * it represents the 2D point type (x,y)
 */
class Point2D : public Point {
private:
    int x;
    int y;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Point>(*this);
        ar & x;
        ar & y;
    }
public:
    Point2D(int xAxis, int yAxis);
    ~Point2D(){};
    Point2D(){};
    void print();
    void setPoint(Point* p1);
    void setPoint(int xAxis, int yAxis);
    bool equals(Point* p1);
    Point* plus(Point* p1);
    int getX();
    int getY();
    void printPoint(ostream& os) const;
};
#endif //AP_EX1_POINT2D_H
