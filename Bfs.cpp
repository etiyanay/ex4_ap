#include "Bfs.h"
#include <queue>


using namespace std;

Bfs::Bfs(Grid* currentGrid) {
    this->currentGrid = currentGrid;
}
Bfs::~Bfs() {
    delete this->currentGrid;
}
NodePoint* Bfs::bfsAlgorithm(Point* startPoint, Point* destination) {
    //initializing a queue to insert the nodes to check on the way
    queue<NodePoint*> nodesQueue;
    //find the pointer to the start node in the grid
    NodePoint* startNode = this->currentGrid->whereIsTheNode(startPoint);
    nodesQueue.push(startNode);
    startNode->setVisited();
    while (!nodesQueue.empty()) {
        NodePoint* tempNode = nodesQueue.front();
        nodesQueue.pop();
        if (tempNode->getPoint()->equals(destination))
            return tempNode;
        vector<Point*>neighbors = this->currentGrid->neighborsPoints(tempNode->getPoint());
        int i;
        //for each neighbor, check if wasn't visited and set as visited and insert to the queue
        for (i = 0; i < neighbors.size(); ++i) {
            NodePoint* child = this->currentGrid->whereIsTheNode(neighbors[i]);
            //deleting the point from memory- after finding its node's location
            delete neighbors[i];
            if (!child->isVisited()) {
                child->initializeFather(tempNode);
                child->setVisited();
                nodesQueue.push(child);
            }
        }
    }
}

vector<NodePoint*> Bfs::runBfs(Point* startPoint, Point* destination) {
    vector<NodePoint*> path;
    NodePoint* destinationP = this->bfsAlgorithm(startPoint, destination);
    path.push_back(destinationP);
    NodePoint* tempNode = destinationP;
     while (NULL != tempNode->getFather()) {
         path.push_back(tempNode->getFather());
         tempNode = tempNode->getFather();
     }
    vector<NodePoint*> pathByOrder;
    //insert the nodes to the vec by order
    int i;
    for (i = path.size()-1; i >= 0; i--) {
        pathByOrder.push_back(path[i]);
    }
    return pathByOrder;
}