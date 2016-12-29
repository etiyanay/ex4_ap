a.out: main.o Bfs.o Grid.o InputProcessing.o NodePoint.o Point.o Point2D.o TwoDim.o CabFactory.o 	Driver.o LuxuryCab.o Passenger.o StandardCab.o TaxiCenter.o Trip.o
	g++ main.o Bfs.o Grid.o InputProcessing.o NodePoint.o Point.o Point2D.o TwoDim.o 		CabFactory.o Driver.o LuxuryCab.o Passenger.o StandardCab.o TaxiCenter.o Trip.o

main.o: main.cpp
	g++ -c main.cpp

Bfs.o: Bfs.cpp Bfs.h
	g++ -c Bfs.cpp

Grid.o: Grid.cpp Grid.h
	g++ -c Grid.cpp

InputProcessing.o: InputProcessing.cpp InputProcessing.h
	g++ -c InputProcessing.cpp

NodePoint.o: NodePoint.cpp NodePoint.h
	g++ -c NodePoint.cpp

Point.o: Point.cpp Point.h
	g++ -c Point.cpp

Point2D.o: Point2D.cpp Point2D.h
	g++ -c Point2D.cpp

TwoDim.o: TwoDim.cpp TwoDim.h
	g++ -c TwoDim.cpp

CabFactory.o: CabFactory.cpp CabFactory.h
	g++ -c CabFactory.cpp

Driver.o: Driver.cpp Driver.h
	g++ -c Driver.cpp

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h
	g++ -c LuxuryCab.cpp

Passenger.o: Passenger.cpp Passenger.h
	g++ -c Passenger.cpp

StandardCab.o: StandardCab.cpp StandardCab.h
	g++ -c StandardCab.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h
	g++ -c TaxiCenter.cpp

Trip.o: Trip.cpp Trip.h
	g++ -c Trip.cpp

