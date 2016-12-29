#include <iostream>
#include <algorithm>
#include "TwoDim.h"
#include "Bfs.h"
#include "InputProcessing.h"
#include "Passenger.h"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    /*Point2D p1(1,2);
    Point2D p2(3,4);
    Point* p3 = &p1;
    Point* p4 = &p2;
    Passenger pass(p3,p4);
    pass.getSourcePoint()->print();
    pass.getDestinationPoint()->print();
    if(p3->equals(pass.getSourcePoint()))
        cout << "im a genius" << endl;*/




   /*string input;
    getline(cin, input);
    //parse the input for 3 strings, separated by ','
    string* inputForBfs = stringPoints(input);
    //counting how many '_' we have to determine what dimension it is
    int dimType = countDimension(inputForBfs[0]);
    Grid* dim;
    Point* startPoint;
    Point* destinationPoint;
    //if the dimension is 2D
    if (dimType == 2) {
        dim = convertToGrid(inputForBfs[0]);
        startPoint = convertToPoint(inputForBfs[1]);
        destinationPoint = convertToPoint(inputForBfs[2]);
    }
    //initializing the bfs
    Bfs b = Bfs(dim, startPoint, destinationPoint);
    vector<NodePoint*> path = b.runBfs();
    for (int j = 0; j < path.size(); ++j) {
        //printing point2D
        cout<<path[j]->getPoint()<<endl;
    }
    delete startPoint;
    delete destinationPoint;
    delete dim;*/

    return 0;
}
