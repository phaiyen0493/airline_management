/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Plane.h"
#include "Planes.h"
using namespace std;

Planes:: Planes()
{
	plane_count = 0;
}

void Planes:: set_plane_count(int count)
{
	plane_count = count;
}

int Planes:: get_plane_count()
{
	return plane_count;
}

vector <Plane> Planes:: get_plane_vector()
{
	return plane_collection;
}

int plane_count_in_file()
{
	string line;
	int count = 0;
	ifstream fin;
	fin.open("planes");

	while(getline(fin, line))
	{
		count++;
	}
	fin.close();
	return count;
}

void Planes:: Load_plane()
{
	plane_collection.clear();
	ifstream fin;
	string make;
	int model;
	string tail_num;
	int seat_count;
	int range;
	string status;
	string start_time;
	string end_time;
	time_t tStart;
	time_t tEnd;
	struct tm start;
	struct tm end;
	int year, month, day, hour, minute, second;
	int plane_count_file = plane_count_in_file();
	string line;

	fin.open("planes");
	for (int i = 0; i < plane_count_file; i++)
	{
		Plane plane;
		getline(fin, make, '\t');
		plane.set_make(make);
		fin >> model;
		plane.set_model(model);
		fin.ignore();
		getline(fin, tail_num, '\t');
		plane.set_tail_num(tail_num);
		fin >> seat_count;
		plane.set_seat_count(seat_count);
		fin >> range;
		plane.set_range(range);
		fin.ignore();
		getline(fin, status,'\t');
		plane.set_status(status);

		getline(fin, line);
		istringstream is(line);

		while (getline(is, start_time, '\t') && getline(is, end_time, '\t'))
		{
			const char* cStart = start_time.c_str();
			sscanf(cStart, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
			start.tm_year = year - 1900;
			start.tm_mon = month - 1;
			start.tm_mday = day;
			start.tm_hour = hour;
			start.tm_min = minute;
			start.tm_sec = second;
			start.tm_isdst = -1;
			tStart = mktime(&start);

			const char* cEnd = end_time.c_str();
			sscanf(cEnd, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
			end.tm_year = year - 1900;
			end.tm_mon = month - 1;
			end.tm_mday = day;
			end.tm_hour = hour;
			end.tm_min = minute;
			end.tm_sec = second;
			end.tm_isdst = -1;
			tEnd = mktime(&end);
			plane.add_time_slot(tStart, tEnd);
		}
		plane_collection.push_back(plane);
	}
	set_plane_count(plane_count_file);
	fin.close();
}

void Planes:: Store_plane()
{
	time_t start_t;
	time_t end_t;
	struct tm* start = new tm[1];
	struct tm* end = new tm[1];
	ofstream fout;
	fout.open("planes");
	char buffer[32];
	char buffer1[32];
	
	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		fout << plane_collection[i].get_make() << "\t" << plane_collection[i].get_model() << "\t" << plane_collection[i].get_tail_num() << "\t" << plane_collection[i].get_seat_count() << "\t" << plane_collection[i].get_range() << "\t" << plane_collection[i].get_status() << "\t";
		for (unsigned int n = 0; n < plane_collection[i].get_time_slot_vector().size(); n++)
		{
			start_t = plane_collection[i].get_time_slot_vector()[n].first;
			start = localtime (&start_t);
			strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);

			end_t = plane_collection[i].get_time_slot_vector()[n].second;
			end = localtime (&end_t);
			strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
			fout << buffer << "\t" << buffer1 << "\t";
		}
		fout << endl;
	}
	fout.close();
}

void Planes:: Add_plane(Plane plane)
{
	bool found_plane = false;
	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (plane.get_tail_num() == plane_collection[i].get_tail_num())
		{
			found_plane = true;
			cout << "This plane's ID (tail number) has already been added. Please add another plane with different ID" << endl;
		}
	}

	if (found_plane == false)
	{
		plane_collection.push_back(plane);
		cout << "A new plane has been added successfully" << endl;
		plane_count++;
	}
	Store_plane();
}

void Planes:: Edit_plane(string plane_ID)
{
	bool found_plane = false;
	bool found_plane1 = false;
	string answer;
	string make;
	int model;
	string tail_num;
	int seat_count;
	int range;
	string status;

	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (plane_ID == plane_collection[i].get_tail_num())
		{
			found_plane = true;
			cout << "i. Make" << endl;
			cout << "ii. Model" << endl;
			cout << "iii. Tail number" << endl;
			cout << "iv. Number of seats" << endl;
			cout << "v. Range in miles" << endl;
			cout << "vi. Status" << endl;
			cout << "Which do you want to edit of a plane? (i, ii, etc.): ";
			cin >> answer;
			cin.ignore();
			
			if ( answer == "i")
			{
				cout << "Enter the make of airplane with ID #" << plane_collection[i].get_tail_num() << ": ";
				getline(cin, make);
				plane_collection[i].set_make(make);
				cout << "Make of this airplane is now changed to: " << plane_collection[i].get_make() << endl; 
				break;
			}

			else if (answer == "ii")
			{
				cout << "Enter the model of airplane with ID #" << plane_collection[i].get_tail_num() << ": ";
				cin >> model;
				plane_collection[i].set_model(model);
				cout << "Model of this airplane is now changed to: " << plane_collection[i].get_model() << endl;	
				break;
			}

			else if (answer == "iii")
			{
				cout << "Enter the new ID of airplane: ";
				getline (cin, tail_num);

				for (unsigned int n = 0; n < plane_collection.size(); n++)
				{
					if (tail_num == plane_collection[n].get_tail_num())
					{
						found_plane1 = true;
						cout << "This new plane ID has been used for another plane. Cannot change into this new plane's ID" << endl; break;	
					}
				}
				if (found_plane1 == false)
				{
					plane_collection[i].set_tail_num(tail_num);
					cout << "Tail number of this airplane is now changed to: " << plane_collection[i].get_tail_num() << endl;
				}
				break;
			}

			else if (answer == "iv")
			{
				cout << "Enter the number of seats of airplane with ID #" << plane_collection[i].get_tail_num() << ": ";
				cin >> seat_count;
				plane_collection[i].set_seat_count(seat_count);
				cout << "Number of seats of this airplane is now changed to: " << plane_collection[i].get_seat_count() << endl;
				break;
			}

			else if (answer == "v")
			{
				cout << "Enter the number of seats of airplane with ID #" << plane_collection[i].get_tail_num() << ": ";
				cin >> range;
				plane_collection[i].set_seat_count(seat_count);
				cout << "Number of seats of this airplane is now changed to: " << plane_collection[i].get_seat_count() << endl;
				break;
			}

			else if (answer == "vi")
			{
				cout << "Enter new status of the airplane with ID#" << plane_collection[i].get_tail_num() << " (out, in , on repair, unknown): ";
				getline (cin, status);

				plane_collection[i].set_status(status);
				cout << "Status this airplane is now changed to: " << plane_collection[i].get_status() << endl;
				break;
			}

			else
			{
				cout << "Wrong choice" << endl;
				break;
			}
		}
	}

	if (found_plane == false)
	{
		cout << "Cannot find any plane with this tail number. Nothing changed" << endl;
	}
	Store_plane();
}

void Planes:: Delete_plane (string plane_ID)
{
	bool found_plane = false;
	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (plane_ID == plane_collection[i].get_tail_num())
		{
			found_plane = true;
			plane_collection.erase(plane_collection.begin() + i);
			plane_count--;
		}		
	}

	if (found_plane == false)
	{
		cout << "Cannot find any plane with this tail number. Nothing removed" << endl;
	}
	else
	{
		cout << "Successfully deleted plane with this tail number" << endl;
	}
	Store_plane();
}

void Planes:: Search_plane()
{
	string answer;
	bool found_plane;

	cout << "Which criteria of a plane you want to look up?" << endl;
	cout << "i. Make" << endl;
	cout << "ii. Model" << endl;
	cout << "iii. Tail number" << endl;
	cout << "iv. Number of seats" << endl;
	cout << "v. Range in miles" << endl;
	cout << "vi. Status (in/available, repair)" << endl;
	cout << "Enter your choice (i, ii, iii, etc.): ";
	cin >> answer;
	cin.ignore();
	cout << endl;

	if (answer == "i")
	{
		string make;
		found_plane = false;
		cout << "Enter plane's make you want to find: ";
		getline(cin, make);
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (make == plane_collection[i].get_make())
			{
				found_plane = true;
				cout << "Airplane's ID #" << plane_collection[i].get_tail_num() << endl;	
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this make" << endl;
		}
	}
	
	else if (answer == "ii")
	{
		int model;
		found_plane = false;
		cout << "Enter plane's model you want to find: ";
		cin >> model;
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (model == plane_collection[i].get_model())
			{
				found_plane = true;
				cout << "Airplane's ID #" << plane_collection[i].get_tail_num() << endl;	
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this model" << endl;
		}
	}

	else if (answer == "iv")
	{
		int seat_count;
		found_plane = false;
		cout << "Enter plane's number of seats you want to find: ";
		cin >> seat_count;
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (seat_count == plane_collection[i].get_seat_count())
			{
				found_plane = true;
				cout << "Airplane's ID #" << plane_collection[i].get_tail_num() << endl;
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this number of seats" << endl;
		}
	}

	else if (answer == "iii")
	{
		string tail_num;
		found_plane = false;
		cout << "Enter plane's ID (tail number) you want to find: ";
		getline(cin, tail_num);
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (tail_num == plane_collection[i].get_tail_num())
			{
				found_plane = true;
				cout << "This airplane is already in the list" << endl;	
				cout << "Plane's make: " << plane_collection[i].get_make() << endl;
				cout << "Plane's model: " << plane_collection[i].get_model() << endl;
				cout << "Plane's tail num: " << plane_collection[i].get_tail_num() << endl;
				cout << "Plane's number of seats: " << plane_collection[i].get_seat_count() << endl;
				cout << "Plane's range in miles: " << plane_collection[i].get_range() << endl;
				cout << "Plane's status: " << plane_collection[i].get_status() << endl;
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this plane's ID" << endl;
		}

	}

	else if (answer == "v")
	{
		int range;
		found_plane = false;
		cout << "Enter plane's range (in miles) you want to find: ";
		cin >> range;
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (range == plane_collection[i].get_range())
			{
				found_plane = true;
				cout << "Airplane's ID #" << plane_collection[i].get_tail_num() << endl;	
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this range" << endl;
		}
	}

	else if (answer == "vi")
	{
		string status;
		found_plane = false;
		cout << "Enter plane's status you want to find: ";
		getline(cin, status);
		
		for (unsigned int i = 0; i < plane_collection.size(); i++)
		{
			if (status == plane_collection[i].get_status())
			{
				found_plane = true;
				cout << "Airplane's ID #" << plane_collection[i].get_tail_num() << endl;	
			}
		}

		if(found_plane == false)
		{
			cout << "Cannot find an airplane with this status" << endl;
		}
	}

	else
	{
		cout << "Wrong choice. Cannot search anything" << endl;
	}
	Store_plane();
}

void Planes:: Print_plane (string plane_ID)
{
	bool found_plane = false;
	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (plane_ID == plane_collection[i].get_tail_num())
		{
			found_plane = true;
			cout << "Plane's make: " << plane_collection[i].get_make() << endl;
			cout << "Plane's model: " << plane_collection[i].get_model() << endl;
			cout << "Plane's tail num: " << plane_collection[i].get_tail_num() << endl;
			cout << "Plane's number of seats: " << plane_collection[i].get_seat_count() << endl;
			cout << "Plane's range in miles: " << plane_collection[i].get_range() << endl;
			cout << "Plane's status: " << plane_collection[i].get_status() << endl;
		}		
	}

	if (found_plane == false)
	{
		cout << "Cannot find any plane with this tail number" << endl;
	}
	Store_plane();
}

void Planes:: Print_planes()
{
	if (plane_count == 0)
	{
		cout << "No plane has been added to the list yet" << endl;
	}

	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		cout << i+1 << "." << endl;
		cout << "Plane's make: " << plane_collection[i].get_make() << endl;
		cout << "Plane's model: " << plane_collection[i].get_model() << endl;
		cout << "Plane's tail num: " << plane_collection[i].get_tail_num() << endl;
		cout << "Plane's number of seats: " << plane_collection[i].get_seat_count() << endl;
		cout << "Plane's range in miles: " << plane_collection[i].get_range() << endl;
		cout << "Plane's status: " << plane_collection[i].get_status() << endl;	
		cout << endl;
	}
	Store_plane();
}

void Planes:: Add_plane_time_slot(int plane_index, time_t start_time, time_t end_time)
{
	plane_collection[plane_index].add_time_slot(start_time, end_time);
	Store_plane();
}

void Planes:: Delete_plane_time_slot(int plane_index)
{
	plane_collection[plane_index].delete_time_slot();
	Store_plane();
}

void Planes:: Delete_plane_time_slot(int plane_index, int time_slot_index)
{
	plane_collection[plane_index].delete_time_slot(time_slot_index);
	Store_plane();
}

void Planes:: Sort_time (int plane_index)
{
	plane_collection[plane_index].sort_time_slot();
	Store_plane();
}