/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <vector>
using namespace std;

class Flights
{
	private:
	int flight_count;
	vector <Flight> flight_collection;

	public:
	Flights();
	void set_flight_count(int count);
	int get_flight_count();
	void Load_flight();
	void Store_flight();
	void Add_flight(Flight flight, Planes* planes, CrewMembers* crew_members);
	void Edit_flight(string flight_ID, Planes* planes, CrewMembers* crew_members);
	void Delete_flight(string flight_ID, Planes* planes, CrewMembers* members);
	void Search_flight();
	void Print_flight(string flight_ID);
	void Print_flights();
	void Print_schedule_plane(string plane_ID, Planes planes);
	void Print_schedule_crew(int member_ID, CrewMembers crew_members);
	void Update_flight();
	void Delete_inactive_flight(Planes* planes, CrewMembers* members);
};