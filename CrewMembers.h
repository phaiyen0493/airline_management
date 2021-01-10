/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <vector>
using namespace std;

class CrewMembers
{
	private:
	int member_count;
	vector <CrewMember*> member_collection;	

	public:
	CrewMembers();
	void set_member_count(int count);
	int get_member_count();
	void Load_member();
	void Store_member();
	vector <CrewMember*> get_member_vector();
	void Add_member(CrewMember* crew_member);
	void Edit_member(int ID);
	void Delete_member(int ID);
	void Search_member();
	void Print_member(int ID);
	void Print_members();
	void Add_member_time_slot(int member_index, time_t start_time, time_t end_time);
	void Delete_member_time_slot(int member_index, int time_slot_index);
	void Sort_time(int member_index);
};