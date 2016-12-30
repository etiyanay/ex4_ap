#ifndef AP_EX1_TWODIM_H
#define AP_EX1_TWODIM_H

#include "NodePoint.h"
#include "Point.h"
#include "Grid.h"
#include "vector"
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
#include <boost/array.hpp>

#include <boost/multi_array.hpp>

using namespace std;
using namespace boost::archive;
/**
 * this class derives from the abstract class- "Grid"
 * it represents the 2D map with Points2D
 */
class TwoDim : public Grid {
private:
    int sizeX, sizeY;
    NodePoint** ptrAllNodes;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Grid>(*this);
        ar & sizeX;
        ar & sizeY;
        ar & *ptrAllNodes;
    }
public:
    /**
     * ctor
     * @return a new TwoDim
     */
    TwoDim(){};
    /**
    * constructor
    * @param xAxis is the x's size of the grid
    * @param yAxis is the y's size of the grid
    * @return a new 2D grid, after allocating memory for it
    */
    TwoDim(int xAxis, int yAxis);
    /**
     * dtor
     */
    ~TwoDim();
    /**
     * @param current the point to find its neighbors
     * @return a vector with all the points of the neighbors
     */
    vector<Point*> neighborsPoints(Point* current);
    /**
     * @param current the point to check if in the range of the dim size
     * @return "true" if it's in the range, "false" if not
     */
    bool ifInRange(Point* current);
    /**
     * the funcs initialize the grid with nodes inside
     */
    //void initializeGrid();
    /**
     * @return the ptr to thr dim
     */
    NodePoint** getPtrGrid();
    /**
     * @param currentPoint the point to find its node in the grid
     * @return the node where the point is
     */
    NodePoint* whereIsTheNode(Point* currentPoint);
    /**
    * initializing the gerid as atabula rasa - without any visited nodes
    * or nodes that have fathers
    */
    void initializeGrid();
};
#endif //AP_EX1_TWODIM_H