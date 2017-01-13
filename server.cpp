#include <iostream>
#include "TwoDim.h"
#include "Bfs.h"
#include "InputProcessing.h"
#include "Tcp.h"
//#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[]) {
    //server commands
    Socket* tcp = new Tcp(1, atoi(argv[1]));
    tcp->initialize();
    //initialize taxi center
    int xGrid, yGrid;
    cin >> xGrid >> yGrid;
    Grid *map = new TwoDim(xGrid, yGrid);
    Bfs currentBfs(map);
    TaxiCenter* station = new TaxiCenter(map, &currentBfs);
    //initializing obstacles
    createObstacles(map);
    //running menu
    while (1) {
        menu(station, tcp);
    }
}