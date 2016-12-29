#include <iostream>
#include <boost/serialization/access.hpp>

#ifndef AP_EX1_POINT_H
#define AP_EX1_POINT_H

using namespace std;
using namespace boost::archive;

/**
 * this is an abstract class that the points type class derive from it
 */
class Point {
public:
    /**
     * print the point as (x,y)
     */
    virtual void print() = 0;
    /**
     * constructor
     * @return a new point
     */
    Point(){};
    /**
     * dtor
     */
    virtual ~Point(){};
    /**
     * @param p1 the new point to set as the current point
     */
    virtual void setPoint(Point* p1) = 0;
    /**
     * @param p1 the point to check if it equals to the current point
     * @return "true" if equals, "false" if not
     */
    virtual bool equals(Point* p1) = 0;
    /**
     * @param p1 the point to add to the current point
     * @return the new point after calculating its new values
     */
    virtual Point* plus(Point* p1) = 0;
    /**
     * the func that in charge of printing generically the points
     * @param os os
     */
    virtual void printPoint(ostream& os) const=0;
    /**
     * in charge of the os stream
     * @param os
     * @param point
     * @return
     */
    friend ostream& operator << (ostream& os, const Point* point);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {}
};

#endif //AP_EX1_POINT_H