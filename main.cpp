/*Name: Yen Pham		yenpham@my.unt.edu
Class: CSCE1040
Instructor: David Keathly
Description: The purpose of this assignment is to write a program for an airline
*/

#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include "Plane.h"
#include "Planes.h"
#include "CrewMember.h"
#include "CrewMembers.h"
#include "Flight.h"
#include "Flights.h"

using namespace std;

int main()
{
// Display name, EUID, e-mail address, the department name, and course number
	cout << "\n+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1040 - Computer Science 2        |" << endl;
	cout << "|   Yen Pham    yhp0005    yenpham@my.unt.edu  |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl;
	int answer = 0;
	char answer1 = 'n';
	char answer2;
	Planes planes;
	CrewMembers crew_members;
	Flights flights;

	planes.Load_plane();
	crew_members.Load_member();
	flights.Load_flight();

	do
	{
		cout << "+-------------Mean Green Airline------------+ " << endl;
		cout << "1. Plane" << endl;
		cout << "2. Crew member" << endl;
		cout << "3. Flight" << endl;
		cout << "4. Quit" << endl;
		cout << "+-------------------------------------------+ " << endl;
		cout << "Choose an option: ";
		cin >> answer;
		cin.ignore();
		cout << endl;

		if (answer == 4)
		{
			break;
		}

		else if (answer == 1)
		{
			Plane plane;
			string make;
			int model;
			string tail_num;
			int seat_count = 0;
			int range;
			string status;

			do
			{
				cout << "************Airplane Menu****************" << endl;
				cout << "a. Add a plane" << endl;
				cout << "b. Edit a plane" << endl;
				cout << "c. Delete a plane" << endl;
				cout << "d. Search a plane" << endl;
				cout << "e. Print a plane's detail" << endl;
				cout << "f. Print planes' list" << endl;
				cout << "j. Back to main menu" << endl;
				cout << "Choose an option: ";
				cin >> answer2;
				cin.ignore();
				cout << endl;

				if (answer2 == 'a')
				{
					cout << "Enter airplane's make: ";
					getline (cin, make);
					plane.set_make(make);

					cout << "Enter airplane's model: ";
					cin >> model;	
					cin.ignore();
					plane.set_model(model);			
					
					cout << "Enter airplane's tail number: ";
					getline (cin, tail_num);
					plane.set_tail_num(tail_num);

					cout << "Enter airplane's number of seat: ";
					cin >> seat_count;
					plane.set_seat_count(seat_count);

					cout << "Enter airplane's range in miles: ";
					cin >> range;
					cin.ignore();
					plane.set_range (range);

					do
					{
						cout << "Enter airplane's status (out, in , on repair, unknown): ";
						getline(cin, status);
						if (status != "out" && status != "in" && status != "on repair" && status != "unknown")
						{
							cout << "Status entered was not in the category" << endl;
						}
					} while (status != "out" && status != "in" && status != "on repair" && status != "unknown");

					plane.set_status(status);
					planes.Add_plane(plane);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'b')
				{
					cout << "Enter plane's tail number: ";
					getline (cin, tail_num);
					planes.Edit_plane(tail_num);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'c')
				{
					cout << "Enter plane's tail number: ";
					getline (cin, tail_num);
					planes.Delete_plane(tail_num);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'd')
				{
					planes.Search_plane();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'e')
				{
					cout << "Enter plane's tail number: ";
					getline (cin, tail_num);
					planes.Print_plane(tail_num);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'f')
				{
					planes.Print_planes();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'j')
				{
					cout << endl;
					break;
				}
				
				else
				{
					cout << "Wrong choice" << endl << endl;
					answer1 = 'y';
				}

			} while (answer1 == 'y');
		}

		else if (answer == 2)
		{
			do
			{
				CrewMember *crew_member;
				Pilot* pilot;
				CoPilot* coPilot;
				CabinCrew* cabinCrew;
				string name;
				int ID;
				string type;
				string status;
				char* rating_code;
				string cabin_position;
				cout << "***********Crew Member Menu *************" << endl;
				cout << "a. Add a crew member" << endl;
				cout << "b. Edit a crew member" << endl;
				cout << "c. Delete a crew member" << endl;
				cout << "d. Search a crew member" << endl;
				cout << "e. Print a crew member's detail" << endl;
				cout << "f. Print crew members' list" << endl;
				cout << "j. Back to main menu" << endl;
				cout << "Choose an option: ";
				cin >> answer2;
				cin.ignore();
				cout << endl;

				if (answer2 == 'a')
				{
					do
					{
						cout << "Enter crew member's type (pilot, co-pilot, cabin): ";
						getline(cin, type);
						if (type != "pilot" && type != "co-pilot" && type != "cabin")
						{
							cout << "Crew member's type has to be in the category (pilot, co-pilot, cabin)" << endl;
						}
					} while (type != "pilot" && type != "co-pilot" && type != "cabin");

					if (type == "pilot")
					{
						pilot = new Pilot;
						crew_member = pilot;
					}

					else if (type == "co-pilot")
					{
						coPilot = new CoPilot;
						crew_member = coPilot;
					}

					else
					{
						cabinCrew = new CabinCrew;
						crew_member = cabinCrew;
					}

					crew_member->set_type(type);

					cout << "Enter crew member's name: ";
					getline(cin, name);
					crew_member->set_name(name);
		
					cout << "Enter crew member's ID: ";
					cin >> ID;
					cin.ignore();
					crew_member->set_ID(ID);

					do
					{
						cout << "Enter crew member's status (available, on leave, sick, unknown): ";
						getline(cin, status);

						if (status != "available" && status!= "on leave" && status != "sick" && status != "unknown")
						{
							cout << "Status entered was not in the category" << endl;
						}
					} while (status != "available" && status!= "on leave" && status != "sick" && status != "unknown");

					crew_member->set_status(status);

					if (type == "pilot")
					{
						rating_code = new char [6];
						cout << "Enter pilot's rating code (5 characters): ";
						cin.getline(rating_code, 6);
						static_cast <Pilot*> (crew_member) -> set_rating_code(rating_code);
					}
					else if (type == "co-pilot")
					{
						rating_code = new char [5];
						cout << "Enter co-pilot's rating code (4 characters): ";
						cin.getline(rating_code, 5);
						static_cast <CoPilot*> (crew_member) -> set_rating_code(rating_code);
					}
					else
					{
						cout << "Enter cabin's position (first class, business class, economy front, economy rear, lead): ";
						getline (cin, cabin_position);
						static_cast <CabinCrew*> (crew_member) -> set_cabin_position(cabin_position);
					}
					crew_members.Add_member(crew_member);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'b')
				{
					cout << "Enter crew member's ID: ";
					cin >> ID;
					crew_members.Edit_member(ID);
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'c')
				{
					cout << "Enter crew member's ID: ";
					cin >> ID;
					crew_members.Delete_member(ID);
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'd')
				{
					crew_members.Search_member();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'e')
				{
					cout << "Enter crew member's ID: ";
					cin >> ID;
					crew_members.Print_member(ID);
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'f')
				{
					crew_members.Print_members();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'j')
				{
					cout << endl;
					break;
				}
				
				else
				{
					cout << "Wrong choice" << endl << endl;
					answer1 = 'y';
				}

			} while (answer1 == 'y');
		}

		else if (answer == 3)
		{
			do
			{	
				Flight flight;
				string flight_ID;
				string tail_num;
				int pilot_ID;
				int coPilot_ID;
				int* cabinCrew_ID;
				string start_time;
				string end_time;
				time_t tStart;
				time_t tEnd;
				char* start_code = new char[4];
				char* end_code = new char[4];
				int passenger_count;
				string status;

				int year, month, day, hour, minute, second;
				cout << "*************Flight Menu********************" << endl;
				cout << "a. Add a flight" << endl;
				cout << "b. Edit a flight" << endl;
				cout << "c. Update flight(s) based on current time" << endl;
				cout << "d. Delete a flight" << endl;
				cout << "e. Delete cancelled or completed flight(s)" << endl;
				cout << "f. Search a flight" << endl;
				cout << "g. Print a flight's detail" << endl;
				cout << "h. Print flights' list" << endl;
				cout << "i. Print flight's schedule for a plane" << endl;
				cout << "j. Print flight's schedule for a crew member" << endl;
				cout << "k. Back to main menu" << endl;
				cout << "Choose an option: ";
				cin >> answer2;
				cin.ignore();
				cout << endl;

				if (answer2 == 'a')
				{					
					struct tm start;
					struct tm end;

					cout << "Enter flight's ID: ";
					getline(cin, flight_ID);
					flight.set_ID (flight_ID);					

					cout << "Enter plane's ID: ";
					getline (cin, tail_num);
					flight.set_tail_num (tail_num);

					cout << "Enter pilot's ID: ";
					cin >> pilot_ID;
					flight.set_pilot_ID(pilot_ID);

					cout << "Enter co-pilot's ID: ";
					cin >> coPilot_ID;
					flight.set_coPilot_ID(coPilot_ID);

					cabinCrew_ID = new int [3];
					for (int i = 0; i< 3; i++)
					{
						cout << "Enter the #" << i+1 << " cabin crew's ID: ";
						cin >> cabinCrew_ID[i];
					}
					cin.ignore();
					flight.set_cabinCrew_ID(cabinCrew_ID);
					
					cout << "Enter flight's start time in GMT (yyyy/mm/dd hh:mm:ss): ";
					getline (cin, start_time);
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

					do
					{
						cout << "Enter flight's end time in GMT (yyyy/mm/dd hh:mm:ss): ";
						getline (cin, end_time);
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
						if (tEnd < tStart)
						{		
							cout << "End time has to be after start time. Please enter the end time again" << endl;
						}

					} while (tEnd <= tStart);

					flight.set_end_time(tEnd);
				
					cout << "Enter starting airport code (3 characters): ";
					cin.getline(start_code, 4);
					flight.set_start_airCode(start_code);

					cout << "Enter ending airport code (3 characters): ";
					cin.getline(end_code, 4);
					flight.set_end_airCode(end_code);

					cout << "Enter number of passengers booked this flight: ";
					cin >> passenger_count;
					flight.set_passenger_count(passenger_count);
					cin.ignore();
					do
					{
						cout << "Enter flight's status (active, cancelled, completed, unknown): ";
						getline(cin, status);
						if (status != "active" && status != "cancelled" && status != "completed")
						{
							cout << "Status entered was not in the category" << endl;
						}
					} while (status != "active" && status != "cancelled" && status != "completed");
					flight.set_status(status);
					cout << endl;
											
					flights.Add_flight(flight, &planes, &crew_members);
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'b')
				{
					cout << "Enter flight's ID: ";
					getline (cin, flight_ID);
					flights.Edit_flight(flight_ID, &planes, &crew_members); 

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'c')
				{
					flights.Update_flight();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;					
				}

				else if (answer2 == 'd')
				{
					cout << "Enter flight's ID: ";
					getline (cin, flight_ID);
					flights.Delete_flight(flight_ID, &planes, &crew_members); 

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'e')
				{
					flights.Delete_inactive_flight(&planes, &crew_members);
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'f')
				{
					flights.Search_flight();

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'g')
				{
					cout << "Enter flight's ID: ";
					getline (cin, flight_ID);
					flights.Print_flight(flight_ID);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'h')
				{
					flights.Print_flights();
					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'i')
				{
					cout << "Enter plane's tail number: ";
					getline (cin, tail_num);
					flights.Print_schedule_plane(tail_num, planes);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'j')
				{
					int member_ID;
					cout << "Enter crew member's ID: ";
					cin >> member_ID;
					flights.Print_schedule_crew(member_ID, crew_members);

					cout << "Would you like to continue? (y/n): ";
					cin >> answer1;
					cout << endl;
				}

				else if (answer2 == 'k')
				{
					cout << endl;
					break;
				}
		
				else
				{
					cout << "Wrong choice" << endl << endl;
					answer1 = 'y';
				}
			} while (answer1 == 'y');
		}

		else
		{
			cout << "Wrong choice" << endl << endl;
		}
	}while (answer != 4);
	planes.Store_plane();
	crew_members.Store_member();
	flights.Store_flight();
	return 0;
}