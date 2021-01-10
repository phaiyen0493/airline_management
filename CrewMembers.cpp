/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include "CrewMember.h"
#include "CrewMembers.h"
using namespace std;

CrewMembers:: CrewMembers()
{
	member_count = 0;
}

void CrewMembers:: set_member_count(int count)
{
	member_count = count;
}

int CrewMembers:: get_member_count()
{
	return member_count;
}

vector <CrewMember*> CrewMembers:: get_member_vector()
{
	return member_collection;
}

//Count how many member in the crew member's list
int member_count_in_file()
{
	string line;
	int count = 0;
	ifstream fin;
	fin.open("crew_members");

	while(getline(fin, line))
	{
		count++;
	}
	fin.close();
	return count;
}

//Load info from the member's list
void CrewMembers:: Load_member()
{
	member_collection.clear();
	ifstream fin;
	string name;
	int ID;
	string type;
	string status;
	string start_time;
	string end_time;
	time_t tStart;
	time_t tEnd;
	struct tm start;
	struct tm end;
	int year, month, day, hour, minute, second;
	int member_count_file = member_count_in_file();
	string line;
	string rating;
	char* rating_code;
	time_t flight_time;
	string cabin_position;

	fin.open("crew_members"); //open file
	for (int i = 0; i < member_count_file; i++)
	{
		CrewMember *member;
		Pilot* pilot;
		CoPilot* coPilot;
		CabinCrew* cabinCrew;
		getline(fin, type, '\t');
		if (type == "pilot")
		{
			pilot = new Pilot;
			member = pilot;
		}
		if (type == "co-pilot")
		{
			coPilot = new CoPilot;
			member = coPilot;
		}
		if (type == "cabin")
		{
			cabinCrew = new CabinCrew;
			member = cabinCrew;
		}
		member->set_type(type);

		getline(fin, name, '\t');
		member->set_name(name);
		fin >> ID;
		member->set_ID(ID);
		fin.ignore();
		getline(fin, status, '\t');
		member->set_status(status);

		if (type == "pilot")
		{
			getline(fin, rating, '\t');
			rating_code = new char [6];
			strcpy(rating_code, rating.c_str());
			static_cast <Pilot*> (member)->set_rating_code(rating_code);
	
			fin >> flight_time;
			static_cast <Pilot*> (member)->set_cum_flight_time(flight_time);
			fin.ignore();
		}
		else if (type == "co-pilot")
		{
			getline(fin, rating, '\t');
			rating_code = new char [5];
			strcpy(rating_code, rating.c_str());
			static_cast <CoPilot*> (member)->set_rating_code(rating_code);
	
			fin >> flight_time;
			static_cast <CoPilot*> (member)->set_cum_flight_time(flight_time);
			fin.ignore();
		}
		else if (type == "cabin")
		{
			getline(fin, cabin_position, '\t');
			static_cast <CabinCrew*> (member)->set_cabin_position(cabin_position);
		}

		getline(fin, line);
		istringstream is(line);

		while (getline(is, start_time, '\t') && getline(is, end_time, '\t'))
		{
			//Convert start time string to time_t
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

			//Convert end time string to time_t
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
			member->add_time_slot(tStart, tEnd);
		}
		//Add member object to crew member vector
		member_collection.push_back(member);
	}
	set_member_count(member_count_file);
	fin.close();
}

//Store member to the member list
void CrewMembers:: Store_member()
{
	time_t start_t;
	time_t end_t;
	struct tm* start = new tm[1];
	struct tm* end = new tm[1];
	ofstream fout;
	fout.open("crew_members");
	char buffer[32];
	char buffer1[32];
	
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		fout << member_collection[i]->get_type() << "\t" << member_collection[i]->get_name() << "\t" << member_collection[i]->get_ID() << "\t" << member_collection[i]->get_status() << "\t";
		if (member_collection[i]->get_type() == "pilot")
		{
			fout << static_cast <Pilot*> (member_collection[i])->get_rating_code() << "\t" << static_cast <Pilot*> (member_collection[i])->get_cum_flight_time() << "\t";
		}
		else if (member_collection[i]->get_type() == "co-pilot")
		{
			fout << static_cast <CoPilot*> (member_collection[i])->get_rating_code() << "\t" << static_cast <Pilot*> (member_collection[i])->get_cum_flight_time() << "\t";
		}
		else
		{
			fout << static_cast <CabinCrew*> (member_collection[i])->get_cabin_position() << "\t";
		}

		for (unsigned int n = 0; n < member_collection[i]->get_time_slot_vector().size(); n++)
		{
			start_t = member_collection[i]->get_time_slot_vector()[n].first;
			start = localtime (&start_t);
			strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);

			end_t = member_collection[i]->get_time_slot_vector()[n].second;
			end = localtime (&end_t);
			strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
			fout << buffer << "\t" << buffer1 << "\t";
		}
		fout << endl; 
	}
	fout.close();
}

//Add member to member's list
void CrewMembers:: Add_member(CrewMember* crew_member)
{
	bool found_member = false;
	//Check if member's ID existed in the list or not
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if (crew_member->get_ID() == member_collection[i]->get_ID())
		{
			found_member = true;
			cout << "This member's ID has already been added in the list. Please add another crew member with different ID" << endl;
		}
	}
	//If input member's ID has not been used, add member object to member's vector
	if (found_member == false)
	{
		member_collection.push_back(crew_member);
		cout << "A new crew member has been added successfully" << endl;
		member_count++;
	}
	Store_member();
}

void CrewMembers:: Edit_member(int ID)
{
	string answer;
	string name;
	string type;
	string status;
	char* rating_code;
	int flight_hours;
	string cabin_position;
	time_t flight_time;
	bool found_member;
	bool found_member1;

	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if (ID == member_collection[i]->get_ID())
		{
			found_member = true;
			if (member_collection[i]->get_type() == "pilot")
			{
				//Print menu
				cout << "Which do you want to edit?" << endl;
				cout << "i. Name" << endl;
				cout << "ii. ID" << endl;
				cout << "iii. Type" << endl;
				cout << "iv. Status" << endl;
				cout << "v. Rating code" << endl;
				cout << "vi. Cumulative flight hours" << endl;
				cout << "Enter your choice: ";
				cin>> answer;
				cin.ignore();
 	
				if (answer == "i") //execute if user wants to change member's name
				{
					cout << "Enter new name: "; //prompt user to enter name
					getline(cin, name); //read name
					member_collection[i]->set_name(name); //reset name
					cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his name to " << member_collection[i]->get_name() << endl; 
					break;
				}

				if (answer == "ii") //if user wants to change member's ID
				{
					cout << "Enter new ID: ";
					cin >> ID;

					//Check if member's ID has been used in the list or not
					for (unsigned int n = 0; n < member_collection.size(); n++)
					{
						if (ID == member_collection[n]->get_ID())
						{
							found_member1 = true;
							cout << "This new member's ID has been used for another member in the list. Cannot change into this new member ID" << endl; break;
						}
					}
					//If member's ID is new, reset the member's ID
					if (found_member1 == false)
					{
						member_collection[i]->set_ID(ID);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his ID to " << member_collection[i]->get_ID() << endl;
					}
					break;
				}
	
				if (answer == "iii") //if change new type
				{
					cout << "Enter new type: ";
					getline (cin, type);
					if (type == "pilot" || type == "co-pilot" || type == "cabin")
					{
						member_collection[i]->set_type(type);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his type to " << member_collection[i]->get_type() << endl;
					}
					else
					{
						cout << "Please type the member's type in the category (pilot, co-pilot, cabin)" << endl;
					} 
					break;
				}

				if (answer == "iv") //if change status
				{
					cout << "Enter new status (available, on leave, sick, unknown): ";
					getline (cin, status);
					if (status == "available" || status == "on leave" || status == "sick" || status == "unknown")
					{
						member_collection[i]->set_status(status);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his status to " << member_collection[i]->get_status() << endl;
					}
					else
					{
						cout << "Please enter crew member's status within the status category (available, on leave, sick)" << endl;
					} 
					break;
				}

				if (answer == "v")
				{
					rating_code = new char[6];
					cout << "Enter new rating code (5 characters): ";
					cin.getline(rating_code,6);
					static_cast <Pilot*> (member_collection[i])-> set_rating_code(rating_code);
					cout << "Successfully change the rating code" << endl;
					delete [] rating_code;
				}

				if (answer == "vi")
				{
					cout << "Enter new flight hours: ";
					cin >> flight_hours;
					flight_time = (time_t) (flight_hours*3600);
					static_cast <Pilot*> (member_collection[i])-> set_cum_flight_time(flight_time);
					cout << "Successfully change the cumulative flight hours" << endl;
				}

				else
				{
					cout << "Wrong choice" << endl; 
					break;
				}
			}

			else if (member_collection[i]->get_type() == "co-pilot")
			{
				//Print menu
				cout << "Which do you want to edit?" << endl;
				cout << "i. Name" << endl;
				cout << "ii. ID" << endl;
				cout << "iii. Type" << endl;
				cout << "iv. Status" << endl;
				cout << "v. Rating code" << endl;
				cout << "vi. Cumulative flight hours" << endl;
				cout << "Enter your choice: ";
				cin>> answer;
				cin.ignore();
 	
				if (answer == "i") //execute if user wants to change member's name
				{
					cout << "Enter new name: "; //prompt user to enter name
					getline(cin, name); //read name
					member_collection[i]->set_name(name); //reset name
					cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his name to " << member_collection[i]->get_name() << endl; 
					break;
				}

				if (answer == "ii") //if user wants to change member's ID
				{
					cout << "Enter new ID: ";
					cin >> ID;

					//Check if member's ID has been used in the list or not
					for (unsigned int n = 0; n < member_collection.size(); n++)
					{
						if (ID == member_collection[n]->get_ID())
						{
							found_member1 = true;
							cout << "This new member's ID has been used for another member in the list. Cannot change into this new member ID" << endl; break;
						}
					}
					//If member's ID is new, reset the member's ID
					if (found_member1 == false)
					{
						member_collection[i]->set_ID(ID);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his ID to " << member_collection[i]->get_ID() << endl;
					}
					break;
				}
	
				if (answer == "iii") //if change new type
				{
					cout << "Enter new type: ";
					getline (cin, type);
					if (type == "pilot" || type == "co-pilot" || type == "cabin")
					{
						member_collection[i]->set_type(type);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his type to " << member_collection[i]->get_type() << endl;
					}
					else
					{
						cout << "Please type the member's type in the category (pilot, co-pilot, cabin)" << endl;
					} 
					break;
				}

				if (answer == "iv") //if change status
				{
					cout << "Enter new status (available, on leave, sick, unknown): ";
					getline (cin, status);
					if (status == "available" || status == "on leave" || status == "sick" || status == "unknown")
					{
						member_collection[i]->set_status(status);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his status to " << member_collection[i]->get_status() << endl;
					}
					else
					{
						cout << "Please enter crew member's status within the status category (available, on leave, sick)" << endl;
					} 
					break;
				}

				if (answer == "v")
				{
					rating_code = new char[5];
					cout << "Enter new rating code (4 characters): ";
					cin.getline(rating_code,5);
					static_cast <CoPilot*> (member_collection[i])-> set_rating_code(rating_code);
					cout << "Successfully change the rating code" << endl;
					delete [] rating_code;
				}

				if (answer == "vi")
				{
					cout << "Enter new flight hours: ";
					cin >> flight_hours;
					flight_time = (time_t) (flight_hours*3600);
					static_cast <CoPilot*> (member_collection[i])-> set_cum_flight_time(flight_time);
					cout << "Successfully change the cumulative flight hours" << endl;
				}

				else
				{
					cout << "Wrong choice" << endl; 
					break;
				}
			}

			else if (member_collection[i]->get_type() == "cabin")
			{
				//Print menu
				cout << "Which do you want to edit?" << endl;
				cout << "i. Name" << endl;
				cout << "ii. ID" << endl;
				cout << "iii. Type" << endl;
				cout << "iv. Status" << endl;
				cout << "v. Cabin position" << endl;
				cout << "Enter your choice: ";
				cin>> answer;
				cin.ignore();
 	
				if (answer == "i") //execute if user wants to change member's name
				{
					cout << "Enter new name: "; //prompt user to enter name
					getline(cin, name); //read name
					member_collection[i]->set_name(name); //reset name
					cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his name to " << member_collection[i]->get_name() << endl; 
					break;
				}

				if (answer == "ii") //if user wants to change member's ID
				{
					cout << "Enter new ID: ";
					cin >> ID;

					//Check if member's ID has been used in the list or not
					for (unsigned int n = 0; n < member_collection.size(); n++)
					{
						if (ID == member_collection[n]->get_ID())
						{
							found_member1 = true;
							cout << "This new member's ID has been used for another member in the list. Cannot change into this new member ID" << endl; break;
						}
					}
					//If member's ID is new, reset the member's ID
					if (found_member1 == false)
					{
						member_collection[i]->set_ID(ID);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his ID to " << member_collection[i]->get_ID() << endl;
					}
					break;
				}
	
				if (answer == "iii") //if change new type
				{
					cout << "Enter new type: ";
					getline (cin, type);
					if (type == "pilot" || type == "co-pilot" || type == "cabin")
					{
						member_collection[i]->set_type(type);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his type to " << member_collection[i]->get_type() << endl;
					}
					else
					{
						cout << "Please type the member's type in the category (pilot, co-pilot, cabin)" << endl;
					} 
					break;
				}

				if (answer == "iv") //if change status
				{
					cout << "Enter new status (available, on leave, sick, unknown): ";
					getline (cin, status);
					if (status == "available" || status == "on leave" || status == "sick" || status == "unknown")
					{
						member_collection[i]->set_status(status);
						cout << "Crew member with ID #" << member_collection[i]->get_ID() << " has changed her/ his status to " << member_collection[i]->get_status() << endl;
					}
					else
					{
						cout << "Please enter crew member's status within the status category (available, on leave, sick)" << endl;
					} 
					break;
				}

				if (answer == "v")
				{
					cout << "Enter new cabin crew's position (first class, business class, economy front, economy rear, lead): ";
					getline(cin, cabin_position);
					static_cast <CabinCrew*> (member_collection[i])-> set_cabin_position(cabin_position);
					cout << "Successfully change the position" << endl;
				}

				else
				{
					cout << "Wrong choice" << endl; 
					break;
				}
			}
		}
	}

	if (found_member == false)
	{
		cout << "Cannot find this crew member in database" << endl;
	}
	Store_member();
}

void CrewMembers:: Delete_member(int ID) //delete member
{
	bool found_member = false;
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if ( ID == member_collection[i]->get_ID())
		{
			found_member = true;
			member_collection.erase(member_collection.begin() + i);
			member_count--;
		}
	}

	if (found_member == false)
	{
		cout << "Cannot find this crew member in database" << endl;
	}
	else
	{
		cout << "Successfully deleted crew member with this ID" << endl;
	}
	Store_member();
}

void CrewMembers:: Search_member() //search member based on criteria
{
	string answer;
	string name;
	int ID;
	string type;
	string status;
	cout << "Which do you want to search?" << endl;
	cout << "i. Name" << endl;
	cout << "ii. ID" << endl;
	cout << "iii. Type" << endl;
	cout << "iv. Status" << endl;
	cout << "Enter your choice: ";
	cin >> answer;
	cin.ignore();

	if (answer == "i")
	{
		bool found_name = false;
		cout << "Enter name: ";
		getline (cin, name);
		for (unsigned int i = 0; i < member_collection.size(); i++)
		{
			if (name == member_collection[i]->get_name())
			{
				found_name = true;
				cout << "Crew member's ID: " << member_collection[i]->get_ID() << endl;
			}
		}

		if (found_name == false)
		{
			cout << "Cannot find crew member with this name" << endl;
		}
	}

	else if (answer == "ii")
	{
		bool found_ID = false;
		cout << "Enter ID: ";
		cin >> ID;
		for (unsigned int i = 0; i < member_collection.size(); i++)
		{
			if (ID == member_collection[i]->get_ID())
			{
				found_ID = true;
				cout << "Found crew member with ID #" << member_collection[i]->get_ID() << endl;
				member_collection[i]->PrintInfo();
			}
		}

		if (found_ID == false)
		{
			cout << "Cannot find crew member with this ID" << endl;
		}
	}

	else if (answer == "iii")
	{
		bool found_type = false;
		cout << "Enter type: ";
		getline (cin, type);
		for (unsigned int i = 0; i < member_collection.size(); i++)
		{
			if (type == member_collection[i]->get_type())
			{
				found_type = true;
				cout << "Crew member's ID: " << member_collection[i]->get_ID() << endl;
			}
		}

		if (found_type == false)
		{
			cout << "Cannot find crew member with this type" << endl;
		}
	}

	else if (answer == "iv")
	{
		bool found_status = false;
		cout << "Enter status: ";
		getline (cin, status);
		for (unsigned int i = 0; i < member_collection.size(); i++)
		{
			if (status == member_collection[i]->get_status())
			{
				found_status = true;
				cout << "Crew member's ID: " << member_collection[i]->get_ID() << endl;
			}
		}

		if (found_status == false)
		{
			cout << "Cannot find crew member with this status" << endl;
		}
	}

	else
	{
		cout << "Wrong choice" << endl;
	}
}

void CrewMembers:: Print_member(int ID) //print a member
{
	bool found_ID = false;
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if (ID == member_collection[i]->get_ID())
		{
			found_ID = true;
			member_collection[i]->PrintInfo();
		}
	}

	if (found_ID == false)
	{
		cout << "Cannot find crew member with this ID" << endl;
	}
}

void CrewMembers:: Print_members() //print member's list
{
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		cout << i+1 << "." << endl;
		member_collection[i]->PrintInfo();
		cout << endl;
	}
	if (member_count == 0)
	{
		cout << "No crew member has been added to this list yet" << endl;
	}
}

void CrewMembers:: Add_member_time_slot(int member_index, time_t start_time, time_t end_time)
{
	time_t time_gap;
	time_t cum_time;
	member_collection[member_index]->add_time_slot(start_time, end_time);
	if (member_collection[member_index]->get_type() == "pilot")
	{
		time_gap = end_time - start_time;
		cum_time = static_cast<Pilot*> (member_collection[member_index])->get_cum_flight_time();
		cum_time += time_gap;
		static_cast<Pilot*> (member_collection[member_index])->set_cum_flight_time(cum_time);
	}

	if (member_collection[member_index]->get_type() == "co-pilot")
	{
		time_gap = end_time - start_time;
		cum_time = static_cast<CoPilot*> (member_collection[member_index])->get_cum_flight_time();
		cum_time += time_gap;
		static_cast<CoPilot*> (member_collection[member_index])->set_cum_flight_time(cum_time);
	}
	Store_member();
}

void CrewMembers:: Delete_member_time_slot(int member_index, int time_slot_index)
{
	time_t time_gap;
	time_t cum_time;
	member_collection[member_index]->delete_time_slot(time_slot_index);
	if (member_collection[member_index]->get_type() == "pilot")
	{
		time_gap = member_collection[member_index]->get_time_slot_vector()[time_slot_index].second - member_collection[member_index]->get_time_slot_vector()[time_slot_index].first;
		cum_time = static_cast<Pilot*> (member_collection[member_index])->get_cum_flight_time();
		cum_time -= time_gap;
		static_cast<Pilot*> (member_collection[member_index])->set_cum_flight_time(cum_time);
	}

	if (member_collection[member_index]->get_type() == "co-pilot")
	{
		time_gap = member_collection[member_index]->get_time_slot_vector()[time_slot_index].second - member_collection[member_index]->get_time_slot_vector()[time_slot_index].first;
		cum_time = static_cast<CoPilot*> (member_collection[member_index])->get_cum_flight_time();
		cum_time -= time_gap;
		static_cast<CoPilot*> (member_collection[member_index])->set_cum_flight_time(cum_time);
	}
	Store_member();
}

void CrewMembers:: Sort_time(int member_index)
{
	member_collection[member_index]->sort_time_slot();
	Store_member();
}