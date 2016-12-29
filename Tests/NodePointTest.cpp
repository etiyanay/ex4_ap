#include "gtest/gtest.h"
#include "../Point.h"
#include "../Point2D.h"
#include "../NodePoint.h"

using namespace std;
/**
 * this is a test class for the class NodePoint
 */
class NodePointTest : public ::testing::Test {
protected:
    NodePoint *node;
    NodePoint* father;
    Point *ptr;
    Point2D p2;
    virtual void SetUp() {
        p2 = Point2D(2,1);
        ptr = new Point2D(2,2);
        father = new NodePoint(&p2);
        node = new NodePoint(ptr);
    }
    virtual void TearDown(){
        delete node;
    }
public:
    NodePointTest() {}
};
/**
 * the test checks the method isVisited from NodePoint Class
 * checks if the node has been visited (flag = 1)
 */
TEST_F(NodePointTest, IsVisitedCheck){
    ASSERT_FALSE(node->isVisited());
}
/**
 * the test checks the method setVisited from NodePoint Class
 * checks if the node has been visited (flag = 1) after setting it
 */
TEST_F(NodePointTest, SetVisitedCheck){
    node->setVisited();
    ASSERT_TRUE(node->isVisited());
}
/**
 * the test checks the method setNotVisited from NodePoint Class
 * checks if the node marked as not visited (flag = 0)
 */
TEST_F(NodePointTest, SetNotVisitedCheck){
    node->setNotVisited();
    ASSERT_EQ(node->isVisited(), 0);
}
/**
 * the test checks the method initializeFather from NodePoint Class
 * checks if the node's father has been set after initializing
 */
TEST_F(NodePointTest, InitializeFatherCheck){
    node->initializeFather(father);
    ASSERT_TRUE(node->getFather()->getPoint()->equals(father->getPoint()));
}
/**
 * the test checks the method getPoint from NodePoint Class
 * checks the point that the node contain
 */
TEST_F(NodePointTest, GetPointCheck){
    ASSERT_TRUE(node->getPoint()->equals(ptr));
}
/**
 * the test checks the method getFather from NodePoint Class
 * checks the node's father if it equals to the father we initialized.
 */
TEST_F(NodePointTest, GetFatherCheck) {
    node->initializeFather(father);
    ASSERT_TRUE(node->getFather()->getPoint()->equals(father->getPoint()));
}