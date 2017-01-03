#include <iostream>
#include "TwoDim.h"
#include "Bfs.h"
#include "InputProcessing.h"
#include "Passenger.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Udp.h"
#include <unistd.h>
//#include <gtest/gtest.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/access.hpp>


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