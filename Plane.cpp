/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "Plane.h"
#include <string>
#include <utility>
using namespace std;

void Plane:: set_make(string make)
{
	this -> make = make;
}

string Plane:: get_make()
{
	return make;
}

void Plane:: set_model(int model)
{
	this -> model = model;
}

int Plane:: get_model()
{
	return model;
}

void Plane:: set_tail_num(string tail_num)
{
	this -> tail_num = tail_num;
}

string Plane:: get_tail_num()
{
	return tail_num;
}

void Plane:: set_seat_count(int count)
{
	seat_count = count;
}

int Plane:: get_seat_count()
{
	return seat_count;
}

void Plane:: set_range(int range)
{
	this -> range = range;
}

int Plane:: get_range()
{
	return range;
}

void Plane:: set_status(string status)
{
	this -> status = status;
}

string Plane:: get_status()
{
	return status;
}

void Plane:: add_time_slot (time_t start, time_t end)
{
	time_slot.push_back(pair <time_t, time_t> (start, end));
}

void Plane:: delete_time_slot()
{
	time_slot.pop_back();
}

void Plane:: delete_time_slot(int i)
{
	time_slot.erase(time_slot.begin() + i);
}

vector < pair <time_t, time_t> > Plane::get_time_slot_vector()
{
	return time_slot;
}

bool ascending( pair <time_t, time_t> &a, pair<time_t, time_t> &b)
{
	return (a.first < b.first && a.second < b.second);	
}

void Plane:: sort_time_slot()
{
	sort(time_slot.begin(), time_slot.end(), ascending);
}