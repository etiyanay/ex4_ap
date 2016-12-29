#ifndef AP_EX1_NODEPOINT_H
#define AP_EX1_NODEPOINT_H

#include "Point.h"

using namespace std;
/**
 * this class represents the node object. the NodePoint hold a ptr to the point,
 * a ptr to the father and a bool flag that indicates if the node was visited.
 */
class NodePoint {
private:
    Point* currentPoint;
    NodePoint* ptrFather;
    bool flagIsVisited;
public:
    /**
    * constructor
    * @param currentPoint is the ptr to the point in the node
    * @return a new node
    */
    NodePoint(Point* currentPoint);
    /**
    * a default constructor
    * @return a new node
    */
    NodePoint(){};
    /**
     * dtor
     */
    ~NodePoint();
    /**
    * @return true if the node was visited, else- return false
    */
    bool isVisited();
    /**
     * set the node to be unvisited (equals to 0)
     */
    void setNotVisited();
    /**
    * set the node to be visited (equals to 1)
    */
    void setVisited();
    /**
    * @param currentNode is a pointer to the current node's father
    */
    void initializeFather(NodePoint* currentNode);
    /**
    * @return a pointer to the point in the node
    */
    Point* getPoint();
    /**
    * @return a pointer to the node's father
    */
    NodePoint* getFather();
};
#endif //AP_EX1_NODEPOINT_H
