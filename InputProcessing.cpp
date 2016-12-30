#include <iostream>
#include <algorithm>
#include "TwoDim.h"
#include "Point2D.h"
#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Socket.h"
#include "Trip.h"
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
#include <boost/serialization/export.hpp>


using namespace std;
using namespace boost::archive;

string bufferToString(char* buffer, int bufflen)
{
    string ret(buffer, bufflen);

    return ret;
}
string* stringPoints(string input) {
    string* strPtr = new string[3];
    int index = 0, found;
    //separate the string by ','
    while (input != "\0") {
        found = input.find(',');
        if (found == -1) {
            strPtr[index] = input;
            break;
        }
        strPtr[index] = input.substr(0, found);
        input.erase(0, found + 1);
        index++;
    }
    return  strPtr;
}
int countDimension(string inputOfPoint) {
    int count = 0, i;
    for (i = 0; i < inputOfPoint.size(); i++)
        if (inputOfPoint[i] == '_') count++;
    return (count + 1);
}
void createObstacles(Grid* map) {
    int numOfObstacles, xObstacle, yObstacle;
    char dummy;
    cin >> numOfObstacles;
    Point *obstacle;
    for (int i = 0; i < numOfObstacles; i++) {
        cin >> xObstacle >> dummy >> yObstacle;;
        obstacle = new Point2D(xObstacle, yObstacle);
        NodePoint * obstacleNodePoint = map->whereIsTheNode(obstacle);
        obstacleNodePoint->setVisited();
        delete obstacle;
    }
}
void insertDriver(TaxiCenter* station, Socket* udp) {
    Driver *newDriver;
    char buffer2[1024];
    udp->reciveData(buffer2, sizeof(buffer2));
    string serial_str = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> newDriver;
    station->addNewDriver(*newDriver);
}
void insertTrip(TaxiCenter* station) {
    int idOfTrip, xStartTrip, yStartTrip, xEndTrip, yEndTrip, numOfPassengerTrip;
    double tariffTrip;
    char dummy;
    Point *source, *destination;
    Point2D p2DStart, p2DEnd;
    Trip newTrip;
    cin >> idOfTrip >> dummy >> xStartTrip >> dummy >> yStartTrip >> dummy >> xEndTrip >> dummy
        >> yEndTrip >> dummy >> numOfPassengerTrip >> dummy >> tariffTrip;
    p2DStart = Point2D(xStartTrip, yStartTrip);
    p2DEnd = Point2D(xEndTrip, yEndTrip);
    source = &p2DStart;
    destination = &p2DEnd;
    //creating new trip
    newTrip = Trip(idOfTrip, source, destination, numOfPassengerTrip, tariffTrip);
    //adding the trip to the taxi center
    station->addNewTrip(newTrip);
}
void insertCab(TaxiCenter* station) {
    int idOfCab, typeOfCab;
    char manufacturerOfCab, colorOfCab, dummy;
    CabFactory* newCab;
    cin >> idOfCab >> dummy >> typeOfCab >> dummy >> manufacturerOfCab >> dummy >> colorOfCab;
    if (typeOfCab == 1) {
        newCab = new StandardCab(idOfCab, Manufacturer(manufacturerOfCab),
                                 Color(colorOfCab));
    } else {
        newCab = new LuxuryCab(idOfCab, Manufacturer(manufacturerOfCab),
                               Color(colorOfCab));
    }
    station->addNewCab(newCab);
}
void driverLocationRequest(TaxiCenter* station) {
    int idOfDriver;
    cin >> idOfDriver;
    cout << station->findDriverLocationById(idOfDriver) << endl;
}
void menu(TaxiCenter* station, Socket* udp) {
    int extension;
    cin >> extension;
    switch (extension) {
        case 1:
            insertDriver(station, udp);
            break;
        case 2:
            insertTrip(station);
            break;
        case 3:
            insertCab(station);
            break;
        case 4:
            driverLocationRequest(station);
            break;
        case 6:
            station->assignTripsToDrivers();
            station->startDriving();
            break;
        case 7:
            udp->closeData();

            delete station;
            exit(0);
        default:
            break;
    }
}