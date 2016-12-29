#include "gtest/gtest.h"
#include "../TwoDim.h"
#include "../Point2D.h"

using namespace std;
/**
 * this is a test class for the class TwoDim
 */
class TwoDimTest : public ::testing::Test {
protected:
    TwoDim map;
    Point2D p, p2, p3;
    Point *ptr, *ptr2, *ptr3;
    virtual void SetUp() {
        p = Point2D(2,2);
        p2 = Point2D(4,4);
        p3 =  Point2D(-1,0);
        ptr = &p;
        ptr2 = &p2;
        ptr3 = &p3;
    }
    virtual void TearDown(){
    }
public: TwoDimTest() : map(4,4) {}
};
/**
 * the test checks the method ifInRange from TwoDim Class
 */
TEST_F(TwoDimTest, IfInRangeCheck){
    ASSERT_TRUE(map.ifInRange(ptr));
    ASSERT_FALSE(map.ifInRange(ptr2));
    ASSERT_FALSE(map.ifInRange(ptr3));
}
/**
 * the test checks the method initializeGrid from TwoDim Class
 * checks the node in (2,2) and compare it to the ptr above that points to (2,2)
 */
TEST_F(TwoDimTest, InitializeGridCheck){
    //map.initializeGrid();
    ASSERT_TRUE(map.getPtrGrid()[2][2].getPoint()->equals(ptr));
}
/**
 * the test checks the method whereIsTheNode from TwoDim Class
 * checks if a node is indeed in range - compare it to another point
 * if it's not equal - the test fails and doesn't continue to test the second test
 */
TEST_F(TwoDimTest, WhereIsTheNodeCheck){
    ASSERT_FALSE(map.ifInRange(ptr3));
    ASSERT_TRUE(map.whereIsTheNode(ptr)->getPoint()->equals(ptr));
}
/**
 * the test checks the method neighborsPoints from TwoDim Class
 * checks who are the neighbors points of a point, insert them to a vector
 * than check if the values equal to the the neighbors points
 */
TEST_F(TwoDimTest, NeighborsPointsCheck){
    vector <Point*> neighbors = map.neighborsPoints(ptr);
    Point2D left(1,2);
    Point2D up(2,3);
    Point2D right(3,2);
    Point2D down(2,1);
    ASSERT_TRUE(neighbors[0]->equals(&left));
    ASSERT_TRUE(neighbors[1]->equals(&up));
    ASSERT_TRUE(neighbors[2]->equals(&right));
    ASSERT_TRUE(neighbors[3]->equals(&down));
}
