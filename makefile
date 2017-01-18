
all: server client

COMMON_SOURCES = src/Grid.cpp src/NodePoint.cpp src/Point.cpp src/Point2D.cpp src/TwoDim.cpp src/Bfs.cpp src/InputProcessing.cpp src/Passenger.cpp src/Trip.cpp src/CabFactory.cpp src/StandardCab.cpp src/LuxuryCab.cpp src/Driver.cpp src/TaxiCenter.cpp src/Socket.cpp src/Tcp.cpp src/Clock.cpp
server:
	g++ -std=c++0x src/server.cpp $(COMMON_SOURCES) -pthread -lboost_serialization -I. -o server.out
client:
	g++ -std=c++0x src/client.cpp $(COMMON_SOURCES) -pthread -lboost_serialization -I. -o client.out
