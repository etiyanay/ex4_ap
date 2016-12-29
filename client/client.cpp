#include "Udp.h"
#include "Driver.h"
#include "Point2D.h"
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
using namespace std;
using namespace boost::archive;

int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    /*int idOfDriver, ageOfDriver, experienceOfDriver, idVehicelOfDriver;
    char statusOfDriver, dummy;
    Driver newDriver;
    //getting input
    cin >> idOfDriver >> dummy >> ageOfDriver >> dummy >> statusOfDriver >> dummy
        >> experienceOfDriver >> dummy >> idVehicelOfDriver;
    //creating driver
    newDriver = Driver(idOfDriver, ageOfDriver, Marital(statusOfDriver)
            ,experienceOfDriver,idVehicelOfDriver);*/
    //serializing
    Point2D *gp = new Point2D(1,1);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << gp;
    s.flush();
    cout << serial_str << endl;

    //creating driver obj and serialize->sendDATA
    //cin >> buffer;
    udp.sendData(serial_str);
    //getting the cab -> diserialize
    udp.reciveData(buffer, sizeof(buffer));
    //attach the cab to driver in the member
    //CabFactory *newCab = diserializebuffer
    //newDriver.setCab(newCab)
    cout << "client got: " << buffer << endl;



//loop trip
    return 0;
}