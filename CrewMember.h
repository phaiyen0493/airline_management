/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class CrewMember
{
	private:
	string name;
	int ID;
	string type;
	string status;
	vector <pair <time_t, time_t> > time_slot ;

	public:
	void set_name(string name);
	string get_name();
	void set_ID(int ID);
	int get_ID();
	void set_type(string type);
	string get_type();
	void set_status(string status);
	string get_status();
	void add_time_slot( time_t start, time_t end);
	void delete_time_slot();
	void delete_time_slot(int i);
	vector <pair <time_t, time_t> > get_time_slot_vector();
	void sort_time_slot();

	virtual void PrintInfo();
};

class Pilot: public CrewMember
{
	private:
	char* rating_code;
	time_t flight_time;

	public:
	Pilot();
	void set_rating_code(char* code);
	char* get_rating_code();
	void set_cum_flight_time(time_t seconds);
	time_t get_cum_flight_time();
	void PrintInfo();
};

class CoPilot: public CrewMember
{
	private:
	char* rating_code;
	time_t flight_time;

	public:
	CoPilot();
	void set_rating_code(char* code);
	char* get_rating_code();
	void set_cum_flight_time(time_t seconds);
	time_t get_cum_flight_time();
	void PrintInfo();
};

class CabinCrew: public CrewMember
{
	private:
	string cabin_position;

	public:
	CabinCrew();
	void set_cabin_position(string position);
	string get_cabin_position();
	void PrintInfo();
};