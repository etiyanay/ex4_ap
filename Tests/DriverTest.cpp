#include "gtest/gtest.h"
#include "../Driver.h"
#include "../Point2D.h"
#include "../StandardCab.h"
#include "../TwoDim.h"

using namespace std;
/**
 * this is a test class for the class Driver
 */
class DriverTest : public ::testing::Test {
protected:
    Driver driver1;
    Trip newTrip, otherTrip;
    Point2D p1;
    Point *source, *destination;
    CabFactory* taxi;
    Passenger *pass1;
    vector <Passenger*> currentPassengers;
    NodePoint *newLocation;
    Grid* map;
    virtual void SetUp(){
        p1 = Point2D(0,0);
        driver1 = Driver(0, 30, SINGLE, 5);
        source = new Point2D(0,3);
        destination = new Point2D(2,2);
        taxi = new StandardCab(555,SUBARO,PINK);
        pass1 = new Passenger(source, destination);
        currentPassengers.push_back(pass1);
        newTrip = Trip(123456, source, destination, 5, currentPassengers);
        otherTrip = Trip(123, source, destination, 5, currentPassengers);
        driver1.setNewTrip(newTrip);
        newLocation = new NodePoint(destination);
        map = new TwoDim(5,5);
    }
    virtual void TearDown(){
        delete source;
        delete destination;
        delete pass1;
        delete taxi;
        delete map;
    }
public: DriverTest() {}
};
/**
 * the test checks the method evaluateSatisfaction from Driver Class
 * checks if it successes to calculate the avg satisfaction- as total score/num of passengers
 * if there are no passangers at all- it doesn't run the test
 */
TEST_F(DriverTest, EvaluateSatisfactionCheck){
    double numOfPassengers= driver1.getNumOfPassengers();
    if(numOfPassengers!=0) {
        EXPECT_EQ(driver1.getTotalScore()/numOfPassengers, driver1.evaluateSatisfaction());
    }
}
/**
 * the test checks the method getScoreFromCurrentPassenger from Driver Class
 * checks that driver's score got changed from 0 after getting a score from a passenger
 */
TEST_F(DriverTest, GetScoreFromCurrentPassengerCheck){
    driver1.getScoreFromCurrentPassenger();
    ASSERT_NE(0, driver1.getTotalScore());
    ASSERT_EQ(1, driver1.getTotalScore());
}
/**
 * the test checks the method setNewTrip from Driver Class
 * checks that driver's trip got changed after setting a new trip
 */
TEST_F(DriverTest, SetNewTripCheck){
    driver1.setNewTrip(newTrip);
    EXPECT_EQ(driver1.getTrip().getId(), newTrip.getId());
    ASSERT_TRUE(driver1.getTrip().getStartPoint()->equals(newTrip.getStartPoint()));
    ASSERT_TRUE(driver1.getTrip().getEndPoint()->equals(newTrip.getEndPoint()));
}
/**
 * the test checks the method calculateTripCost from Driver Class
 * setting a cab and a trip to a driver, and check if it made the right calculation
 */
TEST_F(DriverTest, CalculateTripCostCheck){
    driver1.setNewTrip(newTrip);
    driver1.setCab(taxi);
    EXPECT_EQ( driver1.calculateTripCost(),
               driver1.getTrip().getTripCost() * driver1.getCab()->getTariff());
}
/**
 * the test checks the method getTrip from Driver Class
 * setting a trip to a driver, and check by ID if it did set the trip
 */
TEST_F(DriverTest, GetTripCheck){
    driver1.setNewTrip(newTrip);
    EXPECT_TRUE(driver1.getTrip().getStartPoint()->equals(source));
    EXPECT_TRUE(driver1.getTrip().getEndPoint()->equals(destination));
    EXPECT_EQ(driver1.getTrip().getId(), 123456);
}
/**
 * the test checks the method setCab from Driver Class
 * setting a cab to a driver, and check by manufacturer if it did set the cab
 */
TEST_F(DriverTest, SetCabCheck){
    driver1.setCab(taxi);
    ASSERT_EQ(driver1.getCab()->getTariff(), 1);
    ASSERT_EQ(driver1.getCab()->getManufacturer(), SUBARO);
}
/**
 * the test checks the method getCab from Driver Class
 * setting a cab to a driver, and check by getCab if it did set the cab
 */
TEST_F(DriverTest, GetCabCheck){
    driver1.setCab(taxi);
    ASSERT_EQ(driver1.getCab()->getTariff(), taxi->getTariff());
    ASSERT_EQ(driver1.getCab()->getManufacturer(), taxi->getManufacturer());
}
/**
 * the test checks the method getTotalScore from Driver Class
 * checks that driver's total score got changed from 0 after getting a score from a passenger
 */
TEST_F(DriverTest, GetTotalScoreCheck){
    ASSERT_EQ(driver1.getTotalScore(), 0);
    driver1.getScoreFromCurrentPassenger();
    ASSERT_NE(driver1.getTotalScore(), 0);
}
/**
 * the test checks the method getNumOfPassengers from Driver Class
 * checks if the method counting all passengers in all trips the driver has
 * check tne counter after initilaize two trips
 */
TEST_F(DriverTest, GetNumOfPassengersCheck) {
    EXPECT_EQ(driver1.getNumOfPassengers(), 1);
    driver1.setNewTrip(otherTrip);
    ASSERT_EQ(driver1.getNumOfPassengers(), 2);
}
/**
 * the test checks the method getId from Driver Class
 * checks the driver's id that initialize in the constructor
 */
TEST_F(DriverTest, GetIdCheck) {
    EXPECT_EQ(driver1.getId(), 0);
    ASSERT_NE(driver1.getId(), 4);
}
/**
 * the test checks the method setMap from Driver Class
 * checks the driver's map after initializing
 */
TEST_F(DriverTest, SetMapCheck) {
    driver1.setMap(map);
    EXPECT_TRUE(map->getPtrGrid()[0][0].getPoint()->equals(driver1.getLocationInGrid()
                                                                   ->getPoint()));
}
/**
 * the test checks the method setLocation from Driver Class
 * checks what is the driver's new location after setting his new location
 */
TEST_F(DriverTest, SetLocationCheck) {
    driver1.setLocation(newLocation);
    EXPECT_TRUE(driver1.getLocationInGrid()->getPoint()->equals(destination));
}
/**
 * the test checks the method getLocationInGrid from Driver Class
 * checks what is the driver's new location after setting his new location
 */
TEST_F(DriverTest, GetLocationCheck) {
    driver1.setLocation(newLocation);
    EXPECT_TRUE(driver1.getLocationInGrid()->getPoint()->equals(destination));
}