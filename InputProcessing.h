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
 * @param input is the input from the user, "sizeX_sizeY,startX_startY,endX,endY"
 * @return a pointer to a string arr which contains the 3 three points as strings
 */
string* stringPoints(string input);
/**
 * @param inputOfPoint is the dim size as a string
 * @return the ammount of '_' which determine the dim of the grid +1
 * the dim will be the ammount of '_' + 1.
 */
int countDimension(string inputOfPoint);
/**
 * the func operates the menu and is called from the main
 * @param station the taxi center
 */
void menu(TaxiCenter* station, Socket* udp);
/**
 * the func calls the method "addNewDriver" from the TaxiCenter Classs
 * @param station the taxi center
 */
void insertDriver(TaxiCenter* station, Socket* udp);
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
void createObstacles(Grid* map);

#endif //AP_EX1_INPUTPROCESSING_H