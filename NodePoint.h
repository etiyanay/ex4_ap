#ifndef AP_EX1_NODEPOINT_H
#define AP_EX1_NODEPOINT_H

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
 * this class represents the node object. the NodePoint hold a ptr to the point,
 * a ptr to the father and a bool flag that indicates if the node was visited.
 */
class NodePoint {
private:
    Point* currentPoint;
    NodePoint* ptrFather;
    bool flagIsVisited;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & currentPoint;
        ar & ptrFather;
        ar & flagIsVisited;
    }
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
