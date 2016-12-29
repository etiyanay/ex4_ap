#include "gtest/gtest.h"
#include "../TwoDim.h"
#include "../Point2D.h"
#include "../Bfs.h"
#include "../NodePoint.h"
#include "vector"

using namespace std;
/**
 * this is a test class for the class Bfs
 */
class BfsTest : public ::testing::Test {
protected:
    Bfs *currentBfs;
    Point2D source, destination, p2;
    Point *ptrSource, *ptrDestination, *p3;
    Grid* map;
    NodePoint* nodeDestination;
    virtual void SetUp(){
        ptrSource = new Point2D(1,1);
        ptrDestination = new Point2D(3,3);
        p2 = Point2D(1,3);
        map = new TwoDim(4,4);
        currentBfs = new Bfs(map);
    }
    virtual void TearDown(){
        delete currentBfs;
        delete ptrSource;
        delete ptrDestination;
    }
public:
    BfsTest() {}
};
/**
 * the test checks the method bfsAlgorithm from Bfs Class
 * checks the point of the node that the algorithm returns- equals to the destination point above
 */
TEST_F(BfsTest, bfsAlgorithmCheck){
    nodeDestination = currentBfs->bfsAlgorithm(ptrSource, ptrDestination);
    EXPECT_TRUE(nodeDestination->getPoint()->equals(ptrDestination));
    EXPECT_FALSE(nodeDestination->getPoint()->equals(&p2));
}
/**
 * the test checks the method runBfs from Bfs Class
 * checks the path to the destination, equal to the points above
 */
TEST_F(BfsTest, runBfsCheck){
    vector<NodePoint*> vecNodes = currentBfs->runBfs(ptrSource, ptrDestination);
    p3 = vecNodes[0]->getPoint();
    EXPECT_TRUE(p3->equals(ptrSource));
    p3 = vecNodes[vecNodes.size()-1]->getPoint();
    EXPECT_TRUE(p3->equals(ptrDestination));
    p3 = vecNodes[2]->getPoint();
    EXPECT_TRUE(p3->equals(&p2));

}