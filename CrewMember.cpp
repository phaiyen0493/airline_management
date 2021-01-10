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
#include <iomanip>
#include <algorithm>
#include "CrewMember.h"
using namespace std;

void CrewMember:: set_name(string name)
{
	this -> name = name;
}

string CrewMember:: get_name()
{
	return name;
}

void CrewMember:: set_ID(int ID)
{
	this -> ID = ID;
}

int CrewMember:: get_ID()
{
	return ID;
}

void CrewMember:: set_type(string type)
{
	this-> type = type;
}

string CrewMember:: get_type()
{
	return type;
}

void CrewMember:: set_status(string status)
{
	this -> status = status;
}

string CrewMember:: get_status()
{
	return status;
}

void CrewMember:: PrintInfo()
{}

Pilot:: Pilot()
{
	rating_code = new char [6];
	flight_time = 0;
}

void Pilot:: set_rating_code(char* code)
{
	rating_code = code;
}

char* Pilot:: get_rating_code()
{
	return rating_code;
}

void Pilot:: set_cum_flight_time(time_t seconds)
{
	flight_time = seconds;	
}

time_t Pilot:: get_cum_flight_time()
{
	return flight_time;
}

void Pilot:: PrintInfo()
{
	cout << "ID: " << get_ID() << endl;
	cout << "Name: " << get_name() << endl;
	cout << "Type: " << get_type() << endl;
	cout << "Status: " << get_status() << endl;
	cout << "Rating code: " << get_rating_code() << endl;
	cout << "Cumulative flight hours: " << fixed << setprecision(2) << (double)(get_cum_flight_time())/3600 << endl;
}

CoPilot:: CoPilot()
{
	rating_code = new char [5];
	flight_time = 0;
}

void CoPilot:: set_rating_code(char* code)
{
	rating_code = code;
}

char* CoPilot:: get_rating_code()
{
	return rating_code;
}

void CoPilot:: set_cum_flight_time(time_t seconds)
{
	flight_time = seconds;	
}

time_t CoPilot:: get_cum_flight_time()
{
	return flight_time;
}

void CoPilot:: PrintInfo()
{
	cout << "ID: " << get_ID() << endl;
	cout << "Name: " << get_name() << endl;
	cout << "Type: " << get_type() << endl;
	cout << "Status: " << get_status() << endl;
	cout << "Rating code: " << get_rating_code() << endl;
	cout << "Cumulative flight hours: " << fixed << setprecision(2) << (double)(get_cum_flight_time())/3600 << endl;
}

CabinCrew:: CabinCrew()
{
	cabin_position = "none";
}

void CabinCrew:: set_cabin_position(string position)
{
	cabin_position = position;
}

string CabinCrew:: get_cabin_position()
{
	return cabin_position;
}

void CabinCrew:: PrintInfo()
{
	cout << "ID: " << get_ID() << endl;
	cout << "Name: " << get_name() << endl;
	cout << "Type: " << get_type() << endl;
	cout << "Status: " << get_status() << endl;
	cout << "Cabin position: " << get_cabin_position() << endl;
}

void CrewMember:: add_time_slot( time_t start, time_t end)
{
	time_slot.push_back(pair <time_t, time_t> (start, end));
}

void CrewMember:: delete_time_slot(int i)
{
	time_slot.erase(time_slot.begin() + i);
}

vector <pair <time_t, time_t> > CrewMember:: get_time_slot_vector()
{
	return time_slot;
}

bool ascending( pair <time_t, time_t> &a, pair<time_t, time_t> &b);

void CrewMember:: sort_time_slot()
{
	sort(time_slot.begin(), time_slot.end(), ascending);
}

