#include <iostream>
#include <cstdlib>
#include "TwoDim.h"
#include "Point2D.h"

using namespace std;

TwoDim::TwoDim(int xAxis, int yAxis) {
    this->sizeX = xAxis;
    this->sizeY = yAxis;
    this->ptrAllNodes = new NodePoint*[xAxis];
    for (int k = 0; k < xAxis; ++k) {
        this->ptrAllNodes[k] = new NodePoint[yAxis];
    }
    for (int i = 0; i < xAxis; ++i) {
        for (int j = 0; j < yAxis; ++j) {
            Point* p  = new Point2D(i,j);
            NodePoint* node =  new NodePoint(p);
            this->ptrAllNodes[i][j] = *node;
        }
    }
}
TwoDim::~TwoDim() {
    for (int i = 0; i < this->sizeX; ++i)
            delete [] ptrAllNodes[i];
    delete [] ptrAllNodes;
}
NodePoint** TwoDim::getPtrGrid() {
    return ptrAllNodes;
}

vector<Point*> TwoDim::neighborsPoints(Point* current) {
    vector<Point*> neighbors;
    Point2D* temp = (Point2D*) current;
    int xOfCurrent = temp->getX();
    int yOfCurrent = temp->getY();
    //the optional neighbors as points
    Point2D left(xOfCurrent-1,yOfCurrent);
    Point2D up(xOfCurrent,yOfCurrent+1);
    Point2D right (xOfCurrent+1,yOfCurrent);
    Point2D down(xOfCurrent,yOfCurrent-1);
    //checking if the neighbors are in the range
    if(this->ifInRange(&left)) {
        Point* ptrLeft = new Point2D(left);
        neighbors.push_back(ptrLeft);
    }
    if(this->ifInRange(&up)) {
        Point* ptrUp = new Point2D(up);
        neighbors.push_back(ptrUp);
    }
    if(this->ifInRange(&right)) {
        Point* ptrRight = new Point2D(right);
        neighbors.push_back(ptrRight);
    }
    if(this->ifInRange(&down)) {
        Point* ptrDown = new Point2D(down);
        neighbors.push_back(ptrDown);
    }
    return neighbors;
}

bool TwoDim::ifInRange(Point* current) {
    Point2D* temp = (Point2D*) current;
    return (((temp->getX() >=0) && (temp->getX() < sizeX)) &&
            ((temp->getY() >=0) && (temp->getY() < sizeY)));
}

NodePoint* TwoDim::whereIsTheNode(Point* currentPoint) {
    Point2D* currentPoint2D = (Point2D*)currentPoint;
    int xPoint = currentPoint2D->getX();
    int yPoint = currentPoint2D->getY();
    return &this->getPtrGrid()[xPoint][yPoint];
}

void TwoDim::initializeGrid() {
    for (int i = 0; i < this->sizeX; ++i) {
        for (int j = 0; j < this->sizeY; ++j) {
            this->ptrAllNodes[i][j].initializeFather(NULL);
            this->ptrAllNodes[i][j].setNotVisited();
        }
    }
}