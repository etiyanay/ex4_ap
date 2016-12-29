#ifndef AP_EX1_BFS_H
#define AP_EX1_BFS_H

#include "NodePoint.h"
#include "Point.h"
#include "Grid.h"
#include "vector"

using namespace std;
/**
 * this class is in charge of the BFS algorithm to find the shortest path between 2 points
 * the bfs gets pointer to grid and pointers to start and detination points
 */
class Bfs {
private:
    Grid* currentGrid;
public:
    Bfs(){};
    /**
    * constructor
    * @param currentGrid is the pointer to the grid (is the dim of the map)
    * @return the the bfs object
    **/
    Bfs(Grid* currentGrid);
    /**
     * d'tor
     */
    ~Bfs();
    /**
    * the algorithm finds the shortest way between 2 points (from the constructor)
    * @param startPoint is the pointer to the start point
    * @param destination is the pointer to the destination point
    * @return the last node in the path (= the destination point- as a node)
    */
    NodePoint* bfsAlgorithm(Point* startPoint, Point* destination);
    /**
    * @param startPoint is the pointer to the start point
    * @param destination is the pointer to the destination point* the func calls the bfsAlgorithm() func, and from the last node it extracts the previous nodes
    * @return vector with all the nodes on the path to the destination
    */
    vector<NodePoint*> runBfs(Point* startPoint, Point* destination);
};
#endif //AP_EX1_BFS_H
