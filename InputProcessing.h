#ifndef AP_EX1_INPUTPROCESSING_H
#define AP_EX1_INPUTPROCESSING_H

#include <iostream>
#include <algorithm>
#include "TwoDim.h"
#include "Point2D.h"
#include "NodePoint.h"
#include "Bfs.h"
#include "TaxiCenter.h"
#include "Socket.h"

//this header declares about the helping funcs in the main- that process the inputs and the menu

/**
 * the func operates the menu and is called from the main
 * @param station the taxi center
 */
void menu(TaxiCenter* station, Socket* udp);
/**
 * the func calls the method "addNewDriver" from the TaxiCenter Classs
 * @param station the taxi center
 */
void insertDriver(TaxiCenter* station, Socket* udp, int newClientSd, int index);
/**
 * the func calls the method "addNewTrip" from the TaxiCenter Classs
 * @param station the taxi center
 */
void insertTrip(TaxiCenter* station);
/**
 * the func calls the method "addNewCab" from the TaxiCenter Classs
 * @param station the taxi center
 */
void insertCab(TaxiCenter* station);
/**
 * the func calls the method "findDriverLocationById" from the TaxiCenter Class and prints
 * the point of the driver's location
 * @param station the taxi center
 */
void driverLocationRequest(TaxiCenter* station);
/**
 * the func get the obstacles points, process them and update the map
 * @param map the map to update about the obstacles
 */
void createObstacles(Grid* map, TaxiCenter* station);
/**
 * @param buffer the buffer to convert to a string
 * @param bufflen the length of the buffer
 * @return a new string
 */
string bufferToString(char* buffer, int bufflen);
/**
 * that func is sent to a new thread. the thread is in charge of the connection with a client
 * and inserts a new driver and send/recieve locations.
 * @param element get ClientData Struct
 * @return void
 */
void *manageClient(void* element);
/**
 * the struct to sent to a thread
 */
struct ClientData {
    TaxiCenter* station;
    Socket *tcp;
    int clientSd;
    int index;
};

#endif //AP_EX1_INPUTPROCESSING_H