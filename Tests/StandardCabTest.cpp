#include "gtest/gtest.h"
#include "../StandardCab.h"

using namespace std;
/**
 * this is a test class for the class StandardCab
 */
class StandardCabTest : public ::testing::Test {
protected:
    StandardCab stanCab;
    double tariff, tariff2;
    virtual void SetUp() {
        tariff = 15.123;
        stanCab = StandardCab(0123,SUBARO,PINK);
    }
    virtual void TearDown(){
    }
public:
    StandardCabTest()  {}
};
/**
 * the test checks the method getManufacturerCheck from StandardCab Class
 * checks if the manufacturer member of the new cab we initialized above- does equal
 * or doesn't to manufacturers from the manufacturer enum
 */
TEST_F(StandardCabTest, GetManufacturerCheck){
    ASSERT_EQ(stanCab.getManufacturer(), SUBARO);
    ASSERT_NE(stanCab.getManufacturer(), FIAT);
}
/**
 * the test checks the method getColorCheck from StandardCab Class
 * checks if the color member of the new cab we initialized above- does equal
 * or doesn't to colors from the color enum
 */
TEST_F(StandardCabTest, GetColorCheck) {
    ASSERT_EQ(stanCab.getColor(), PINK);
    ASSERT_NE(stanCab.getColor(), WHITE);
}
/**
 * the test checks the method getTariffCheck from StandardCab Class
 * checks if the tariff member of the new cab we initialized above- does equal
 * or doesn't to tarrif we initialized above
 */
TEST_F(StandardCabTest, GetTariffCheck) {
    ASSERT_EQ(stanCab.getTariff(), 1);
    ASSERT_NE(stanCab.getTariff(), tariff);
}
/**
 * the test checks the method getSpeedCheck from StandardCab Class
 * checks if the speed member of the cab we initialized above, equals to 1
 * which is the speed of a standard cab
 */
TEST_F(StandardCabTest, GetSpeedCheck) {
    ASSERT_EQ(stanCab.getSpeed(), 1);
    ASSERT_NE(stanCab.getSpeed(), 2);
}
/**
 * the test checks the method howManyKm from StandardCab Class
 * checks if the km passed of the cab we initialized above, equals to 0- as a initial value
 */
TEST_F(StandardCabTest, HowManyKmCheck) {
    ASSERT_EQ(stanCab.howManyKm(), 0.0);
}
/**
 * the test checks the method updateKm from StandardCab Class
 * checks if the km passed of the cab we initialized above, got changed after updating the km
 */
TEST_F(StandardCabTest, UpdateKmCheck) {
    stanCab.updateKm(150);
    ASSERT_EQ(stanCab.howManyKm(), 0.15);
    stanCab.updateKm(150);
    ASSERT_EQ(stanCab.howManyKm(), 0.3);
}
/**
 * the test checks the method getID from StandardCab Class
 * checks if the id of the cab we initialized above, got changed
 */
TEST_F(StandardCabTest, getIDCheck) {
    ASSERT_EQ(stanCab.getID(), 0123);
    ASSERT_NE(stanCab.getID(), 05);
}