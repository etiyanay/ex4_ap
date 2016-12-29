#include <iostream>
#include "NodePoint.h"

using namespace std;

NodePoint::NodePoint(Point* currentPoint) {
    this->currentPoint= currentPoint;
    ptrFather = NULL;
    flagIsVisited = 0;
}
NodePoint::~NodePoint() {
    delete this->currentPoint;
    //delete this->ptrFather;
}

bool NodePoint::isVisited() {
    return flagIsVisited;
}

void NodePoint::setVisited() {
    flagIsVisited = 1;
}
void NodePoint::setNotVisited() {
    flagIsVisited = 0;
}
void NodePoint::initializeFather(NodePoint* currentNode) {
    ptrFather = currentNode;
}

Point* NodePoint::getPoint() {
    return currentPoint;
}

NodePoint* NodePoint::getFather() {
    return ptrFather;
}