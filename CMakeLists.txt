cmake_minimum_required(VERSION 3.3)
project(ap_ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

set(SOURCE_FILES Grid.cpp Grid.h NodePoint.cpp NodePoint.h Point.cpp Point.h Point2D.cpp Point2D.h TwoDim.cpp
        TwoDim.h Bfs.cpp Bfs.h InputProcessing.cpp InputProcessing.h Passenger.cpp Passenger.h Trip.cpp Trip.h
        CabFactory.cpp CabFactory.h StandardCab.cpp StandardCab.h
        LuxuryCab.cpp LuxuryCab.h Driver.cpp Driver.h TaxiCenter.cpp TaxiCenter.h
        Socket.cpp Socket.h Tcp.cpp Tcp.h Clock.cpp Clock.h ThreadPool.cpp ThreadPool.h Job.cpp Job.h)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

add_executable(server server.cpp ${SOURCE_FILES})
add_executable(client client.cpp ${SOURCE_FILES})

target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})

