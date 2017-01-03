#include <iostream>
#include "TwoDim.h"
#include "Bfs.h"
#include "InputProcessing.h"
#include "Udp.h"


using namespace std;

int main(int argc, char* argv[]) {
    //server commands
    Socket* udp = new Udp(1, atoi(argv[1]));
    udp->initialize();
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
        menu(station, udp);
    }
}