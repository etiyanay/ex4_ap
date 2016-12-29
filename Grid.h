#ifndef AP_EX1_GRID_H
#define AP_EX1_GRID_H

#include "NodePoint.h"
#include "vector"

using namespace std;
/**
 * this class is an abstract class which TwoDim class derives from it
 * the class is in charge of the grid (= map)
 */
class Grid {
public:
    /**
     * constructor
     * @return a new grid -> will create in the derived classes
     */
    Grid(){};
    /**
     * dtor
     */
    virtual ~Grid(){};
    /**
    * @param current is a pointer to a point to find its neighbors
    * @return a vector with all the pointers to the neighbors points
    */
    virtual vector<Point*> neighborsPoints(Point* current) = 0;
    /**
    * @param current is a pointer to a point to check if it's in the range of the grid
    * @return true if it is in range, else return false
    */
    virtual bool ifInRange(Point* current) = 0;
    /**
    * this func initialize the grid with nodes with cordinates[x][y]
    */
    //virtual void initializeGrid() = 0;
    /**
    * @return the pointer to the grid (as a NodePoint*)
    */
    virtual NodePoint** getPtrGrid() = 0;
    /**
    * @param currentPoint is a pointer to a point to find its node in the grid
    * @return the pointer to the node that contains the point
    */
    virtual NodePoint* whereIsTheNode(Point* currentPoint) =0;
    /**
     * initializing the gerid as atabula rasa - without any visited nodes
     * or nodes that have fathers
     */
    virtual void initializeGrid()=0;
};
#endif //AP_EX1_GRID_H
