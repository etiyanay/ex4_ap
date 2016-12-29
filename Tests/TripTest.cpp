#include <gtest/gtest.h>
#include "../Point.h"
#include "../Point2D.h"
#include "../Trip.h"
#include "../Grid.h"
#include "../TwoDim.h"

using namespace std;
/**
 * this is a test class for the class Trip
 */
class TripTest : public ::testing::Test {
protected:
    Trip newTrip;
    Point *ptrSource, *ptrDest, *p2, *p3;
    Point2D tempPoint;
    vector<NodePoint*> path;
    NodePoint *firstPointOfPath, *secondPointPath, *thirdPointPath;
    virtual void SetUp() {
        ptrSource = new Point2D(2,2);
        ptrDest = new Point2D(4,4);
        tempPoint = Point2D(0,0);
        p2 = new Point2D(2,3);
        p3 = new Point2D(3,3);
        newTrip = Trip(1254, ptrSource, ptrDest, 4, 18.5);
        //making nodes for the trip's vector of path nodes
        firstPointOfPath = new NodePoint(ptrSource);
        secondPointPath = new NodePoint(p2);
        thirdPointPath = new NodePoint(p3);
        //push steps to vector
        path.push_back(firstPointOfPath);
        path.push_back(secondPointPath);
        path.push_back(thirdPointPath);
    }
    virtual void TearDown() {
        delete firstPointOfPath;
        delete secondPointPath;
        delete thirdPointPath;
    }
public:
    TripTest() {}
};
/**
 * the test checks the method getTripCostCheck from Trip Class
 * checks the cost of the new trip that was initialized above
 */
TEST_F(TripTest, GetTripCostCheck){
    ASSERT_EQ(newTrip.getTripCost(), 18.5);
}
/**
 * the test checks the method getStartPoint from Trip Class
 * checks the start point of the trip we initialize
 */
TEST_F(TripTest, GetStartPointCheck){
    EXPECT_TRUE(ptrSource->equals(newTrip.getStartPoint()));
    EXPECT_FALSE(tempPoint.equals(newTrip.getStartPoint()));
}
/**
 * the test checks the method getEndPoint from Trip Class
 * checks the dest point of the trip we initialize
 */
TEST_F(TripTest, GetEndPointCheck){
    EXPECT_TRUE(ptrDest->equals(newTrip.getEndPoint()));
    EXPECT_FALSE(tempPoint.equals(newTrip.getEndPoint()));
}
/*
 * the test checks the method GetId from Trip Class
 * checks the id of the new trip that was initialized above
 */
TEST_F(TripTest, GetIdCheck){
    ASSERT_EQ(newTrip.getId(), 1254);
}
/*
 *  the test checks the method SetPath from Trip Class
 *  checks if the path of the new trip is equal to the vector that was initialized above
 */
TEST_F(TripTest, SetPathCheck){
    //set path of trip
    newTrip.setPath(path);
    int lengthTrip = newTrip.getPath().size();
    //compare between vector and path
    for (int i = 0; i < lengthTrip ; ++i) {
        ASSERT_EQ(newTrip.getPath()[i], path[i]);
    }
}
/*
 *  the test checks the method GetPath from Trip Class
 *  checks if the path of the new trip is equal to the vector that was initialized above
 */
TEST_F(TripTest, GetPathCheck){
    newTrip.setPath(path);
    int lengthTrip = newTrip.getPath().size();
    for (int i = 0; i < lengthTrip ; ++i) {
        ASSERT_EQ(newTrip.getPath()[i], path[i]);
    }
}
