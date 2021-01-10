main: main.o Plane.o Planes.o CrewMember.o CrewMembers.o Flight.o Flights.o
	g++ main.o Plane.o Planes.o CrewMember.o CrewMembers.o Flight.o Flights.o -o main

main.o: main.cpp Plane.h Planes.h CrewMember.h CrewMembers.h Flight.h Flights.h
	g++ -c main.cpp

Plane.o: Plane.cpp Plane.h
	g++ -c Plane.cpp

Planes.o: Planes.cpp Plane.h Planes.h
	g++ -c Planes.cpp

CrewMember.o: CrewMember.cpp CrewMember.h
	g++ -c CrewMember.cpp

CrewMembers.o: CrewMembers.cpp CrewMember.h CrewMembers.h
	g++ -c CrewMembers.cpp

Flight.o: Flight.cpp Flight.h
	g++ -c Flight.cpp

Flights.o: Flights.cpp Plane.h Planes.h CrewMember.h CrewMembers.h Flight.h Flights.h
	g++ -c Flights.cpp

clean:
	rm *.o main