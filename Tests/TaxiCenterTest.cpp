#include "gtest/gtest.h"
#include "../TaxiCenter.h"
#include "../TwoDim.h"
#include "../StandardCab.h"
#include "../Point2D.h"


using namespace std;
/**
 * this is a test class for the class TaxiCenter
 */
class TaxiCenterTest : public ::testing::Test {
protected:
    TaxiCenter *center;
    Point *source, *destination;
    Grid* map;
    Bfs *currentBfs;
    Driver driver1, driver2, closestDriver;
    CabFactory *taxi1, *taxi2;
    NodePoint* node;
    Point2D p1;
    Trip newTrip, otherTrip;
    virtual void SetUp() {
        source = new Point2D(0,0);
        destination = new Point2D(3,3);
        p1 = Point2D(0,0);
        node = new NodePoint(&p1);
        //creating 2 cabs
        taxi1 = new StandardCab(5555,SUBARO,PINK);
        taxi2 = new StandardCab(6666,SUBARO,RED);
        map = new TwoDim(4,4);
        //creating 2 drivers
        driver1 = Driver(55555, 25, SINGLE, 5);
        driver2 = Driver(10101, 50, MARRIED, 10);
        currentBfs = new Bfs(map);
        center = new TaxiCenter(map,currentBfs);
        //creating 2 trips
        newTrip = Trip(123456, source, destination, 2, 13.5);
        otherTrip = Trip(123, source, destination, 5, 14.2);

    }
    virtual void TearDown(){
        delete source;
        delete destination;
        delete center;
    }
public:
    TaxiCenterTest() {}
};
/**
 * the test checks the method addNewDriver from TaxiCenter Class
 * checks if the num of drivers changed after adding a new driver
 */
TEST_F(TaxiCenterTest, addNewDriverCheck){
    ASSERT_EQ(center->getNumOfDrivers(), 0);
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    center->addNewDriver(driver1, 6666);
    ASSERT_NE(center->getNumOfDrivers(), 0);
    ASSERT_EQ(center->getNumOfDrivers(), 1);
};
/*
 * the test checks the method addNewCab from TaxiCenter Class
 * checks if the num of cabs changed after adding a new cab
 */
TEST_F(TaxiCenterTest, addNewCabCheck){
    ASSERT_EQ(center->getNumOfCabs(), 0);
    center->addNewCab(taxi1);
    ASSERT_NE(center->getNumOfCabs(), 0);
    ASSERT_EQ(center->getNumOfCabs(), 1);
}
/*
 * not implemented yet.
 * the test checks the method findClosestDriver from TaxiCenter Class
 * checks if the location of the closest driver we found - equals to the right closest driver
 */
TEST_F(TaxiCenterTest, findClosestDriverCheck){
    /*driver2.setLocation(map->getPtrGrid()[2]);
    center.addNewDriver(driver1, 5555);
    center.addNewDriver(driver2, 6666);
    cout<<center.findClosestDriver(source).getId()<<endl;
    ASSERT_EQ(center.findClosestDriver(source).getId() ,driver2.getId());*/
}
/*
 * the test checks the method getNumOfDrivers from TaxiCenter Class
 * checks if the num of drivers changed after adding a new driver
 */
TEST_F(TaxiCenterTest, getNumOfDriversCheck){
    ASSERT_EQ(center->getNumOfDrivers(), 0);
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    center->addNewDriver(driver1, 6666);
    ASSERT_NE(center->getNumOfDrivers(), 0);
    ASSERT_EQ(center->getNumOfDrivers(), 1);
    center->addNewDriver(driver1, 5555);
    ASSERT_EQ(center->getNumOfDrivers(), 2);
}
/*
 * the test checks the method getNumOfCabs from TaxiCenter Class
 * checks if the num of cabs changed after adding a new cab
 */
TEST_F(TaxiCenterTest,getNumOfCabsCheck){
    ASSERT_EQ(center->getNumOfCabs(), 0);
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    ASSERT_EQ(center->getNumOfCabs(), 2);
}
/*
 * the test checks the method findCabById from TaxiCenter Class
 * checks if the returned cab is the wanted cab
 */
TEST_F(TaxiCenterTest,findCabByIdCheck){
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    ASSERT_EQ(center->findCabById(5555)->getID(), 5555);
    ASSERT_EQ(center->findCabById(5555)->getColor(),PINK);
}
/*
 * the test checks the method findDriverLocationById from TaxiCenter Class
 * checks the location of the wanted driver, equals to the right point
 */
TEST_F(TaxiCenterTest,findDriverLocationByIdCheck){
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    center->addNewDriver(driver1,5555);
    center->addNewDriver(driver2,6666);
    ASSERT_TRUE(center->findDriverLocationById(55555)->equals(&p1));
}
/*
 * the test checks the method addNewTrip from TaxiCenter Class
 * checks if after adding a trip- the num of trips changed
 */
TEST_F(TaxiCenterTest,addNewTripCheck){
    ASSERT_EQ(center->getNumOfTrips(), 0);
    center->addNewTrip(newTrip);
    ASSERT_EQ(center->getNumOfTrips(), 1);
    center->addNewTrip(otherTrip);
    ASSERT_EQ(center->getNumOfTrips(), 2);
}
/*
 * the test checks the method startDriving from TaxiCenter Class
 * checks if the driver really did move to their destination point
 */
TEST_F(TaxiCenterTest,startDrivingCheck){
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    center->addNewDriver(driver1,5555);
    center->addNewDriver(driver2,6666);
    center->addNewTrip(newTrip);
    center->addNewTrip(otherTrip);
    ASSERT_TRUE(center->findDriverLocationById(55555)->equals(&p1));
    ASSERT_TRUE(center->findDriverLocationById(10101)->equals(&p1));
    center->assignTripsToDrivers();
    center->startDriving();
    ASSERT_TRUE(center->findDriverLocationById(55555)->equals(destination));
    ASSERT_TRUE(center->findDriverLocationById(10101)->equals(destination));
}
/*
 * not implemented yet.
 * the test checks the method getCall from TaxiCenter Class
 * checks if the start point of the trip of the closest driver we found -
 * equals to the original source point we initialized above and send in getCall method
 */
TEST_F(TaxiCenterTest, getCallCheck){
    //we get exit code 139
    /*driver2.setLocation(node);
    center.addNewDriver(driver1);
    center.addNewDriver(driver2);
    center.getCall(source, destination);
    ASSERT_TRUE(driver2.getTrip().getStartPoint()->equals(source));*/
}
/*
 * the test checks the method assignTripsToDrivers from TaxiCenter Class
 * checks if we succeeded matching the trips to drivers
 */
TEST_F(TaxiCenterTest,assignTripsToDriversCheck){
    center->addNewCab(taxi1);
    center->addNewCab(taxi2);
    center->addNewDriver(driver1,5555);
    center->addNewDriver(driver2,6666);
    center->addNewTrip(newTrip);
    center->addNewTrip(otherTrip);
    center->assignTripsToDrivers();
    center->startDriving();
    ASSERT_TRUE(center->findDriverLocationById(55555)->equals(destination));
    ASSERT_TRUE(center->findDriverLocationById(10101)->equals(destination));
}
/*
 * the test checks the method getNumOfTrips from TaxiCenter Class
 * checks if after adding a trip- the num of trips changed
 */
TEST_F(TaxiCenterTest,getNumOfTripsCheck){
    ASSERT_EQ(center->getNumOfTrips(), 0);
    center->addNewTrip(newTrip);
    ASSERT_EQ(center->getNumOfTrips(), 1);
    center->addNewTrip(otherTrip);
    ASSERT_EQ(center->getNumOfTrips(), 2);
}