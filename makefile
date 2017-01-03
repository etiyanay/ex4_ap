
all: server client

COMMON_SOURCES = Grid.cpp NodePoint.cpp Point.cpp Point2D.cpp TwoDim.cpp Bfs.cpp InputProcessing.cpp Passenger.cpp Trip.cpp CabFactory.cpp StandardCab.cpp LuxuryCab.cpp Driver.cpp TaxiCenter.cpp Socket.cpp Udp.cpp Clock.cpp
server:
	g++ -std=c++0x server.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out
client:
	g++ -std=c++0x client.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o client.out
