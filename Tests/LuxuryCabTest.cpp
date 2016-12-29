#include "gtest/gtest.h"
#include "../LuxuryCab.h"

using namespace std;
/**
 * this is a test class for the class LuxuryCab
 */
class LuxuryCabTest : public ::testing::Test {
protected:
    LuxuryCab luxCab;
    double tariff;
    virtual void SetUp() {
        tariff = 25.01;
        luxCab = LuxuryCab(555,SUBARO,PINK);
    }
    virtual void TearDown(){
    }
public:
    LuxuryCabTest()  {}
};
/**
 * the test checks the method getManufacturerCheck from LuxuryCab Class
 * checks if the manufacturer member of the new cab we initialized above- does equal
 * or doesn't to manufacturers from the manufacturer enum
 */
TEST_F(LuxuryCabTest, GetManufacturerCheck){
    ASSERT_EQ(luxCab.getManufacturer(), SUBARO);
    ASSERT_NE(luxCab.getManufacturer(), FIAT);
}
/**
 * the test checks the method getColorCheck from LuxuryCab Class
 * checks if the color member of the new cab we initialized above- does equal
 * or doesn't to colors from the color enum
 */
TEST_F(LuxuryCabTest, GetColorCheck) {
    ASSERT_EQ(luxCab.getColor(), PINK);
    ASSERT_NE(luxCab.getColor(), WHITE);
}
/**
 * the test checks the method getTariffCheck from LuxuryCab Class
 * checks if the tariff member of the new cab we initialized above- does equal
 * or doesn't to tarrif we initialized above
 */
TEST_F(LuxuryCabTest, GetTariffCheck) {
    ASSERT_EQ(luxCab.getTariff(), 2);
    ASSERT_NE(luxCab.getTariff(), tariff);
}
/**
 * the test checks the method getSpeedCheck from LuxuryCab Class
 * checks if the speed member of the cab we initialized above, equals to 2
 * which is the speed of a Luxury cab
 */
TEST_F(LuxuryCabTest, GetSpeedCheck) {
    ASSERT_EQ(luxCab.getSpeed(), 2);
    ASSERT_NE(luxCab.getSpeed(), 1);
}
/**
 * the test checks the method howManyKm from LuxuryCab Class
 * checks if the km passed of the cab we initialized above, equals to 0- as a initial value
 */
TEST_F(LuxuryCabTest, HowMany) {
    ASSERT_EQ(luxCab.howManyKm(), 0.0);
}
/**
 * the test checks the method updateKm from LuxuryCab Class
 * checks if the km passed of the cab we initialized above, got changed after updating the km
 */
TEST_F(LuxuryCabTest, UpdateKmCheck) {
    luxCab.updateKm(1500);
    ASSERT_EQ(luxCab.howManyKm(), 1.5);
    luxCab.updateKm(200);
    ASSERT_EQ(luxCab.howManyKm(), 1.7);
}
/**
 * the test checks the method getID from LuxuryCab Class
 * checks if the id of the cab we initialized above, got changed
 */
TEST_F(LuxuryCabTest, getIDCheck) {
    ASSERT_EQ(luxCab.getID(), 555);
    ASSERT_NE(luxCab.getID(), 055);
}