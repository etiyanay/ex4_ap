#include "Udp.h"
#include "Driver.h"
#include "InputProcessing.h"
#include "Point2D.h"
#include "StandardCab.h"
#include "CabFactory.h"
#include "LuxuryCab.h"
#include "TwoDim.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
#include <boost/array.hpp>
#include <boost/multi_array.hpp>

BOOST_CLASS_EXPORT_GUID(Point,"Point");
BOOST_CLASS_EXPORT_GUID(CabFactory,"CabFactory");

using namespace std;
using namespace boost::archive;

int main(int argc, char *argv[]) {
    Udp udp(argv[1], atoi(argv[2]));
    udp.initialize();
//
    char buffer[1024];
    int idOfDriver, ageOfDriver, experienceOfDriver, idVehicelOfDriver;
    char statusOfDriver, dummy;
    Driver *newDriver;
    //getting input
    cin >> idOfDriver >> dummy >> ageOfDriver >> dummy >> statusOfDriver >> dummy
        >> experienceOfDriver >> dummy >> idVehicelOfDriver;
    //creating driver
    newDriver = new Driver(idOfDriver, ageOfDriver, Marital(statusOfDriver)
            ,experienceOfDriver,idVehicelOfDriver);
    //serializing
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << newDriver;
    s.flush();
    //sending the serialized driver
    udp.sendData(serial_str);

    //getting the cab -> diserialize
    char buffer2[1024];
    CabFactory* matchingCab;
    udp.reciveData(buffer2, sizeof(buffer2));
    string serial_str2 = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str2.c_str(), serial_str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> matchingCab;
    newDriver->setCab(matchingCab);

    while (1) {
        udp.sendData("wait_for_a_trip");
        //getting the trip -> diserialize
        char buffer3[1024];
        Trip *newTrip;
        udp.reciveData(buffer3, sizeof(buffer3));
        string serial_trip = bufferToString(buffer3, sizeof(buffer3));
        if (strcmp(serial_trip.data(), "close") ==0) {
            return 0;
        }
        boost::iostreams::basic_array_source<char> device2(serial_trip.c_str(), serial_trip.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
        boost::archive::binary_iarchive ia2(s3);
        ia2 >> newTrip;
        newDriver->setNewTrip(*newTrip);
        //
        NodePoint *newLocation;
        int sizeOfTrip = newDriver->getTrip().getPath().size();
        for (int i = 1; i < sizeOfTrip; ++i) {
            udp.sendData("wait_for_GO");
            //
            char newLocationBuffer[1024];
            udp.reciveData(newLocationBuffer, sizeof(newLocationBuffer));
            string serial_location = bufferToString(newLocationBuffer, sizeof(newLocationBuffer));
            if (strcmp(serial_location.data(), "close") ==0) {
                return 0;
            }
            boost::iostreams::basic_array_source<char> device3(serial_location.c_str(), serial_location.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device3);
            boost::archive::binary_iarchive ia3(s4);
            ia3 >> newLocation;
            newDriver->setLocation(newLocation);
            if (newDriver->getCab()->getSpeed() == 2)
                i++;
            }
    }
}