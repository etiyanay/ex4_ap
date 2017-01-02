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
    std::cout << "Hello, from client" << std::endl;

    cout << argv[2] << endl;
    Udp udp(argv[1], atoi(argv[2]));
    udp.initialize();

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


    /*udp.reciveData(buffer, sizeof(buffer));
    //attach the cab to driver in the member
    //CabFactory *newCab = diserializebuffer
    //newDriver.setCab(newCab)
    cout << "client got: " << buffer << endl;*/

    /*CabFactory* matchingCab;
    matchingCab = new StandardCab(1,FIAT, WHITE);
    //serializing
    std::string serial_str2;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str2);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << matchingCab;
    s.flush();
    //sending the serialized cab
    udp.sendData(serial_str2);*/

    /*char buffer2[1024];
    udp.reciveData(buffer2, sizeof(buffer2));
    string serial_str = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> matchingCab;
    //newDriver->setCab(matchingCab);
    cout<< matchingCab->getID()<<endl;*/



    //loop trip
    return 0;
}