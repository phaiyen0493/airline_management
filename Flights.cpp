/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/
#include <iostream>
#include <vector>
#include <utility>
#include <ctime>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include "Plane.h"
#include "CrewMember.h"
#include "Flight.h"
#include "Planes.h"
#include "CrewMembers.h"
#include "Flights.h"

Flights::Flights()
{
	flight_count = 0;
}

void Flights:: set_flight_count(int count)
{
	flight_count = count;
}

int Flights:: get_flight_count()
{
	return flight_count;
}

int flight_count_in_file()
{
	string line;
	int count = 0;
	ifstream fin;
	fin.open("flights");

	while(getline(fin, line))
	{
		count++;
	}
	fin.close();
	return count;
}

void Flights:: Store_flight()//store flight
{
	time_t start_t;
	time_t end_t;
	struct tm* start = new tm[1];
	struct tm* end = new tm[1];
	ofstream fout;
	fout.open("flights");
	char buffer[32];
	char buffer1[32];

	for (unsigned int i = 0; i < flight_collection.size(); i++)
	{
		fout << flight_collection[i].get_ID() << "\t" << flight_collection[i].get_tail_num() << "\t" << flight_collection[i].get_pilot_ID() << "\t" << flight_collection[i].get_coPilot_ID() << "\t" << flight_collection[i].get_cabinCrew_ID()[0] << "\t" << flight_collection[i].get_cabinCrew_ID()[1] << "\t" << flight_collection[i].get_cabinCrew_ID()[2] << "\t";
		start_t = flight_collection[i].get_start_time();
		start = localtime (&start_t);
		strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);

		end_t = flight_collection[i].get_end_time();
		end = localtime (&end_t);
		strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
		fout << buffer << "\t" << buffer1 << "\t" << flight_collection[i].get_start_airCode() << "\t" << flight_collection[i].get_end_airCode() << "\t" << flight_collection[i].get_passenger_count() << "\t" << flight_collection[i].get_status() << endl;
	}
	fout.close();
}

void Flights:: Add_flight(Flight flight, Planes* planes, CrewMembers* crew_members)//add flight
{
	bool seat_check = false;
	bool flight_found = false;
	bool plane_found = false;
	bool pilot_found = false;
	bool coPilot_found = false;
	bool first_cabinCrew_found = false;
	bool second_cabinCrew_found = false;
	bool third_cabinCrew_found = false;
	bool plane_time_check = true;
	bool pilot_time_check = true;
	bool coPilot_time_check = true;
	bool first_cabinCrew_time_check = true;
	bool second_cabinCrew_time_check = true;
	bool third_cabinCrew_time_check = true;
	int plane_index, pilot_index, coPilot_index, first_cabin_index, second_cabin_index, third_cabin_index;

	//check if flight ID has existed before
	for (unsigned int i = 0; i < flight_collection.size(); i++)
	{
		if (flight.get_ID() == flight_collection[i].get_ID())
		{	
			flight_found = true;
			cout << "This flight ID has been used for another flight. Please add another flight with different flight ID" << endl;
		}
	}

	time_t slot_start_time;
	time_t slot_end_time;
	time_t flight_start_time = flight.get_start_time();
	time_t flight_end_time = flight.get_end_time();

	vector <Plane> plane_collection = planes->get_plane_vector();
	vector <CrewMember*> member_collection = crew_members->get_member_vector();

	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (flight.get_tail_num() == plane_collection[i].get_tail_num() && plane_collection[i].get_status() != "on repair")
		{
			plane_found = true;
			if (flight.get_passenger_count() <= plane_collection[i].get_seat_count())
			{
				seat_check = true;
				vector < pair <time_t, time_t> > plane_time_slot_vector = plane_collection[i].get_time_slot_vector();
				for (unsigned int n = 0; n < plane_time_slot_vector.size(); n++)
				{
					slot_start_time = plane_time_slot_vector[n].first;
					slot_end_time = plane_time_slot_vector[n].second;
					if ( ((flight_start_time >= slot_start_time) && (flight_start_time < slot_end_time)) || ((flight_end_time > slot_start_time) && (flight_end_time <= slot_end_time)) || ((flight_start_time <= slot_start_time) && (flight_end_time >= slot_end_time)))
					{
						plane_time_check = false;
					}
				}
				if (plane_time_check == true)
				{
					plane_index = i;
				}
			}
		}
	}

	if (plane_found == true && plane_time_check == false)
	{
		cout << "The chosen airplane has already been scheduled for another flight (time conflict)" << endl;
		cout << "Please change flight time or choose another airplane for this plane" << endl << endl;
	}
	
	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if (flight.get_pilot_ID() == member_collection[i]->get_ID() && member_collection[i]->get_type() == "pilot" && member_collection[i]->get_status() == "available")
		{
			pilot_found = true;
			vector < pair <time_t, time_t> > member_time_slot_vector = member_collection[i]->get_time_slot_vector();
			for (unsigned int n = 0; n < member_time_slot_vector.size(); n++)
			{
				if ((flight.get_start_time() >= member_time_slot_vector[n].first && flight.get_start_time() < member_time_slot_vector[n].second) || (flight.get_end_time() > member_time_slot_vector[n].first && flight.get_end_time() <= member_time_slot_vector[n].second) || ((flight.get_start_time() <= member_time_slot_vector[n].first) && (flight.get_end_time() >= member_time_slot_vector[n].second)) )
				{
					pilot_time_check = false;
				}
			}
			if (pilot_time_check == true)
			{
				pilot_index = i;
			}
		}
		else if (flight.get_coPilot_ID() == member_collection[i]->get_ID() && member_collection[i]->get_type() == "co-pilot" && member_collection[i]->get_status() == "available")
		{
			coPilot_found = true;
			vector < pair <time_t, time_t> > member_time_slot_vector = member_collection[i]->get_time_slot_vector();
			for (unsigned int n = 0; n < member_time_slot_vector.size(); n++)
			{
				if ((flight.get_start_time() >= member_time_slot_vector[n].first && flight.get_start_time() < member_time_slot_vector[n].second) || (flight.get_end_time() > member_time_slot_vector[n].first && flight.get_end_time() <= member_time_slot_vector[n].second) || ((flight.get_start_time() <= member_time_slot_vector[n].first) && (flight.get_end_time() >= member_time_slot_vector[n].second)))
				{
					coPilot_time_check = false;
				}
			}
			if (coPilot_time_check == true)
			{
				coPilot_index = i;
			}
		}
		else
		{
			if ((flight.get_cabinCrew_ID()[0] == member_collection[i]->get_ID()) && (member_collection[i]->get_type() == "cabin") && member_collection[i]->get_status() == "available")
			{
				first_cabinCrew_found = true;
				vector < pair <time_t, time_t> > member_time_slot_vector = member_collection[i]->get_time_slot_vector();
				for (unsigned int n = 0; n < member_time_slot_vector.size(); n++)
				{
					if ((flight.get_start_time() >= member_time_slot_vector[n].first && flight.get_start_time() < member_time_slot_vector[n].second) || (flight.get_end_time() > member_time_slot_vector[n].first && flight.get_end_time() <= member_time_slot_vector[n].second) || ((flight.get_start_time() <= member_time_slot_vector[n].first) && (flight.get_end_time() >= member_time_slot_vector[n].second)))
					{
						first_cabinCrew_time_check = false;
					}
				}
				if (first_cabinCrew_time_check == true)
				{
					first_cabin_index = i;
				}
			}

			if ((flight.get_cabinCrew_ID()[1] == member_collection[i]->get_ID()) && (member_collection[i]->get_type() == "cabin") && member_collection[i]->get_status() == "available")
			{
				second_cabinCrew_found = true;
				vector < pair <time_t, time_t> > member_time_slot_vector = member_collection[i]->get_time_slot_vector();
				for (unsigned int n = 0; n < member_time_slot_vector.size(); n++)
				{
					if ((flight.get_start_time() >= member_time_slot_vector[n].first && flight.get_start_time() < member_time_slot_vector[n].second) || (flight.get_end_time() > member_time_slot_vector[n].first && flight.get_end_time() <= member_time_slot_vector[n].second) || ((flight.get_start_time() <= member_time_slot_vector[n].first) && (flight.get_end_time() >= member_time_slot_vector[n].second)))
					{
						second_cabinCrew_time_check = false;
					}
				}
				if (second_cabinCrew_time_check == true)
				{
					second_cabin_index = i;
				}
			}

			if ((flight.get_cabinCrew_ID()[2] == member_collection[i]->get_ID()) && (member_collection[i]->get_type() == "cabin") && member_collection[i]->get_status() == "available")
			{
				third_cabinCrew_found = true;
				vector < pair <time_t, time_t> > member_time_slot_vector = member_collection[i]->get_time_slot_vector();
				for (unsigned int n = 0; n < member_time_slot_vector.size(); n++)
				{
					if ((flight.get_start_time() >= member_time_slot_vector[n].first && flight.get_start_time() < member_time_slot_vector[n].second) || (flight.get_end_time() > member_time_slot_vector[n].first && flight.get_end_time() <= member_time_slot_vector[n].second) || ((flight.get_start_time() <= member_time_slot_vector[n].first) && (flight.get_end_time() >= member_time_slot_vector[n].second)))
					{
						third_cabinCrew_time_check = false;
					}
				}
				if (third_cabinCrew_time_check == true)
				{
					third_cabin_index = i;
				}
			}
		}
	}

	if (plane_found == false)
	{
		cout << "Cannot find a plane with this tail number or the plane you chose is on repair" << endl << "Please add a flight again with a correct plane's tail number" << endl << endl;
	}

	if (plane_found == true && seat_check == false)
	{
		cout << "The chosen airplane does not have enough seats for the flight" << endl << "Please choose another airplane" << endl << endl;
	}

	if (pilot_found == false)
	{
		cout << "Cannot find the entered pilot available at the moment" << endl << "Pilot was either not available or the input ID was not correct" << endl << endl;
	}

	if (coPilot_found == false)
	{
		cout << "Cannot find the entered co-pilot available at the moment" << endl << "Co-pilot was either not available or the input ID was not correct" << endl << endl;
	}

	if (first_cabinCrew_found == false)
	{
		cout << "Cannot find the first cabin crew member available at the moment" << endl << "Cabin crew was either not available or the input ID was not correct" << endl << endl;
	}

	if (second_cabinCrew_found == false)
	{
		cout << "Cannot find ID of the second cabin crew member available at the moment" << endl << "Cabin crew was either not available or the input ID was not correct" << endl << endl;
	}

	if (third_cabinCrew_found == false)
	{
		cout << "Cannot find ID of the third cabin crew member available at the moment" << endl << "Cabin crew was either not available or the input ID was not correct" << endl << endl;
	}

	if (pilot_found == true && pilot_time_check == false)
	{
		cout << "The chosen pilot has been assigned to another flight at this flight time" << endl << "Please select another crew member for the pilot position or change flight time" << endl << endl;
	}

	if (coPilot_found == true && coPilot_time_check == false)
	{
		cout << "The chosen co-pilot has been assigned to another flight at this flight time" << endl << "Please select another crew member for the co-pilot position or change flight time" << endl << endl;
	}

	if (first_cabinCrew_found == true && first_cabinCrew_time_check == false)
	{
		cout << "The first cabin crew member has been assigned to another flight at this flight time" << endl << "Please select another crew member for the 1st cabin crew member position or change flight time" << endl << endl;
	}

	if (second_cabinCrew_found == true && second_cabinCrew_time_check == false)
	{
		cout << "The second cabin crew member has been assigned to another flight at this flight time" << endl << "Please select another crew member for the 2nd cabin crew member position or change flight time" << endl << endl;
	}

	if (third_cabinCrew_found == true && third_cabinCrew_time_check == false)
	{
		cout << "The third cabin crew member has been assigned to another flight at this flight time" << endl << "Please select another crew member for the 3rd cabin crew member position or change flight time" << endl << endl;
	}

	if (flight_found == false && seat_check == true && plane_found == true && plane_time_check == true && pilot_found == true && pilot_time_check == true && coPilot_found == true && coPilot_time_check == true && first_cabinCrew_found == true && first_cabinCrew_time_check == true && second_cabinCrew_found == true && second_cabinCrew_time_check == true && third_cabinCrew_found == true && third_cabinCrew_time_check == true)
	{
		flight_collection.push_back(flight);
		cout << "Successfully add a flight" << endl;
		planes->Add_plane_time_slot(plane_index, flight_start_time, flight_end_time);
		crew_members->Add_member_time_slot(pilot_index, flight_start_time, flight_end_time);
		crew_members->Add_member_time_slot(coPilot_index, flight_start_time, flight_end_time);
		crew_members->Add_member_time_slot(first_cabin_index, flight_start_time, flight_end_time);
		crew_members->Add_member_time_slot(second_cabin_index, flight_start_time, flight_end_time);
		crew_members->Add_member_time_slot(third_cabin_index, flight_start_time, flight_end_time);
		flight_count++;
	}
	Store_flight();
} 

void Flights:: Edit_flight (string flight_ID, Planes* planes, CrewMembers* crew_members)
{
	string answer;
	string plane_ID;
	int member_ID;
	string start_time;
	string end_time;
	char* start_code = new char[4];
	char* end_code = new char[4];
	int passenger_count;
	string status;
	struct tm start;
	struct tm end;
	int year, month, day, hour, minute, second;
	vector <Plane> plane_collection = planes->get_plane_vector();
	vector <CrewMember*> member_collection = crew_members->get_member_vector();
	vector < pair <time_t, time_t> > time_slot;	
	
	for (unsigned int i = 0; i < flight_collection.size(); i++)
	{
		if (flight_ID == flight_collection[i].get_ID())
		{
			cout << "What do you want to edit?" << endl;
			cout << "i. Flight ID" << endl;
			cout << "ii. Tail number (plane ID)" << endl;
			cout << "iii. Pilot ID" << endl;
			cout << "iv. Co-pilot ID" << endl;
			cout << "v. 1st cabin crew ID" << endl;
			cout << "vi. 2nd cabin crew ID" << endl;
			cout << "vii. 3rd cabin crew ID" << endl;
			cout << "viii. Start time" << endl;
			cout << "ix. End time" << endl;
			cout << "x. Starting airport code" << endl;	
			cout << "xi. Ending airport code" << endl;
			cout << "xii. Number of passengers" << endl;
			cout << "xiii. Status" << endl;
			cout << "Choose an option: ";
			getline(cin, answer);
		
			if (answer == "i")
			{
				bool found = false;
				cout << "Enter new flight ID: ";
				getline(cin, flight_ID);
				for (int n = 0; n < flight_collection.size(); n++)
				{
					if (flight_ID == flight_collection[n].get_ID())
					{
						found = true;
						cout << "This new flight ID has been existed in the database. Cannot change into this new flight ID" << endl;
					}
				}
				if (found == false)
				{
					flight_collection[i].set_ID(flight_ID);
					cout << "Flight ID has been changed successfully" << endl;
				} 
			}
			else if (answer == "ii")
			{
				bool found = false;
				bool new_plane_check = false;
				bool new_plane_time_check = false;
				cout << "Enter new tail number (plane ID): ";
				getline(cin, plane_ID);

				for (int n = 0; n < planes->get_plane_vector().size(); n++)
				{
					if (plane_ID == planes->get_plane_vector()[n].get_tail_num())
					{
						found = true; break;
					}
				}

				if (found == false)
				{
					cout << "Cannot find this plane ID in the planes' list" << endl;
				} 
				else
				{
					for (unsigned int n = 0; n < plane_collection.size() ; n++)
					{
						if (plane_ID == plane_collection[n].get_tail_num() && plane_collection[n].get_status() != "on repair")
						{
							new_plane_check = true;
							time_slot = plane_collection[n].get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_plane_time_check = false;
								}
								else
								{
									new_plane_time_check = true;
									planes -> Add_plane_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_plane_check == false)
					{
						cout << "New plane's ID (tail number) is not in the list or the plane is on repair at present" << endl;
					}

					if (new_plane_check == true && new_plane_time_check == false)
					{
						cout << "The plane with the entered plane ID (tail number) has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_plane_check == true && new_plane_time_check == true)
					{
						for (unsigned int n = 0; n < plane_collection.size() ; n++)
						{
							if (flight_collection[i].get_tail_num() == plane_collection[n].get_tail_num())
							{
								time_slot = plane_collection[n].get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										planes -> Delete_plane_time_slot(n, g);
									}
								}
							}
						}
						flight_collection[i].set_tail_num(plane_ID);
						cout << "Plane ID has been changed successfully" << endl;
					}
				}
			}
			else if (answer == "iii")
			{
				bool found = false;
				bool new_member_check = false;
				bool new_member_time_check = false;
				cout << "Enter new pilot ID: ";
				cin >> member_ID;

				for (int n = 0; n < crew_members->get_member_vector().size(); n++)
				{
					if (member_ID == crew_members->get_member_vector()[n]->get_ID() && crew_members->get_member_vector()[n]->get_type() == "pilot")
					{
						found = true; break;
					} 
				}
				if (found == false)
				{
					cout << "Cannot find this pilot ID in the crew members' list" << endl;
				}
				else
				{
					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (member_ID == member_collection[n]->get_ID() && member_collection[n]->get_type() == "pilot" && member_collection[n]->get_status() == "available")
						{
							new_member_check = true;
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_member_time_check = false;
								}
								else
								{
									new_member_time_check = true;
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_member_check == false)
					{
						cout << "Entered pilot's ID is not in the list or the member is on leave/sick at present" << endl;
					}

					if (new_member_check == true && new_member_time_check == false)
					{
						cout << "The pilot has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_member_check == true && new_member_time_check == true)
					{
						for (unsigned int n = 0; n < member_collection.size() ; n++)
						{
							if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID())
							{
								time_slot = member_collection[n]->get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										crew_members -> Delete_member_time_slot(n, g);
									}
								}
							}
						}
						flight_collection[i].set_pilot_ID(member_ID);
						cout << "Pilot ID has been changed successfully" << endl;
					}
				} 
			}
			else if (answer == "iv")
			{
				bool found = false;
				bool new_member_check = false;
				bool new_member_time_check = false;
				cout << "Enter new co-pilot ID: ";
				cin >> member_ID;

				for (int n = 0; n < crew_members->get_member_vector().size(); n++)
				{
					if (member_ID == crew_members->get_member_vector()[n]->get_ID() && crew_members->get_member_vector()[n]->get_type() == "co-pilot")
					{
						found = true; break;
					} 
				}
				if (found == false)
				{
					cout << "Cannot find this co-pilot ID in the crew members' list" << endl;
				}
				else
				{
					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (member_ID == member_collection[n]->get_ID() && member_collection[n]->get_type() == "co-pilot" && member_collection[n]->get_status() == "available")
						{
							new_member_check = true;
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_member_time_check = false;
								}
								else
								{
									new_member_time_check = true;
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_member_check == false)
					{
						cout << "The entered co-pilot's ID is not in the list or the member is on leave/sick at present" << endl;
					}

					if (new_member_check == true && new_member_time_check == false)
					{
						cout << "The co-pilot with the entered ID has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_member_check == true && new_member_time_check == true)
					{
						for (unsigned int n = 0; n < member_collection.size() ; n++)
						{
							if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID())
							{
								time_slot = member_collection[n]->get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										crew_members -> Delete_member_time_slot(n, g);
									}
								}
							}
						}
						flight_collection[i].set_coPilot_ID(member_ID);
						cout << "Co-pilot ID has been changed successfully" << endl;
					}
				} 
			}
			else if (answer == "v")
			{
				bool found = false;
				bool new_member_check = false;
				bool new_member_time_check = false;
				cout << "Enter new first cabin crew ID: ";
				cin >> member_ID;

				for (int n = 0; n < crew_members->get_member_vector().size(); n++)
				{
					if (member_ID == crew_members->get_member_vector()[n]->get_ID() && crew_members->get_member_vector()[n]->get_type() == "cabin")
					{
						found = true; break;
					} 
				}
				if (found == false)
				{
					cout << "Cannot find this cabin crew member's ID in the crew members' list" << endl;
				}
				else
				{
					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (member_ID == member_collection[n]->get_ID() && member_collection[n]->get_type() == "cabin" && member_collection[n]->get_status() == "available")
						{
							new_member_check = true;
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_member_time_check = false;
								}
								else
								{
									new_member_time_check = true;
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_member_check == false)
					{
						cout << "The entered cabin member's ID is not in the list or the member is on leave/sick at present" << endl;
					}

					if (new_member_check == true && new_member_time_check == false)
					{
						cout << "The cabin member has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_member_check == true && new_member_time_check == true)
					{
						for (unsigned int n = 0; n < member_collection.size() ; n++)
						{
							if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID())
							{
								time_slot = member_collection[n]->get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										crew_members -> Delete_member_time_slot(n, g);
									}
								}
							}
						}
						int* cabinCrew_ID = flight_collection[i].get_cabinCrew_ID();
						cabinCrew_ID[0] = member_ID;
						flight_collection[i].set_cabinCrew_ID(cabinCrew_ID);
						cout << "First cabin crew ID of the flight has been changed successfully" << endl;
					}
				}			 				
			}
			else if (answer == "vi")
			{
				bool found = false;
				bool new_member_check = false;
				bool new_member_time_check = false;
				cout << "Enter new second cabin crew ID: ";
				cin >> member_ID;

				for (int n = 0; n < crew_members->get_member_vector().size(); n++)
				{
					if (member_ID == crew_members->get_member_vector()[n]->get_ID() && crew_members->get_member_vector()[n]->get_type() == "cabin")
					{
						found = true; break;
					} 
				}
				if (found == false)
				{
					cout << "Cannot find this cabin crew member's ID in the crew members' list" << endl;
				}
				else
				{
					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (member_ID == member_collection[n]->get_ID() && member_collection[n]->get_type() == "cabin" && member_collection[n]->get_status() == "available")
						{
							new_member_check = true;
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_member_time_check = false;
								}
								else
								{
									new_member_time_check = true;
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_member_check == false)
					{
						cout << "The entered cabin member's ID is not in the list or the member is on leave/sick at present" << endl;
					}

					if (new_member_check == true && new_member_time_check == false)
					{
						cout << "The cabin member has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_member_check == true && new_member_time_check == true)
					{
						for (unsigned int n = 0; n < member_collection.size() ; n++)
						{
							if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID())
							{
								time_slot = member_collection[n]->get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										crew_members -> Delete_member_time_slot(n, g);
									}
								}
							}
						}
						int* cabinCrew_ID = flight_collection[i].get_cabinCrew_ID();
						cabinCrew_ID[1] = member_ID;
						flight_collection[i].set_cabinCrew_ID(cabinCrew_ID);
						cout << "Second cabin crew ID of the flight has been changed successfully" << endl;
					}
				}			 				
			}

			else if (answer == "vii")
			{
				bool found = false;
				bool new_member_check = false;
				bool new_member_time_check = false;
				cout << "Enter new third cabin crew ID: ";
				cin >> member_ID;

				for (int n = 0; n < crew_members->get_member_vector().size(); n++)
				{
					if (member_ID == crew_members->get_member_vector()[n]->get_ID() && crew_members->get_member_vector()[n]->get_type() == "cabin")
					{
						found = true; break;
					} 
				}
				if (found == false)
				{
					cout << "Cannot find this cabin crew member's ID in the crew members' list" << endl;
				}
				else
				{
					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (member_ID == member_collection[n]->get_ID() && member_collection[n]->get_type() == "cabin" && member_collection[n]->get_status() == "available")
						{
							new_member_check = true;
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if ((flight_collection[i].get_start_time() >= time_slot[g].first && flight_collection[i].get_start_time() < time_slot[g].second) || (flight_collection[i].get_end_time() > time_slot[g].first && flight_collection[i].get_end_time() <= time_slot[g].second) || (flight_collection[i].get_start_time() <= time_slot[g].first && flight_collection[i].get_end_time() >= time_slot[g].second))
								{
									new_member_time_check = false;
								}
								else
								{
									new_member_time_check = true;
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), flight_collection[i].get_end_time());
								}
							}
						}
					}

					if (new_member_check == false)
					{
						cout << "The entered cabin member's ID is not in the list or the member is on leave/sick at present" << endl;
					}

					if (new_member_check == true && new_member_time_check == false)
					{
						cout << "The cabin member has been assigned for another flight that has time conflict with this flight" << endl << "Cannot change this flight's tail number" << endl;
					}

					if (new_member_check == true && new_member_time_check == true)
					{
						for (unsigned int n = 0; n < member_collection.size() ; n++)
						{
							if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID())
							{
								time_slot = member_collection[n]->get_time_slot_vector();
								for (unsigned int g = 0; g < time_slot.size(); g++)
								{
									if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
									{
										crew_members -> Delete_member_time_slot(n, g);
									}
								}
							}
						}
						int* cabinCrew_ID = flight_collection[i].get_cabinCrew_ID();
						cabinCrew_ID[2] = member_ID;
						flight_collection[i].set_cabinCrew_ID(cabinCrew_ID);
						cout << "Third cabin crew ID has been changed successfully" << endl;
					}
				}			 				
			}

			else if (answer == "viii")
			{
				bool start_time_check = false;
				cout << "Enter start time at GMT (yyyy/mm/dd hh:mm:ss): ";
				getline(cin, start_time);

				const char* cStart = start_time.c_str();
				sscanf(cStart, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				start.tm_year = year - 1900;
				start.tm_mon = month - 1;
				start.tm_mday = day;
				start.tm_hour = hour;
				start.tm_min = minute;
				start.tm_sec = second;
				start.tm_isdst = -1;
				time_t tStart = mktime(&start);

				if (tStart < flight_collection[i].get_end_time())
				{
					start_time_check = true;
					for (unsigned int n = 0; n < plane_collection.size() ; n++)
					{
						if (flight_collection[i].get_tail_num() == plane_collection[n].get_tail_num())
						{
							time_slot = plane_collection[n].get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
								{
									planes -> Delete_plane_time_slot(n, g);
									planes -> Add_plane_time_slot(n, tStart, flight_collection[i].get_end_time());
								}
							}
						}
					}

					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_coPilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[0] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[1] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[2] == member_collection[n]->get_ID())
						{
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
								{
									crew_members -> Delete_member_time_slot(n, g);
									crew_members -> Add_member_time_slot(n, tStart, flight_collection[i].get_end_time());
								}
							}
						}
					}
				}
		
				if (start_time_check == true)
				{
					flight_collection[i].set_start_time(tStart);
					cout << "Start time has been changed successfully" << endl;
				}
				else
				{
					cout << "Start time has to be before the end time of the flight. Cannot change the start time" << endl;
				}
			}
			else if (answer == "ix")
			{
				cout << "Enter end time at GMT (yyyy/mm/dd hh:mm:ss): ";
				getline(cin, end_time);

				const char* cEnd = end_time.c_str();
				sscanf(cEnd, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				end.tm_year = year - 1900;
				end.tm_mon = month - 1;
				end.tm_mday = day;
				end.tm_hour = hour;
				end.tm_min = minute;
				end.tm_sec = second;
				end.tm_isdst = -1;
				time_t tEnd = mktime(&end);
				bool end_time_check = false;

				if (tEnd > flight_collection[i].get_start_time())
				{
					end_time_check = true;
					for (unsigned int n = 0; n < plane_collection.size() ; n++)
					{
						if (flight_collection[i].get_tail_num() == plane_collection[n].get_tail_num())
						{
							time_slot = plane_collection[n].get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
								{
									planes -> Delete_plane_time_slot(n, g);
									planes -> Add_plane_time_slot(n, flight_collection[i].get_start_time(), tEnd);
								}
							}
						}
					}

					for (unsigned int n = 0; n < member_collection.size() ; n++)
					{
						if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_coPilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[0] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[1] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[2] == member_collection[n]->get_ID())
						{
							time_slot = member_collection[n]->get_time_slot_vector();
							for (unsigned int g = 0; g < time_slot.size(); g++)
							{ 
								if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
								{
									crew_members -> Delete_member_time_slot(n, g);
									crew_members -> Add_member_time_slot(n, flight_collection[i].get_start_time(), tEnd);
								}
							}
						}
					}
				}

				if (end_time_check == true)
				{
					flight_collection[i].set_end_time(tEnd);
					cout << "End time has been changed successfully" << endl;
				}
				else
				{
					cout << "End time has to be after the start time of the flight. Cannot change the end time" << endl;
				}
			}
			else if (answer == "x")
			{
				cout << "Enter new starting airport code: ";
				cin.getline(start_code, 4);
				flight_collection[i].set_start_airCode(start_code);
				cout << "Starting airport code has been changed successfully" << endl;
			}
			else if (answer == "xi")
			{
				cout << "Enter new ending airport code: ";
				cin.getline(end_code, 4);
				flight_collection[i].set_end_airCode(end_code);
			}
			else if (answer == "xii")
			{
				bool seat_check = false;
				cout << "Enter new number of passengers in the flight: ";
				cin >> passenger_count;

				for (int n = 0; n < planes->get_plane_vector().size(); n++)
				{
					if (passenger_count <= planes->get_plane_vector()[n].get_seat_count())
					{
						seat_check = true;
						flight_collection[i].set_passenger_count(passenger_count);
						cout << "Number of passengers has been changed successfully" << endl;
					}
				}
				if (seat_check == false)
				{
					cout << "Number of passengers exceeds the maximum seats in the chosen plane. Failed to change the number of passengers." << endl;
				}
			}
			else if (answer == "xiii")
			{
				cout << "Enter new flight status (active, completed, cancelled, unknown): ";
				getline(cin, status);
				if (status == "active" || status == "completed" || status == "cancelled" || status == "unknown")
				{
					flight_collection[i].set_status(status);
					cout << "Flight status has been changed successfully" << endl;
				}
				else
				{
					cout << "Flight status has to be in the category (active, completed, cancelled, unknown). Cannot change flight status" << endl;
				}
			}
			else
			{
				cout << "Wrong choice" << endl;
			}
		}
	}
	Store_flight();
}

void Flights:: Delete_flight(string flight_ID, Planes* planes, CrewMembers* members)
{
	vector <Plane> plane_collection = planes->get_plane_vector();
	vector <CrewMember*> member_collection = members->get_member_vector();
	vector < pair <time_t, time_t> > time_slot;

	bool flight_found = false;
	for (unsigned int i = 0; i < flight_collection.size(); i++)
	{
		if (flight_ID == flight_collection[i].get_ID())
		{
			flight_found = true;
			for (unsigned int n = 0; n < plane_collection.size() ; n++)
			{
				if (flight_collection[i].get_tail_num() == plane_collection[n].get_tail_num())
				{
					time_slot = plane_collection[n].get_time_slot_vector();
					for (unsigned int g = 0; g < time_slot.size(); g++)
					{ 
						if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
						{
							planes -> Delete_plane_time_slot(n, g);
						}
					}
				}
			}

			for (unsigned int n = 0; n < member_collection.size() ; n++)
			{
				if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_coPilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[0] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[1] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[2] == member_collection[n]->get_ID())
				{
					time_slot = member_collection[n]->get_time_slot_vector();
					for (unsigned int g = 0; g < time_slot.size(); g++)
					{ 
						if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
						{
							members -> Delete_member_time_slot(n, g);
						}
					}
				}
			}

			if (flight_found == true)
			{
				flight_collection.erase(flight_collection.begin() + i);
				cout << "Flight has been deleted successfully" << endl;	
				flight_count--;
			}
			else
			{
				cout << "Cannot find this flight ID in the flight list" << endl;
			}
		}
	}
	Store_flight();
}

void Flights:: Search_flight()
{
	string answer;
	string flight_ID;
	string tail_num;
	int member_ID;
	string start_time;
	string end_time;
	time_t tStart;
	time_t tEnd;
	char * start_code = new char[4];
	char * end_code = new char[4];
	int year, month, day, hour, minute, second;
	bool found;
	int passenger_count;
	string status;

	cout << "What criteria of flight do your want to look up?" << endl;
	cout << "i. Flight ID" << endl;
	cout << "ii. Tail number (plane ID)" << endl;
	cout << "iii. Pilot ID" << endl;
	cout << "iv. Co-pilot ID" << endl;
	cout << "v. Cabin crew ID" << endl;
	cout << "vi. Start time" << endl;
	cout << "vii. End time" << endl;
	cout << "viii. Starting airport code" << endl;	
	cout << "ix. Ending airport code" << endl;
	cout << "x. Number of passengers" << endl;
	cout << "xi. Status (active, cancelled, completed)" << endl;
	cout << "Choose an option: ";
	getline(cin, answer);
	
	if (answer == "i")
	{
		struct tm* start;
		struct tm* end;
		found = false;
		time_t start_t;
		time_t end_t;
		cout << "Enter flight ID: ";
		getline(cin, flight_ID);
		
		for (unsigned int i = 0; i< flight_collection.size(); i++)
		{
			if (flight_ID == flight_collection[i].get_ID())
			{
				found = true;
				cout << "Found a flight with ID#" << flight_collection[i].get_ID() << endl;
				cout << "Tail number (plane ID): " << flight_collection[i].get_tail_num() << endl;
				cout << "Pilot ID: " << flight_collection[i].get_pilot_ID() << endl;
				cout << "Co-pilot ID: " << flight_collection[i].get_coPilot_ID() << endl;
				cout << "1st cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[0] << endl;
				cout << "2nd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[1] << endl;
				cout << "3rd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[2] << endl;

				start_t = flight_collection[i].get_start_time();
				start = localtime (&start_t);
				char buffer[32];
				strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);
				cout << "Start time: " << buffer << endl;

				end_t = flight_collection[i].get_end_time();
				end = localtime (&end_t);
				char buffer1[32];
				strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
				cout << "End time: " << buffer1 << endl;

				cout << "Staring airport code: " << flight_collection[i].get_start_airCode() << endl;
				cout << "Ending airport code: " << flight_collection[i].get_end_airCode() << endl;
				cout << "Number of passenger: " << flight_collection[i].get_passenger_count() << endl;
				cout << "Status: " << flight_collection[i].get_status() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find any flight with this flight ID" << endl;
		}
	}

	else if (answer == "ii")
	{
		found = false;
		cout << "Enter plane's tail number (plane ID): ";
		getline(cin, tail_num);
		
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (tail_num == flight_collection[i].get_tail_num())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find any flight with this tail number" << endl;
		}
	}

	else if (answer == "iii")
	{
		found = false;
		cout << "Enter pilot ID: ";
		cin >> member_ID;
		
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (member_ID == flight_collection[i].get_pilot_ID())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find any flight with this pilot ID" << endl;
		}
	}

	else if (answer == "iv")
	{
		found = false;
		cout << "Enter co-pilot ID: ";
		cin >> member_ID;
		
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (member_ID == flight_collection[i].get_coPilot_ID())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this co-pilot ID" << endl;
		}
	}

	else if (answer == "v")
	{
		found = false;
		cout << "Enter cabin crew ID: ";
		cin >> member_ID;
		
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (member_ID == flight_collection[i].get_cabinCrew_ID()[k])
				{
					found = true;
					cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
				}
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this cabin crew ID" << endl;
		}
	}

	else if (answer == "vi")
	{
		struct tm start;
		found = false;
		cout << "Enter start time: ";
		getline(cin, start_time);

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

		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (tStart == flight_collection[i].get_start_time())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this start time" << endl;
		}
	}

	 else if (answer == "vii")
	{
		struct tm end;
		found = false;
		cout << "Enter end time: ";
		getline(cin, end_time);

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

		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (tEnd == flight_collection[i].get_end_time())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this end time" << endl;
		}
	}

	else if (answer == "viii")
	{
		cout << "Enter starting airport code: ";
		cin.getline(start_code, 4);
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if ((strcmp (start_code, flight_collection[i].get_start_airCode())) == 0)
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this starting airport code" << endl;
		}
	}

	else if (answer == "ix")
	{
		cout << "Enter ending airport code: ";
		cin.getline(end_code, 4);
		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if ((strcmp (end_code, flight_collection[i].get_end_airCode())) == 0)
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}

		if (found == false)
		{
			cout << "Cannot find a flight with this ending airport code" << endl;
		}
	}

	else if (answer == "x")
	{
		cout << "Enter number of passengers: ";
		cin >> passenger_count;

		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (passenger_count == flight_collection[i].get_passenger_count())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}
		if (found == false)
		{
			cout << "Cannot find a flight with this ending number of passengers" << endl;
		}
	}

	else if (answer == "xi")
	{
		cout << "Enter flight's status: ";
		getline(cin, status);

		for (unsigned int i = 0; i < flight_collection.size(); i++)
		{
			if (status == flight_collection[i].get_status())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			}
		}
		if (found == false)
		{
			cout << "Cannot find a flight with this flight status" << endl;
		}
	}

	else
	{
		cout << "Wrong choice" << endl;
	}
}

void Flights:: Print_flight(string flight_ID)
{
	bool found;
	time_t start_t;
	time_t end_t;
	char buffer[32];
	char buffer1[32];

	for (unsigned int i = 0; i< flight_collection.size(); i++)
	{
		if (flight_ID == flight_collection[i].get_ID())
		{
			struct tm* start = new tm[1];
			struct tm* end = new tm[1];
			found = true;
			cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
			cout << "Tail number (plane ID): " << flight_collection[i].get_tail_num() << endl;
			cout << "Pilot ID: " << flight_collection[i].get_pilot_ID() << endl;
			cout << "Co-pilot ID: " << flight_collection[i].get_coPilot_ID() << endl;
			cout << "1st cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[0] << endl;
			cout << "2nd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[1] << endl;
			cout << "3rd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[2] << endl;

			start_t = flight_collection[i].get_start_time();
			start = localtime (&start_t);
			strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);
			cout << "Start time: " << buffer << endl;

			end_t = flight_collection[i].get_end_time();
			end = localtime (&end_t);
			strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
			cout << "End time: " << buffer1 << endl;

			cout << "Staring airport code: " << flight_collection[i].get_start_airCode() << endl;
			cout << "Ending airport code: " << flight_collection[i].get_end_airCode() << endl;
			cout << "Number of passenger: " << flight_collection[i].get_passenger_count() << endl;
			cout << "Status: " << flight_collection[i].get_status() << endl;
			cout << endl;
		}
	}

	if (found == false)
	{
		cout << "Cannot find any flight with this flight ID. No information printed" << endl;
	}
}

void Flights:: Print_flights()
{
	time_t start_t;
	struct tm* start;
	time_t end_t;
	struct tm* end;
	char buffer[32];
	char buffer1[32];

	if (flight_count == 0)
	{
		cout << "No flight has been added yet" << endl;
	}

	for (unsigned int i = 0; i< flight_collection.size(); i++)
	{
		cout << i+1 << "." << endl;
		cout << "Flight ID: " << flight_collection[i].get_ID() << endl;
		cout << "Tail number (plane ID): " << flight_collection[i].get_tail_num() << endl;
		cout << "Pilot ID: " << flight_collection[i].get_pilot_ID() << endl;
		cout << "Co-pilot ID: " << flight_collection[i].get_coPilot_ID() << endl;
		cout << "1st cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[0] << endl;
		cout << "2nd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[1] << endl;
		cout << "3rd cabin crew ID: " << flight_collection[i].get_cabinCrew_ID()[2] << endl;

		start_t = flight_collection[i].get_start_time();
		start = localtime (&start_t);
		strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);
		cout << "Start time: " << buffer << endl;

		end_t = flight_collection[i].get_end_time();
		end = localtime (&end_t);
		strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
		cout << "End time: " << buffer1 << endl;

		cout << "Staring airport code: " << flight_collection[i].get_start_airCode() << endl;
		cout << "Ending airport code: " << flight_collection[i].get_end_airCode() << endl;
		cout << "Number of passenger: " << flight_collection[i].get_passenger_count() << endl;
		cout << "Status: " << flight_collection[i].get_status() << endl;
		cout << endl;
	}
}

void Flights:: Print_schedule_plane(string plane_ID, Planes planes)
{
	bool found = false;
	time_t start_t;
	struct tm* start;
	time_t end_t;
	struct tm* end;
	char buffer[32];
	char buffer1[32];
	
	vector <Plane> plane_collection = planes.get_plane_vector();
	vector < pair <time_t, time_t> > plane_time_slot;

	for (unsigned int i = 0; i < plane_collection.size(); i++)
	{
		if (plane_ID == plane_collection[i].get_tail_num())
		{
			planes.Sort_time(i);
			plane_time_slot = planes.get_plane_vector()[i].get_time_slot_vector();
		}
	}

	for (unsigned int n = 0; n < plane_time_slot.size(); n++)
	{
		for (unsigned int g = 0; g < flight_collection.size(); g++)
		{
			if (plane_ID == flight_collection[g].get_tail_num() && plane_time_slot[n].first == flight_collection[g].get_start_time())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[g].get_ID() << endl;
				start_t = flight_collection[g].get_start_time();
				start = localtime (&start_t);
				strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);
				cout << "Start time: " << buffer << endl;

				end_t = flight_collection[g].get_end_time();
				end = localtime (&end_t);
				strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
				cout << "End time: " << buffer1 << endl;
				cout << endl;
			}
		}
	}

	if (found == false)
	{
		cout << "Cannot find any flight assigned for this plane" << endl;
	}	
}

void Flights:: Print_schedule_crew(int member_ID, CrewMembers crew_members)
{
	bool found = false;
	time_t start_t;
	struct tm* start;
	time_t end_t;
	struct tm* end;
	char buffer[32];
	char buffer1[32];
	
	vector <CrewMember*> member_collection = crew_members.get_member_vector();
	vector < pair <time_t, time_t> > member_time_slot;

	for (unsigned int i = 0; i < member_collection.size(); i++)
	{
		if (member_ID == member_collection[i]->get_ID())
		{
			crew_members.Sort_time(i);
			member_time_slot = crew_members.get_member_vector()[i]->get_time_slot_vector();
		}
	}

	for (unsigned int n = 0; n < member_time_slot.size(); n++)
	{
		for (unsigned int g = 0; g < flight_collection.size(); g++)
		{
			if ((member_ID == flight_collection[g].get_pilot_ID() || member_ID == flight_collection[g].get_coPilot_ID() || member_ID == flight_collection[g].get_cabinCrew_ID()[0] || member_ID == flight_collection[g].get_cabinCrew_ID()[1] || member_ID == flight_collection[g].get_cabinCrew_ID()[2]) && member_time_slot[n].first == flight_collection[g].get_start_time())
			{
				found = true;
				cout << "Flight ID: " << flight_collection[g].get_ID() << endl;
				start_t = flight_collection[g].get_start_time();
				start = localtime (&start_t);
				strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", start);
				cout << "Start time: " << buffer << endl;

				end_t = flight_collection[g].get_end_time();
				end = localtime (&end_t);
				strftime(buffer1, 32, "%Y/%m/%d %H:%M:%S", end);
				cout << "End time: " << buffer1 << endl;

				cout << endl;
			}
		}
	}

	if (found == false)
	{
		cout << "Cannot find any flight assigned for this crew member" << endl;
	}		
}

void Flights:: Update_flight()
{
	time_t now = time(0);
	for (unsigned int i = 0; i< flight_collection.size(); i++)
	{
		if (flight_collection[i].get_end_time() <= now)
		{
			flight_collection[i].set_status("completed");
		}
	}
	cout << "Successfully updated all flights based on current time" << endl;
	Store_flight();		
}

void Flights:: Delete_inactive_flight(Planes* planes, CrewMembers* members)
{
	vector <Plane> plane_collection = planes->get_plane_vector();
	vector <CrewMember*> member_collection = members->get_member_vector();
	vector < pair <time_t, time_t> > time_slot;
	bool found = false;

	for (unsigned int i = 0; i < flight_collection.size(); i++)
	{
		if(flight_collection[i].get_status() == "completed" || flight_collection[i].get_status() == "cancelled")
		{
			found = true;
			for (unsigned int n = 0; n < plane_collection.size() ; n++)
			{
				if (flight_collection[i].get_tail_num() == plane_collection[n].get_tail_num())
				{
					time_slot = plane_collection[n].get_time_slot_vector();
					for (unsigned int g = 0; g < time_slot.size(); g++)
					{ 
						if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
						{
							planes -> Delete_plane_time_slot(n, g);
						}
					}
				}
			}

			for (unsigned int n = 0; n < member_collection.size() ; n++)
			{
				if (flight_collection[i].get_pilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_coPilot_ID() == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[0] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[1] == member_collection[n]->get_ID() || flight_collection[i].get_cabinCrew_ID()[2] == member_collection[n]->get_ID())
				{
					time_slot = member_collection[n]->get_time_slot_vector();
					for (unsigned int g = 0; g < time_slot.size(); g++)
					{ 
						if (flight_collection[i].get_start_time() == time_slot[g].first && flight_collection[i].get_end_time() == time_slot[g].second)
						{
							members -> Delete_member_time_slot(n, g);
						}
					}
				}
			}

			flight_collection.erase(flight_collection.begin()+i);
			flight_count--;
		}
	}
	if (found == false)
	{
		cout << "All flights' status in the flight's list are either active or unknown right now. Nothing deleted" << endl; 
	}
	else
	{
		cout << "Successfully deleted all completed or cancelled flight(s)" << endl;
	}
	Store_flight();
}

void Flights:: Load_flight()
{
	flight_collection.clear();

	ifstream fin;
	string flight_ID;
	string tail_num;
	int member_ID;
	int* cabinCrew_ID;
	string start_code;
	string end_code;
	char* start_airCode;
	char* end_airCode;
	int passenger_count;
	string status;
	string start_time;
	string end_time;
	time_t tStart;
	time_t tEnd;
	struct tm start;
	struct tm end;
	int year, month, day, hour, minute, second;
	int flight_count_file = flight_count_in_file();

	fin.open("flights");
	Flight flight;
	for (int i = 0; i < flight_count_file; i++)
	{
		cabinCrew_ID = new int[3];
		start_airCode = new char[4];
		end_airCode = new char[4];

		getline(fin, flight_ID,'\t');
		flight.set_ID(flight_ID);
		getline(fin, tail_num, '\t');
		flight.set_tail_num(tail_num);
		fin >> member_ID;
		flight.set_pilot_ID(member_ID);
		fin >> member_ID;
		flight.set_coPilot_ID(member_ID);
		fin >> member_ID;
		cabinCrew_ID[0] = member_ID;
		fin >> member_ID;
		cabinCrew_ID[1] = member_ID;
		fin >> member_ID;
		cabinCrew_ID[2] = member_ID;		
		flight.set_cabinCrew_ID(cabinCrew_ID);
		fin.ignore();

		getline(fin, start_time, '\t');
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
		flight.set_start_time(tStart);

		getline(fin, end_time, '\t');
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
		flight.set_end_time(tEnd);

		getline(fin, start_code, '\t');
		strcpy(start_airCode, start_code.c_str());
		flight.set_start_airCode(start_airCode);
		getline(fin, end_code, '\t');
		strcpy(end_airCode, end_code.c_str());
		flight.set_end_airCode(end_airCode);
		fin >> passenger_count;
		fin.ignore();
		flight.set_passenger_count(passenger_count);
		getline(fin, status);
		flight.set_status(status);
		flight_collection.push_back(flight);	
	}
	set_flight_count(flight_count_file);
	fin.close();
}