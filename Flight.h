/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Flight
{
	private:
	string flight_ID;
	string tail_num;
	int pilot_ID;
	int coPilot_ID;
	int* cabinCrew_ID;
	time_t start_time;
	time_t end_time;
	char* start_airCode;
	char* end_airCode;
	int passenger_count;
	string status;
	
	public:
	void set_ID(string ID);
	string get_ID();
	void set_tail_num (string num);
	string get_tail_num();
	void set_pilot_ID (int ID);
	int get_pilot_ID();
	void set_coPilot_ID(int ID);
	int get_coPilot_ID();
	void set_cabinCrew_ID (int* ID);
	int* get_cabinCrew_ID();
	void set_start_time(time_t time);
	time_t get_start_time();
	void set_end_time(time_t time);
	time_t get_end_time();
	void set_start_airCode(char* code);
	char* get_start_airCode();
	void set_end_airCode(char* code);
	char* get_end_airCode();
	void set_passenger_count(int count);
	int get_passenger_count();
	void set_status(string status);
	string get_status();	
};