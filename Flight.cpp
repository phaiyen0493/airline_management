/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <utility>
#include "Flight.h"
using namespace std;

void Flight:: set_ID (string ID)
{
	flight_ID = ID;
}

string Flight:: get_ID()
{
	return flight_ID;
}

void Flight:: set_tail_num (string num)
{
	tail_num = num;
}

string Flight:: get_tail_num()
{
	return tail_num;
}

void Flight:: set_pilot_ID (int ID)
{
	pilot_ID = ID;
}

int Flight:: get_pilot_ID()
{
	return pilot_ID;
}

void Flight:: set_coPilot_ID(int ID)
{
	coPilot_ID = ID;
}

int Flight:: get_coPilot_ID()
{
	return coPilot_ID;
}

void Flight:: set_cabinCrew_ID (int* ID)
{
	cabinCrew_ID = ID;
}

int* Flight:: get_cabinCrew_ID()
{
	return cabinCrew_ID;
}

void Flight:: set_start_time(time_t time)
{
	start_time = time;
}

time_t Flight:: get_start_time()
{
	return start_time;
}

void Flight:: set_end_time(time_t time)
{
	end_time = time;
}

time_t Flight:: get_end_time()
{
	return end_time;
}

void Flight:: set_start_airCode(char* code)
{
	start_airCode = code;
}

char* Flight:: get_start_airCode()
{
	return start_airCode;
}

void Flight:: set_end_airCode(char* code)
{
	end_airCode = code;
}

char* Flight:: get_end_airCode()
{
	return end_airCode;
}

void Flight :: set_passenger_count(int count)
{
	passenger_count = count;
}

int Flight:: get_passenger_count()
{
	return passenger_count;
}

void Flight:: set_status(string status)
{
	this -> status = status;
}

string Flight:: get_status()
{
	return status;
}