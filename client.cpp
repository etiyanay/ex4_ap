#include "Udp.h"
#include "Driver.h"
#include "InputProcessing.h"
#include <boost/serialization/export.hpp>
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
    //getting input from console
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
    //getting the cab and diserializing it
    char buffer2[1024];
    CabFactory* matchingCab;
    udp.reciveData(buffer2, sizeof(buffer2));
    string serial_str2 = bufferToString(buffer2, sizeof(buffer2));
    boost::iostreams::basic_array_source<char> device(serial_str2.c_str(), serial_str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> matchingCab;
    //setting the cab to the driver
    newDriver->setCab(matchingCab);
    //endless loop for getting trips and GO advances- till we get "close" from server
    while (1) {
        udp.sendData("wait_for_a_trip");
        //getting the trip and diserializing it
        char buffer3[1024];
        Trip *newTrip;
        udp.reciveData(buffer3, sizeof(buffer3));
        string serial_trip = bufferToString(buffer3, sizeof(buffer3));
        //if we get "close" - we release allocating memory and finish
        if (strcmp(serial_trip.data(), "close") ==0) {
            delete newDriver;
            return 0;
        }
        boost::iostreams::basic_array_source<char> device2(serial_trip.c_str(), serial_trip.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
        boost::archive::binary_iarchive ia2(s3);
        ia2 >> newTrip;
        //setting the trip to the driver
        newDriver->setNewTrip(*newTrip);
        NodePoint *newLocation;
        int sizeOfTrip = newDriver->getTrip().getPath().size();
        //advance the driver to its next location in trip's path
        for (int i = 1; i < sizeOfTrip; ++i) {
            udp.sendData("wait_for_GO");
            //getting driver's new location and diseralizing it
            char newLocationBuffer[1024];
            udp.reciveData(newLocationBuffer, sizeof(newLocationBuffer));
            string serial_location = bufferToString(newLocationBuffer, sizeof(newLocationBuffer));
            if (strcmp(serial_location.data(), "close") ==0) {
                delete newDriver;
                return 0;
            }
            boost::iostreams::basic_array_source<char> device3(serial_location.c_str(), serial_location.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device3);
            boost::archive::binary_iarchive ia3(s4);
            ia3 >> newLocation;
            newDriver->setLocation(newLocation);
            //if the cab is luxury- advance the driver 2 blocks
            if (newDriver->getCab()->getSpeed() == 2)
                i++;
            }
    }
}