#include "gtest/gtest.h"
#include "../Point.h"
#include "../Point2D.h"

using namespace std;
/**
 * this is a test class for the class Point2D
 */
class Point2DTest : public ::testing::Test {
protected:
    Point2D p1, p2;
    int x, y;
    virtual void SetUp(){
        x = p1.getX();
        y = p1.getY();
        p1 = Point2D(1,2);
        p2 = Point2D(3,4);
    }
    virtual void TearDown() {
    }
public:
    Point2DTest()  {}
};
/**
 * the test checks the method getX from Point2D Class
 * checks a point, if its x vals equal to other x vals.
 */
TEST_F(Point2DTest, GetXCheck){
    EXPECT_EQ(1, p1.getX());
    EXPECT_NE(3, p1.getX());
}
/**
 * the test checks the method getY from Point2D Class
 * checks a point, if its y vals equal to other y vals.
 */
TEST_F(Point2DTest, GetYCheck){
    EXPECT_EQ(2, p1.getY());
    EXPECT_NE(3, p1.getY());
}
/**
 * the test checks the method pointsEqual from Point2D Class
 * checks if a point equals to another point
 */
TEST_F(Point2DTest, PointsEqualCheck) {
    ASSERT_NE(p1.equals(&p2), true);
}
/**
 * the test checks the method setPoint from Point2D Class
 * checks if setting point to be another point, succeeded
 */
TEST_F(Point2DTest, SetPointCheck){
    p1.setPoint(&p2);
    EXPECT_EQ(p2.equals(&p1), true);
}
/**
 * the test checks the method print from Point2D Class
 * checks if it prints the right point in the right format (x,y)
 */
TEST_F(Point2DTest,PrintCheck){
    testing::internal::CaptureStdout();
    p1.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(1,2)\n");
}
/**
 * the test checks the method plus from Point2D Class
 * checks if adding a point to another, succeeded
 */
TEST_F(Point2DTest,plusCheck){
    Point2D otherPoint = Point2D(4,6);
    EXPECT_EQ(p1.plus(&p2)->equals(&otherPoint), true);
}
/**
 * the test checks the method printPoint from Point2D Class
 * checks if printing a point in the right format, succeeded
 */
TEST_F(Point2DTest, printPointCheck){
    testing::internal::CaptureStdout();
    Point* other = &p1;
    cout<< other<<endl;
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(1,2)\n");
}

