#include <iostream>
#include <algorithm>
#include "TwoDim.h"
#include "Point2D.h"
#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "InputProcessing.h"
#include <boost/serialization/export.hpp>

using namespace std;
using namespace boost::archive;

vector <pthread_t> clientsThreads;
pthread_mutex_t finishMutex, closeThreadMutex;
int numOfClientsThreads = 0;
int extension;
int count9extension = 0;
int threadsFinish = 0;
bool mutexInit = false;
int numOfDrivers =0;
int ifAllSocketsClosed = 0;

void separateString(string input, vector<string> &separatedStrings, char separator) {
    int index = 0, found;
    //separate the string by ','
    while (input != "\0") {
        found = input.find(separator);
        if (found == -1) {
            separatedStrings[index] = input;
            break;
        }
        separatedStrings[index] = input.substr(0, found);
        input.erase(0, found + 1);
        index++;
    }
}
int countMembers(string inputOfPoint, char separator) {
    int count = 0, i;
    for (i = 0; i < inputOfPoint.size(); i++)
        if (inputOfPoint[i] == separator) count++;
    return (count + 1);
}

bool ifGreaterThan(int num, int lowerBound) {
    if (num >= lowerBound)
        return true;
    else
        return false;
}

bool ifStringIsNum(string str){
    int strLength = str.length();
    for (int i = 0; i < strLength; ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

int cabInputProcessing(vector<string> &separatedMembers) {

    //check id
    if(!ifStringIsNum(separatedMembers[0].c_str()))
        return -1;
    int id = atoi(separatedMembers[0].c_str());
    if (!ifGreaterThan(id, 0))
        return -1;
    //check type of cab if 1 or 2
    if((separatedMembers[1].compare("1") != 0) && (separatedMembers[1].compare("2") != 0))
        return  -1;
    //check manufacturer
    if((separatedMembers[2].compare("H") != 0) && (separatedMembers[2].compare("T") != 0) &&
            (separatedMembers[2].compare("S") != 0) && (separatedMembers[2].compare("F") != 0))
        return  -1;
    if((separatedMembers[3].compare("R") != 0) && (separatedMembers[3].compare("B") != 0) &&
       (separatedMembers[3].compare("G") != 0) && (separatedMembers[3].compare("P") != 0) &&
            (separatedMembers[3].compare("W") != 0))
        return  -1;
    return 0;
}

void createObstacles(Grid* map) {
    int numOfObstacles, xObstacle, yObstacle;
    char dummy;
    cin >> numOfObstacles;
    Point *obstacle;
    for (int i = 0; i < numOfObstacles; i++) {
        cin >> xObstacle >> dummy >> yObstacle;;
        obstacle = new Point2D(xObstacle, yObstacle);
        NodePoint *obstacleNodePoint = map->whereIsTheNode(obstacle);
        obstacleNodePoint->setVisited();
        delete obstacle;
    }
}
string bufferToString(char* buffer, int bufflen)
{
    string ret(buffer, bufflen);
    return ret;
}

void createObstacles(Grid* map, TaxiCenter* station) {
    int numOfObstacles, xObstacle, yObstacle;
    char dummy;
    cin >> numOfObstacles;
    Point *obstacle;
    for (int i = 0; i < numOfObstacles; i++) {
        cin >> xObstacle >> dummy >> yObstacle;;
        obstacle = new Point2D(xObstacle, yObstacle);
        NodePoint * obstacleNodePoint = map->whereIsTheNode(obstacle);
        station->pushObstacleToMap(obstacleNodePoint);
        //obstacleNodePoint->setVisited();
        delete obstacle;
    }
}
void insertDriver(TaxiCenter* station, Socket* tcp, int newClientSd) {
    //getting driver from client and diseralizing it
    Driver *newDriver;
    char buffer2[8096];
    tcp->reciveData(buffer2, sizeof(buffer2), newClientSd);
    string serial_str = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> newDriver;
    //adding the driver to the taxi center
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
    tcp->sendData(serial_str2, newClientSd);
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
        >> yEndTrip >> dummy >> numOfPassengerTrip >> dummy >> tariffTrip
        >> dummy >> clockTimeTrip;
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
    string cabString;
    cin >> cabString;

    int idOfCab, typeOfCab;
    char manufacturerOfCab, colorOfCab, dummy;
    CabFactory* newCab;
    //getting the cab from console
    //create vector -> resize ->
    //counting how many members that separated by ','
    int numOfMembers = countMembers(cabString, ',');
    //if there is less/more parameters than supposed to be
    if (numOfMembers != 4) {
        cout << "-1" << endl;
        return;
    }
    vector<string> separatedMembers;
    separatedMembers.resize(numOfMembers);
    separateString(cabString, separatedMembers, ',');
    int isValid = cabInputProcessing(separatedMembers);
    if (isValid == -1) {
        cout << "-1" << endl;
        return;
    }
    //the input is valid
    idOfCab = atoi(separatedMembers[0].c_str());
    typeOfCab = atoi(separatedMembers[1].c_str());
    manufacturerOfCab = separatedMembers[2][0];
    colorOfCab = separatedMembers[3][0];
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
void menu(TaxiCenter* station, Socket* tcp) {
    int status;
    if (threadsFinish == numOfDrivers*count9extension) {
        cin >> extension;
        if (extension == 9)
            count9extension++;
        switch (extension) {
            case 1:
                //initializing the mutex once!
                if (mutexInit == false) {
                    pthread_mutex_init(&finishMutex,0);
                    pthread_mutex_init(&closeThreadMutex,0);
                    mutexInit = true;
                }
                //getting num of drivers that we are going to get from clients
                cin >> numOfDrivers;
                for (int i = 0; i < numOfDrivers; ++i) {
                    //"hand shake" with a new client and saving its socket descriptor
                    int newClientSd = tcp->tcpAccept();
                    station->setNewClientSd(newClientSd);
                    insertDriver(station, tcp, newClientSd);
                }
                //increasing the vector to contain the threads we are going to get
                clientsThreads.resize(numOfDrivers);
                for (int j = 0; j < numOfDrivers; ++j) {
                    //creating a clientData Struct to send to the thread
                    ClientData *newClient = new ClientData();
                    newClient->clientSd = station->getNewClientSd(j);
                    newClient->station = station;
                    newClient->tcp = tcp;
                    newClient->index = j;
                    //create new thread to manage a client
                    status = pthread_create(&(clientsThreads[j]), NULL, manageClient,
                                            (void *) newClient);
                    if (status)
                        exit(0);
                }
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
                break;
            case 7:
                while (1) {
                    //check if all the threads finish closing
                    if (ifAllSocketsClosed == numOfDrivers) {
                        delete tcp;
                        delete station;
                        pthread_mutex_destroy(&closeThreadMutex);
                        pthread_mutex_destroy(&finishMutex);
                        exit(0);
                    }
                }
            default:
                break;
        }
    }
}

void *manageClient(void* element) {
    ClientData *data = (ClientData*)element;
    int stepsCounter = 0;
    while (1) {
        switch (extension) {
            case 9:
                //check if the thread already advanced the client
                if (stepsCounter + 1 == count9extension) {
                    data->station->moveDriverOneStep(data->tcp, data->index);
                    stepsCounter++;
                    pthread_mutex_lock(&finishMutex);
                    threadsFinish++;
                    pthread_mutex_unlock(&finishMutex);
                }
                break;
            case 7:
                data->tcp->sendData("close", data->clientSd);
                pthread_mutex_lock(&closeThreadMutex);
                ifAllSocketsClosed++;
                pthread_mutex_unlock(&closeThreadMutex);
                pthread_exit(NULL);
                break;
            default:
                break;
        }
    }
}