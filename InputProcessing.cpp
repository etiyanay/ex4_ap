#include <iostream>
#include <algorithm>
#include "TwoDim.h"
#include "Point2D.h"
#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
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
    //getting driver from client and diseralizing it
    Driver *newDriver;
    char buffer2[1024];
    udp->reciveData(buffer2, sizeof(buffer2));
    string serial_str = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> newDriver;
    //addind the driver to the taxi center
    station->addNewDriver(*newDriver);
    //sending matching cab to client
    CabFactory* matchingCab;
    matchingCab = station->findCabById(newDriver->getCabId());
    //serializing
    string serial_str2;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str2);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << matchingCab;
    s.flush();
    //sending the serialized cab to the client
    udp->sendData(serial_str2);
}
void insertTrip(TaxiCenter* station) {
    int idOfTrip, xStartTrip, yStartTrip, xEndTrip, yEndTrip, numOfPassengerTrip, clockTimeTrip;
    double tariffTrip;
    char dummy;
    Point *source, *destination;
    Point2D p2DStart, p2DEnd;
    Trip newTrip;
    //getting the trip from the console
    cin >> idOfTrip >> dummy >> xStartTrip >> dummy >> yStartTrip >> dummy >> xEndTrip >> dummy
        >> yEndTrip >> dummy >> numOfPassengerTrip >> dummy >> tariffTrip >> dummy >> clockTimeTrip;
    p2DStart = Point2D(xStartTrip, yStartTrip);
    p2DEnd = Point2D(xEndTrip, yEndTrip);
    source = &p2DStart;
    destination = &p2DEnd;
    //creating new trip
    newTrip = Trip(idOfTrip, source, destination, numOfPassengerTrip, tariffTrip, clockTimeTrip);
    //adding the trip to the taxi center
    station->addNewTrip(newTrip);
}
void insertCab(TaxiCenter* station) {
    int idOfCab, typeOfCab;
    char manufacturerOfCab, colorOfCab, dummy;
    CabFactory* newCab;
    //getting the cab from console
    cin >> idOfCab >> dummy >> typeOfCab >> dummy >> manufacturerOfCab >> dummy >> colorOfCab;
    if (typeOfCab == 1) {
        newCab = new StandardCab(idOfCab, Manufacturer(manufacturerOfCab),
                                 Color(colorOfCab));
    } else {
        newCab = new LuxuryCab(idOfCab, Manufacturer(manufacturerOfCab),
                               Color(colorOfCab));
    }
    //adding it
    station->addNewCab(newCab);
}
void driverLocationRequest(TaxiCenter* station) {
    int idOfDriver;
    cin >> idOfDriver;
    cout << station->findDriverLocationById(idOfDriver) << endl;
}
void menu(TaxiCenter* station, Socket* udp) {
    int extension, numOfDrivers;
    cin >> extension;
    switch (extension) {
        case 1:
            //getting num of drivers that we are going to get from clients
            cin >> numOfDrivers;
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
        case 9:
            station->advanceTime();
            station->moveAllDriversOneStep(udp);
            break;
        case 7:
            //telling the clients to shutdown themselves
            udp->sendData("close");
            udp->closeData();
            delete udp;
            delete station;
            exit(0);
        default:
            break;
    }
}