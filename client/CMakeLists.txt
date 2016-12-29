cmake_minimum_required(VERSION 3.3)
project(ap_ex1)


SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(core_sockets Socket.cpp Udp.cpp)
add_library(sockets ${core_sockets})




set(SOURCE_FILES server.cpp Grid.cpp Grid.h NodePoint.cpp NodePoint.h Point.cpp Point.h Point2D.cpp Point2D.h TwoDim.cpp
        TwoDim.h Bfs.cpp Bfs.h InputProcessing.cpp InputProcessing.h Passenger.cpp Passenger.h Trip.cpp Trip.h
        CabFactory.cpp CabFactory.h StandardCab.cpp StandardCab.h
        LuxuryCab.cpp LuxuryCab.h Driver.cpp Driver.h TaxiCenter.cpp TaxiCenter.h
        client.cpp Socket.cpp Socket.h Udp.cpp Udp.h)

#add_executable(ap_ex1 ${SOURCE_FILES})
#target_link_libraries(ap_ex1 gtest gtest_main ${Boost_LIBRARIES})

add_executable(server ${SOURCE_FILES} server.cpp)
add_executable(client ${SOURCE_FILES} client.cpp)

target_link_libraries(server sockets ${Boost_LIBRARIES})
target_link_libraries(client sockets ${Boost_LIBRARIES})