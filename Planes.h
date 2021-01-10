/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <vector>
using namespace std;

class Planes
{
	private:
	int plane_count;
	vector <Plane> plane_collection;

	public:
	Planes();
	void set_plane_count(int count);
	int get_plane_count();
	void Load_plane();
	void Store_plane();
	vector <Plane> get_plane_vector();
	void Add_plane(Plane plane);
	void Edit_plane(string plane_ID);
	void Delete_plane(string plane_ID);
	void Search_plane();
	void Print_plane(string plane_ID);
	void Print_planes();
	void Add_plane_time_slot(int plane_index, time_t start_time, time_t end_time);
	void Delete_plane_time_slot(int plane_index);
	void Delete_plane_time_slot(int plane_index, int time_slot_index); 
	void Sort_time(int plane_index);
};