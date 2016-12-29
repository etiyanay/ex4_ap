#include "gtest/gtest.h"
#include "../Point.h"
#include "../Passenger.h"
#include "../Point2D.h"

using namespace std;
/**
 * this is a test class for the class Passenger
 */
class PassengerTest : public ::testing::Test {
protected:
    Passenger pass;
    Point2D p3, p4;

    virtual void SetUp() {
        p3 = Point2D(1,2);
        p4 = Point2D(3,4);
        pass = Passenger(&p3,&p4);
    }
    virtual void TearDown(){
    }
public:
    PassengerTest()  {}
};
/**
 * the test checks the method getSourcePoint from Passenger Class
 * checks the source point of a passanger if equals to another point
 */
TEST_F(PassengerTest, GetSourcePointCheck){
    EXPECT_EQ(p3.equals(pass.getSourcePoint()), true);
    EXPECT_EQ(p4.equals(pass.getSourcePoint()), false);
}
/**
 * the test checks the method getDestinationPoint from Passenger Class
 * checks the source point of a passanger if equals to another point
 */
TEST_F(PassengerTest, getDestinationPoint){
    EXPECT_EQ(p4.equals(pass.getDestinationPoint()), true);
    EXPECT_EQ(p3.equals(pass.getDestinationPoint()), false);
}
/**
 * the test checks the method sendRandomScore from Passenger Class
 * checks the random score we got- is in range of 1-5
 */
TEST_F(PassengerTest, sendRandomScore){
    int a = pass.sendRandomScore();
    EXPECT_EQ(((a >= 1) && (a <= 5)), true);
}