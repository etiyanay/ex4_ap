#include "Point2D.h"
#include <iostream>
#include "Point2D.h"
#include <string>
#include <sstream>

using namespace std;
/**
 * @param xAxis is the x size of the point
 * @param yAxis is the y size of the point
 * @return a new point according the (x,y) that is given
 */
Point2D::Point2D(int xAxis, int yAxis){
    x = xAxis;
    y = yAxis;
}
/**
 * @param p1 is the new pointer to point to set instead the current point
 */
void Point2D::setPoint(Point* p1) {
    x = ((Point2D*) p1)->x;
    y = ((Point2D*) p1)->y;
}
/**
 * the func prints the point with (x,y)
 */
void Point2D::print() {
    cout <<"("<<x<<","<<y<<")"<<endl;
}
/**
 * @param p1 is the pointer to a point to check if equals
 * @return true if they equal, else- return false
 */
bool Point2D::equals(Point* p1) {
    return ((x == ((Point2D*) p1)->x) && (y == ((Point2D*) p1)->y));
}
/**
 * @param p1 is a pointer to a point to add it to the current poont
 * @return a pointer to othe new point after calculating
 */
Point* Point2D::plus(Point* p1) {
    x += ((Point2D*) p1)->x;
    y += ((Point2D*) p1)->y;
}
/**
 * @return the x val of the point
 */
int Point2D::getX() {
    return x;
}
/**
 * @return the y val of the point
 */
int Point2D::getY() {
    return y;
}
void Point2D::printPoint(ostream &os) const{
    os<<"(" << this->x << "," << this->y << ")";

}

