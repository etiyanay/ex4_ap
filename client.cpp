#include "Udp.h"
#include "Driver.h"
#include "Point2D.h"
#include "StandardCab.h"
#include "CabFactory.h"
#include "LuxuryCab.h"
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
BOOST_CLASS_EXPORT_GUID(Point,"Point");
BOOST_CLASS_EXPORT_GUID(CabFactory,"CabFactory");


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
    udp.sendData("hello");

    udp.reciveData(buffer, sizeof(buffer));
    cout << "client got: " << buffer << endl;
Point2D* x = new Point2D(2,2);
    Point2D* y = new Point2D(3,3);

    Trip *gp = new Trip(1234,x,y,5,20.5);
    //cout << "the x is: " <<((Point2D*)gp)->getX() << endl;
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << gp;
    s.flush();
    cout << serial_str << endl;
    //creating driver obj and serialize->sendDATA
    //cin >> buffer;

    /* Point2D *gp2;
     boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
     boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
     boost::archive::binary_iarchive ia(s2);
     ia >> gp2;
     cout << "we are printing gp2: "<< gp2<<endl;
 */

    udp.sendData(serial_str);
    //getting the cab -> diserialize
    /*udp.reciveData(buffer, sizeof(buffer));
    //attach the cab to driver in the member
    //CabFactory *newCab = diserializebuffer
    //newDriver.setCab(newCab)
    cout << "client got: " << buffer << endl;*/


    /*Point2D *p = new Point2D(1,1);

    NodePoint *node = new NodePoint(p);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << node;
    s.flush();
    cout << serial_str << endl;
    udp.sendData(serial_str);*/



    //loop trip
    return 0;
}