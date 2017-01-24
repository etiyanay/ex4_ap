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

bool ifStringIsDouble(string str){
    int strLength = str.length();
    bool flagDot = false;
    if (!isdigit(str[0]))
        return false;
    for (int i = 1; i < strLength; ++i) {
        if (!isdigit(str[i])) {
            if (((str[i]) == '.') && (flagDot == false)) {
                flagDot = true;
            } else {
                return false;
            }
        }
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
int driverInputProcessing(vector<string> &separatedMembers) {
    //check id of driver
    if(!ifStringIsNum(separatedMembers[0].c_str()))
        return -1;
    int id = atoi(separatedMembers[0].c_str());
    if (!ifGreaterThan(id, 0))
        return -1;
    //check age
    if(!ifStringIsNum(separatedMembers[1].c_str()))
        return -1;
    int age = atoi(separatedMembers[1].c_str());
    if (!ifGreaterThan(age, 0))
        return -1;
    //check status
    if((separatedMembers[2].compare("S") != 0) && (separatedMembers[2].compare("M") != 0) &&
       (separatedMembers[2].compare("D") != 0) && (separatedMembers[2].compare("W") != 0))
        return  -1;
    //check experience years
    if(!ifStringIsNum(separatedMembers[3].c_str()))
        return -1;
    int experience = atoi(separatedMembers[3].c_str());
    if (!ifGreaterThan(experience, 0))
        return -1;
    //check id of cab
    if(!ifStringIsNum(separatedMembers[4].c_str()))
        return -1;
    int cabId = atoi(separatedMembers[4].c_str());
    if (!ifGreaterThan(cabId, 0))
        return -1;
    return 0;
}

int gridSizeInputProcessing() {


}

Point* validObstacle(string obstacleStr) {
    //counting how many members that separated by "space"
    int numOfMembers = countMembers(obstacleStr, ',');
    //if there is less/more parameters than supposed to be
    if (numOfMembers != 2) {
        cout << "-1" << endl;
        return NULL;
    }
    vector<string> separatedMembers;
    separatedMembers.resize(numOfMembers);
    separateString(obstacleStr, separatedMembers, ',');
    int xGrid = atoi(separatedMembers[0].c_str());
    int yGrid = atoi(separatedMembers[1].c_str());
    if (!ifGreaterThan(xGrid,0) && !ifGreaterThan(yGrid,0)) {
        cout << "-1" << endl;
        return NULL;
    }
    Point *obs = new Point2D(xGrid, yGrid);
    return obs;
}

Grid* createGridAndObstacles() {
    string xStr, yStr;
    cin >> xStr;
    cin >> yStr;
    if(!ifStringIsNum(xStr) || !ifStringIsNum(yStr)) {
        cout << "-1" << endl;
        return NULL;
    }
    int xGrid = atoi(xStr.c_str());
    int yGrid = atoi(yStr.c_str());
    if (!ifGreaterThan(xGrid,1) || !ifGreaterThan(yGrid,1)) {
        cout << "-1" << endl;
        return NULL;
    }
    //grid is valid, now get the num of obstacles input
    string numOfObstacles;
    cin >> numOfObstacles;
    if(!ifStringIsNum(numOfObstacles)) {
        cout << "-1" << endl;
        return NULL;
    }
    //num of obstacles is valid, check the points
    int obstacles = atoi(numOfObstacles.c_str());
    vector<Point2D> obstaclesVec;
    for (int i = 0; i < obstacles; ++i) {
        string newObstacleStr;
        cin >> newObstacleStr;
        //counting how many members that separated by "space"
        int numOfMembers = countMembers(newObstacleStr, ',');
        //if there is less/more parameters than supposed to be
        if (numOfMembers != 2) {
            cout << "-1" << endl;
            return NULL;
        }
        vector<string> separatedMembers;
        separatedMembers.resize(numOfMembers);
        separateString(newObstacleStr, separatedMembers, ',');
        int xPoint = atoi(separatedMembers[0].c_str());
        int yPoint = atoi(separatedMembers[1].c_str());
        if ((!ifGreaterThan(xPoint, 0) && !ifGreaterThan(yPoint, 0)) ||
                (xPoint >= xGrid) || (yPoint >= yGrid)) {
            cout << "-1" << endl;
            return NULL;
        }
        obstaclesVec.push_back(Point2D(xPoint, yPoint));
    }
    //obstacles are valid, now create the map and initialize the obstacles points
    Grid *map = new TwoDim(xGrid, yGrid);
    Point* obstaclePoint;
    for (int i = 0; i < obstacles; i++) {
        obstaclePoint = new Point2D(obstaclesVec[i]);
        NodePoint *obstacleNodePoint = map->whereIsTheNode(obstaclePoint);
        obstacleNodePoint->setVisited();
        map->pushObstacleToVec(obstacleNodePoint);
        delete obstaclePoint;
    }
    return map;
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
    char buffer2[2048];
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
    //getting the trip from the console
    string tripString;
    cin >> tripString;

    int idOfTrip, xStartTrip, yStartTrip, xEndTrip, yEndTrip, numOfPassengerTrip, clockTimeTrip;
    double tariffTrip;
    //counting how many members that separated by ','
    int numOfMembers = countMembers(tripString, ',');
    if (numOfMembers != 8) {
        cout << "-1" << endl;
        return;
    }
    vector<string> separatedMembers;
    separatedMembers.resize(numOfMembers);
    separateString(tripString, separatedMembers, ',');
    Point* mapSize = station->getMapSize();
    int isValid = tripInputProcessing(separatedMembers, mapSize);
    if (isValid == -1) {
        cout << "-1" << endl;
        delete mapSize;
        return;
    }
    Point *source, *destination;
    Point2D p2DStart, p2DEnd;
    Trip newTrip;
    //the input is valid
    idOfTrip = atoi(separatedMembers[0].c_str());
    xStartTrip = atoi(separatedMembers[1].c_str());
    yStartTrip = atoi(separatedMembers[2].c_str());
    xEndTrip = atoi(separatedMembers[3].c_str());
    yEndTrip = atoi(separatedMembers[4].c_str());
    numOfPassengerTrip = atoi(separatedMembers[5].c_str());
    tariffTrip = atof(separatedMembers[6].c_str());
    clockTimeTrip = atoi(separatedMembers[7].c_str());
    p2DStart = Point2D(xStartTrip, yStartTrip);
    p2DEnd = Point2D(xEndTrip, yEndTrip);
    source = &p2DStart;
    destination = &p2DEnd;
    //creating new trip
    newTrip = Trip(idOfTrip, source, destination, numOfPassengerTrip, tariffTrip, clockTimeTrip);
    //adding the trip to the taxi center
    station->addNewTrip(newTrip);
}


int tripInputProcessing(vector<string> &separatedMembers, Point* mapSize) {
    //check id
    int vecSize = separatedMembers.size();
    for (int i = 0; i < vecSize-2; ++i) {
        if(!ifStringIsNum(separatedMembers[i].c_str()))
            return -1;
    }
    if (!ifStringIsDouble(separatedMembers[6].c_str())) {
        return -1;
    }
    if(!ifStringIsNum(separatedMembers[7].c_str()))
        return -1;
    int id = atoi(separatedMembers[0].c_str());
    int mapSizeX = ((Point2D*)mapSize)->getX();
    int mapSizeY = ((Point2D*)mapSize)->getY();
    int startTripX = atoi(separatedMembers[1].c_str());
    int startTripY = atoi(separatedMembers[2].c_str());
    int endTripX = atoi(separatedMembers[3].c_str());
    int endTripY = atoi(separatedMembers[4].c_str());
    int numOfPassengers = atoi(separatedMembers[5].c_str());
    double tarrif = atof(separatedMembers[6].c_str());
    int time =  atoi(separatedMembers[7].c_str());

    if (!ifGreaterThan(id, 0)) {
        return -1;
    }
    if ((startTripX >= mapSizeX) || (endTripX >= mapSizeX)) {
        return -1;
    }
    if ((startTripY >= mapSizeY) || (endTripY >= mapSizeY)) {
        return -1;
    }
    if ((!ifGreaterThan(startTripX, 0)) || (!ifGreaterThan(endTripX, 0))
        || (!ifGreaterThan(startTripY, 0)) || (!ifGreaterThan(endTripY, 0))) {
        return -1;
    }
    if (!ifGreaterThan(numOfPassengers, 1)) {
        return -1;
    }
    if (!(tarrif >= 0.0)) {
        return -1;
    }
    if (!ifGreaterThan(time, 1)) {
        return -1;
    }
    return 0;
}

int getNumOfClients() {
    string numOfDriversStr;
    cin >> numOfDriversStr;
    if(!ifStringIsNum(numOfDriversStr.c_str()))
        return -1;
    int numOfDrivers = atoi(numOfDriversStr.c_str());
    if (!ifGreaterThan(numOfDrivers, 1))
        return -1;
    return numOfDrivers;
}

void insertCab(TaxiCenter* station) {
    string cabString;
    cin >> cabString;
    int idOfCab, typeOfCab;
    char manufacturerOfCab, colorOfCab;
    CabFactory* newCab;
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
    string idOfDriverStr;
    cin >> idOfDriverStr;
    if(!ifStringIsNum(idOfDriverStr.c_str())) {
        cout << "-1" << endl;
        return;
    }
    int idOfDriver = atoi(idOfDriverStr.c_str());
    if (!ifGreaterThan(idOfDriver, 0)) {
        cout << "-1" << endl;
        return;
    }
    Point* driverLocation = station->findDriverLocationById(idOfDriver);
    if (NULL == driverLocation) {
        cout << "-1" << endl;
        return;
    }
    cout << driverLocation << endl;
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
                numOfDrivers = getNumOfClients();
                if (numOfDrivers == -1) {
                    cout << "-1" << endl;
                    return;
                }
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
                cout << "-1" << endl;
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
                //closing client and update counter
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