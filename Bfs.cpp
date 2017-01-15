#include "Bfs.h"
#include "Trip.h"
#include <queue>
#include "TaxiCenter.h"

using namespace std;
pthread_mutex_t myMutex;


Bfs::Bfs(Grid* currentGrid) {
    this->currentGrid = currentGrid;
    pthread_mutex_init(&myMutex,0);

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
void* Bfs::calculatePath(void *element) {

    pthread_mutex_lock(&myMutex);

    //pthread_mutex_lock(&((TripData*)element)->mutex);
    TripData* data = (TripData*)element;
    cout << "the trip is:  " << data->trip->getId() << endl;
    //Trip newTrip = *((Trip*)trip);
    Point *start = data->trip->getStartPoint();
    Point *end = data->trip->getEndPoint();
    //vector<NodePoint*> path = this->runBfs(start,end);

    data->trip->setPath(data->bfs->runBfs(start,end));
    data->bfs->currentGrid->initializeGrid();

   pthread_mutex_unlock(&myMutex);

    //mutex unlock

    //return (void*)&path;
    //((Trip*)trip)->setPath(path);
}