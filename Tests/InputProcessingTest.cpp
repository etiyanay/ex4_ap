#include "gtest/gtest.h"
#include "../TwoDim.h"
#include "../Point2D.h"
#include "../InputProcessing.h"

using namespace std;
/**
 * this is a test class for the class InputProcessing
 */
class InputProcessingTest : public ::testing::Test {
protected:
    Point2D p1, p3;
    Point *p2;
    Grid* map;
    virtual void SetUp(){
        p1 =  Point2D(1,1);
        p3 = Point2D(4,4);
    }
    virtual void TearDown(){
    }
public:
    InputProcessingTest() {}
};
/**
 *this test runs the func stringPoints from InputProcessing Class
 * it checks if it knows to parse the input by ","
 * we compare each string in an index- to what it has to look like
 */
TEST_F(InputProcessingTest, StringPointsCheck){
    string input = "3_3,0_0,2_2";
    string* strPtr = stringPoints(input);
    ASSERT_EQ(strPtr[0], "3_3");
    ASSERT_EQ(strPtr[1], "0_0");
    ASSERT_EQ(strPtr[2], "2_2");
}
/**
 *this test runs the func countDimension from InputProcessing Class
 * it counts the shows of '_' in order to know what dim the point is
 * the test checks if it returns the real dimention size
 */
TEST_F(InputProcessingTest, countDimensionCheck){
    int countDim = countDimension("1_2_3_4_1");
    ASSERT_EQ(countDim, 5);
    countDim = countDimension("1");
    ASSERT_EQ(countDim, 1);
    countDim = countDimension("1_1");
    ASSERT_EQ(countDim, 2);
}
