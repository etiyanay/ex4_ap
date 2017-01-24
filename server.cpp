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
    Grid *map = createGridAndObstacles();
    while (NULL == map)
        map = createGridAndObstacles();
    Bfs currentBfs(map);
    TaxiCenter* station = new TaxiCenter(map, &currentBfs);
    //running menu
    while (1) {
        menu(station, tcp);
    }
}