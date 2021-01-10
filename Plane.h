/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <utility>
using namespace std;

class Plane
{
	private:
	string make;
	int model;
	string tail_num;
	int seat_count;
	int range;
	string status;
	vector < pair <time_t, time_t> > time_slot ;

	public:
	void set_make(string make);
	string get_make();
	void set_model(int model);
	int get_model();
	void set_tail_num(string tail_num);
	string get_tail_num();
	void set_seat_count(int count);
	int get_seat_count();
	void set_range(int range);
	int get_range();
	void set_status(string status);
	string get_status();
	void add_time_slot (time_t start, time_t end);
	void delete_time_slot();
	void delete_time_slot(int i);
	vector < pair <time_t, time_t> > get_time_slot_vector();
	void sort_time_slot();
};