#include "stdafx.h"
#pragma warning(disable:4996) //Disable the warning generated during execution due to use of local_time() function.
#include "Functions.h" //Include the Header File


Person* PersonData; // Array of Guests from which random people will be taken, made into groups and will be entered to a room
string** guestarray; // For the Parsing of the names.txt file which has Guest Information. will be deleted in GetGuestNames Function
int arrsize = 0; // The array size of PersonData array.
Floor Hotel_Floors[3] = { Floor(1),Floor(2),Floor(3) }; // The Array contains all 3 Floors of the hotel. All Floors are initialized.

void TimeDelay(int delay) //For the delay of 1.5 seconds for the execution
{
	for (int i = delay; i>0; i--)
	{
		cout << ".";
		Sleep(500); // Sleep for 500 miliseconds, and print a dot on the screen for every 0.5 seconds.
	}
	cout << endl;

}

void BookRoom(Room &room, Person guest[], Date &bookdate, Time &booktime,int DaystoStay) //Books a Room for a guest party if the Occupancy matches the number of guests
{
	for (int i = 0; i < room.Occupancy; i++)
	{
		room.BookedTo[i] = guest[i].GetName();
		room.Guests[i] = guest[i];

	}
	room.Refrigerator_Fill();
	room.isBooked = true;
	room.Bookedon = bookdate;
	room.Checkouton = bookdate.DateAfterDays(DaystoStay);
	room.StayDays = DaystoStay;
	room.Charges = room.StayDays * room.Occupancy * 400;
	room.BookingTime = booktime;
	room.AllCustomers[room.CustomerNo] = CustomersInfo(room.Occupancy, bookdate, booktime, guest);
	room.AllCustomers[room.CustomerNo].DaysStayed = DaystoStay;
	room.AllCustomers[room.CustomerNo].rentpaid = room.Charges;
	room.AllCustomers[room.CustomerNo].CheckoutDate = room.Checkouton;
	
}

void ChkoutRoom(Room &room) //Checks out the Guests staying in the room. Also increments the CustomerNo for room, denoting the customer currently staying in the room.
{
	room.Checkout();
	room.AllCustomers[room.CustomerNo].Chkouttime = Time(to_string(rand() % 24) + "/" + to_string(rand() % 60) + "/" + to_string(rand() % 60));
	room.CustomerNo++;
}

bool GetGuestNames() // Parses the names.txt file,initializes Person Objects with the contents of the file and fills the array of guests
{
	ifstream countlines("names.txt");
	ifstream guestnames("names.txt");
	string guestinfo;
	string unused;

	string guests;
	/*guestnames.open("names.txt");
	countlines.open("names.txt");*/
	if (guestnames.good()) {
		while (getline(countlines, unused))
		{
			arrsize++;
		}
		guestarray = new string*[arrsize];
		PersonData = new Person[arrsize];
		for (int i = 0; getline(guestnames, guestinfo); i++)
		{
			guestarray[i] = new string[4];
			istringstream info(guestinfo);
			for (int j = 0; getline(info, guests, ','); j++)
			{
				guestarray[i][j] = guests;
			}
		}
		for (int i = 0; i < arrsize; i++)
		{
			PersonData[i] = Person(guestarray[i][1], guestarray[i][2], guestarray[i][3]);
		}

		delete[] * guestarray;
		return true;
	}
	else cout << "names.txt file not found. Please put the file in the same directory as the program. Each entry should be like this \n"
		<< "<SerialNumber>, <Name>, M / dd / YYYY, <ID Number>";
	return false;
}

void ConsolidatedLog(int days,stringstream& checkins, stringstream& checkouts,int chkins,int chkouts,int money) // Prepares the final Simulation log
{
	ofstream consolidatedlog;
	consolidatedlog.open("Simulation Log.txt",ios_base::trunc);

	consolidatedlog << string(40, '~') << endl;
	consolidatedlog << string(8,' ') << "Hotel Management Simulation Log" << endl;
	consolidatedlog << string(40, '~') << endl << endl;

	consolidatedlog << "Simulation Ran For " << days << " Days" << endl << endl;

	consolidatedlog << string(40, '~') << endl;
	consolidatedlog << string(12,' ') << "Hotel Check-Ins" << endl;
	consolidatedlog << string(40, '~') << endl << endl;
	consolidatedlog << checkins.str() << endl << endl;
	consolidatedlog << string(40, '~') << endl;
	consolidatedlog << string(12, ' ') << "Hotel Check-Outs" << endl;
	consolidatedlog << string(40, '~') << endl << endl;
	consolidatedlog << checkouts.str() << endl << endl;

	consolidatedlog << string(41, '-') << endl;
	consolidatedlog << string(10, ' ') << "Total Check-Ins : " << chkins << endl;
	consolidatedlog << string(10, ' ') << "Total Check-Outs : " << chkouts << endl;
	consolidatedlog << string(7, ' ') << "Total Hotel Income : " << money << endl;
	consolidatedlog << string(41, '-') << endl << endl;
}


Date DateToday() //Generates Today's Date as Date Object.
{
	string date;
	auto t = time(NULL);
	auto tm = *localtime(&t);
	stringstream ss;
	ss << (put_time(&tm, "%d/%m/%Y"));
	ss >> date;
	Date today = Date(date);
	return today;
}

Time TimeNow() // Generates System Time as a Time Object
{
	string timer;
	auto t = time(NULL);
	auto tm = *localtime(&t);
	stringstream ss;
	ss << (put_time(&tm, "%H/%M/%S"));
	ss >> timer;
	Time now = Time(timer);
	return now;
}

void simulation(int daysToSimulate) // Runs the Hotel Management Simulation for specified Number of days.
{
	stringstream Checkins("", ios_base::app | ios_base::out); //The StringStream containing checkin info, will be used for the log
	stringstream Checkouts("", ios_base::app | ios_base::out);////The StringStream containing checkout info, will be used for the log
	int checkins = 0;
	int checkouts = 0;
	int checkoutsofday;
	int rent = 0;

	Person** guestgroups; //will be used to contain random number of guest parties
	Date date = DateToday();

	cout << "Starting Simulation";
	TimeDelay(3);
	cout << endl;

	for (int day = 1; day <= daysToSimulate; day++)
	{
		checkoutsofday = 0;
		system("CLS");
		cout << "Simulating Day " << day;
		TimeDelay(3);
		cout << string(30, '-') << endl;
		cout << string(12, ' ') << "Day " << day << endl;
		cout << string(30, '-') << endl;

		cout << endl << string(40, '*') << endl << "CHECK IN INFORMATION" << endl << string(40, '*') << endl << endl;

		//Booking Process
		int NumofGuestGroups = 5 + rand() % 6; // The Number of Guests Groups that are going to book a room
		guestgroups = new Person*[NumofGuestGroups]; // Make an array of the Guest Groups
		for (int i = 0; i < NumofGuestGroups; i++) // Fill the array with the Guest Groups
		{
			int NumOfGuests = 2 + (rand() % 4); // Num of Guests in each group is 2 to 5
			guestgroups[i] = new Person[NumOfGuests]; // for every group there is a number of guests
			for (int guests = 0; guests < NumOfGuests; guests++) // iterate and fill the array of each guest group with guest objects
			{
				int personnumber = rand() % arrsize; // get a random person to put in the array
				while (PersonData[personnumber].inRoom == true) // if the person is already in a group, then put someone else who is not in a group or room
				{
					personnumber = rand() % arrsize; // change the person randomly until a free person is found
				}
				guestgroups[i][guests] = PersonData[personnumber]; // put the person as object in the guest group array
				guestgroups[i][guests].inRoom = true; // set the inRoom attribute so that the person can't be added to another group or room
			}

			// Now iterate into the floors and find a room which can accomodate the guest group

			for (int floor = 0; floor < 3; floor++)
			{
				for (int room = 0; room < 10; room++)
				{
					if (Hotel_Floors[floor].Rooms[room].Occupancy == NumOfGuests && Hotel_Floors[floor].Rooms[room].isBooked == false)
					{
						string bookingtime = to_string(rand() % 24) + "/" + to_string(rand() % 60) + "/" + to_string(rand() % 60);

						BookRoom(Hotel_Floors[floor].Rooms[room], guestgroups[i], date, Time(bookingtime), 1 + rand() % 10);
						
						cout << string(45, '~') << endl;
						Checkins << string(45, '~') << endl;
						cout << "Room No. " << Hotel_Floors[floor].Rooms[room].Room_No << " has been Booked for Guest No." << i << endl;
						Checkins << "Room No. " << Hotel_Floors[floor].Rooms[room].Room_No << " has been Booked for Guest No." << i << endl;
						Hotel_Floors[floor].Rooms[room].DisplayBookingInfo();
						Hotel_Floors[floor].Rooms[room].DisplayBookingInfo(Checkins);
						rent += Hotel_Floors[floor].Rooms[room].Charges;
						checkins++;
						floor = 4; // since these are used in conditions, we change these values so that the
						room = 11; // loop will break, as we can manipulate these values as flags for the loop
					}
				}
			}
		}
		//Consumption of Drinks
		cout << string(30, '-') << endl;
		cout << string(3, ' ') << "Refrigerator Replenishes" << endl;
		cout << string(30, '-') << endl << endl;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Hotel_Floors[i].Rooms[j].isBooked)
				{
					int ConsumedDrinks = rand() % 10;
					for (int drink = 0; drink < ConsumedDrinks; drink++)
					{
						Hotel_Floors[i].Rooms[j].Refrigerator[drink].isempty = true; //Changes the consumption flag to true to denote that the drink has been consumed
						Hotel_Floors[i].Rooms[j].AllCustomers[Hotel_Floors[i].Rooms[j].CustomerNo].ConsumedDrinks[drink + Hotel_Floors[i].Rooms[j].Consumed_Drinks] = Hotel_Floors[i].Rooms[j].Refrigerator[drink]; //update info for the current customer
					}
					if (ConsumedDrinks >= 7)
					{
						Hotel_Floors[i].Rooms[j].Refrigerator_Fill();
						cout << "Refrigerator Replenished in Room " << Hotel_Floors[i].Rooms[j].Room_No << endl;
					}
					Hotel_Floors[i].Rooms[j].Consumed_Drinks += ConsumedDrinks; //increment the number of consumed drinks
					Hotel_Floors[i].Rooms[j].AllCustomers[Hotel_Floors[i].Rooms[j].CustomerNo].Drinksdrunk = Hotel_Floors[i].Rooms[j].Consumed_Drinks; //increment the number of consumed drinks for the current customer of the room
				}
			}
		}

		if (checkins == 0)
		{
			cout << endl << "No Checkins Today! :(" << endl;
		}

		//Checkout

		cout << endl << string(30, '*') << endl;
		cout << string(4,' ') << "CHECK OUT INFORMATION" << string(6, ' ')  << endl;
		cout << string(30, '*') << endl << endl;


		// Iterate into every room and check if the checkout date for the guests staying in the room is the current simulation day or not
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Hotel_Floors[i].Rooms[j].isBooked && Hotel_Floors[i].Rooms[j].Checkouton.ShowDate() == date.ShowDate())
				{
					Checkouts << string(55, '~') << endl;
					 
					Time checkingouttime = Time(to_string(rand() % 24) + "/" + to_string(rand() % 60) + "/" + to_string(rand() % 60));
					Hotel_Floors[i].Rooms[j].CheckoutTime = checkingouttime;
					Hotel_Floors[i].Rooms[j].AllCustomers[Hotel_Floors[i].Rooms[j].CustomerNo].Chkouttime = checkingouttime;
					cout << "Guests in Room " << Hotel_Floors[i].Rooms[j].Room_No << " have checked out" << endl << endl;
					Checkouts << "Guests in Room " << Hotel_Floors[i].Rooms[j].Room_No << " have checked out" << endl << endl;
					Hotel_Floors[i].Rooms[j].DisplayBookingInfo(Hotel_Floors[i].Rooms[j].Checkouton, checkingouttime);
					Hotel_Floors[i].Rooms[j].DisplayBookingInfo(Checkouts, Hotel_Floors[i].Rooms[j].Checkouton, checkingouttime);
					Checkouts << endl;
					Checkouts << endl;
					cout << endl;
					ChkoutRoom(Hotel_Floors[i].Rooms[j]);
					checkouts++;
					checkoutsofday++;
				}
			}
		}

		if (checkoutsofday == 0)
		{
			cout << "No Checkouts Today!" << endl << endl;
		}

		cout << string(30, '-') << endl;
		cout << "Simulation Day : " << day << endl;
		cout << "Number of Total Check-ins : " << checkins << endl;
		cout << "Number of Total Check-outs : " << checkouts << endl;
		cout << "Total Income : " << rent << endl;

		date.AddDays(1);
		system("PAUSE");
	}
	cout << endl << "Simulation Complete" << endl;
	system("PAUSE");
	ConsolidatedLog(daysToSimulate,Checkins, Checkouts,checkins,checkouts,rent);
	system("CLS");
	cout << "Log File has been Generated for this Simulation" << endl << endl;
	system("PAUSE");
	cout << "Taking you back to the Main Menu";
	TimeDelay(3);
}

void Report(int RoomNumber) //Generate a full report for the specified room
{
	system("CLS");
	for (int floor = 0; floor < 3; floor++)
	{
		for (int room = 0; room < 10; room++)
		{
			if (Hotel_Floors[floor].Rooms[room].Room_No == RoomNumber)
			{
				cout << "Room Number : " << Hotel_Floors[floor].Rooms[room].Room_No << endl;
				cout << "Phone Number : " << Hotel_Floors[floor].Rooms[room].Phone_No << endl;
				cout << "Occupancy : " << Hotel_Floors[floor].Rooms[room].Occupancy << endl;
				cout << endl;
				if (Hotel_Floors[floor].Rooms[room].CustomerNo > 0 || (Hotel_Floors[floor].Rooms[room].CustomerNo == 0 && Hotel_Floors[floor].Rooms[room].isBooked))
				{
					cout << "Booking History : " << endl;
					for (int i = 0; i < Hotel_Floors[floor].Rooms[room].CustomerNo; i++)
					{
						cout << endl << string(25, '~') << endl;
						cout << "Details for Customer " << i << " :" << endl;
						cout << "Booking Date : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].BookingDate.ShowDate() << endl;
						cout << "Booking Time : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].Booktime.ShowTime() << endl;
						cout << "Stayed for Days : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].DaysStayed << endl;
						cout << "Departure Date : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].CheckoutDate.ShowDate() << endl;
						cout << "Departure Time : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].Chkouttime.ShowTime() << endl;
						cout << "Total Drinks Consumed : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].Drinksdrunk << endl;
						cout << "Rent Paid : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].rentpaid << endl << endl;
						cout << "Guest Information :" << endl;
						for (int guests = 0; guests < Hotel_Floors[floor].Rooms[room].Occupancy; guests++)
						{
							cout << "Name : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].StayingGuests[guests].GetName() << endl;
							cout << "CNIC No : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].StayingGuests[guests].GetCNIC() << endl;
							cout << "Date Of Birth : " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].StayingGuests[guests].GetDOB() << endl << endl;
						}
						cout << "Drinks Consumed by these Guests :" << endl;
						for (int drinks = 0; drinks < Hotel_Floors[floor].Rooms[room].AllCustomers[i].Drinksdrunk; drinks++)
						{
							cout << Hotel_Floors[floor].Rooms[room].AllCustomers[i].ConsumedDrinks[drinks].GetBrand() << " " <<
								Hotel_Floors[floor].Rooms[room].AllCustomers[i].ConsumedDrinks[drinks].GetSize() << " mL" << endl;
						}

						cout << "Drinks Available in the Refrigerator after Customer Left:" << endl;
						for (int refr = 0; refr < 10; refr++)
						{
							cout << refr << ") " << Hotel_Floors[floor].Rooms[room].AllCustomers[i].Refrigerator[refr].GetBrand() << " " <<
								Hotel_Floors[floor].Rooms[room].AllCustomers[i].Refrigerator[refr].GetSize() << " mL : ";
							if (Hotel_Floors[floor].Rooms[room].AllCustomers[i].Refrigerator[refr].isempty)
							{
								cout << "Empty" << endl;
							}
							else
							{
								cout << "Full" << endl;
							}
						}
						
					}
				}
				else
				{
					cout << "Room has no Booking History" << endl;
				}
			}
			
		}
	}
	system("PAUSE");
	cout << "Going Back to Main Menu ";
	TimeDelay(3);
}

void RoomsinFloorsReport(int RequestedFloorNo) //Generate brief reports for all rooms in a specified floor
{
	system("CLS");
	Banner();
	for (int rooms = 0; rooms < 10; rooms++)
	{
		cout << string(40, '~') << endl;
		cout << "Information for Room No." << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Room_No << " :" << endl;
		cout << "Phone No. : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Phone_No << endl;
		cout << "Occupancy : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Occupancy << endl << endl;
		cout << "Refrigerator Status : " << endl;
		Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Display_Refrigerator();
		if (Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].isBooked)
		{
			cout << endl <<  "Room Is Currently Booked, Showing Booking Info . . . " << endl << endl;
			cout << "Room is Currently Booked to these Guests :" << endl;
			for (int i = 0; i < Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Occupancy; i++)
			{
				cout << "Name : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Guests[i].GetName() << endl;
				cout << "CNIC : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Guests[i].GetCNIC() << endl;
				cout << "Date of Birth : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Guests[i].GetDOB() << endl;
			}
			cout << endl << "Booking Details : " << endl << endl;
			cout << "Booking Date : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Bookedon.ShowDate() << endl;
			cout << "Booking Time : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].BookingTime.ShowTime() << endl;
			cout << "Staying for : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].StayDays << " Days" << endl;
			cout << "Charges : " << Hotel_Floors[RequestedFloorNo - 1].Rooms[rooms].Charges << endl;
			cout << endl;
		}
		else
		{
			cout << "Room is currently unbooked" << endl;
		}
	}
	system("PAUSE");
}


void Banner()
{
	cout << "---------------------------------------" << endl;
	cout << "   Pearl Continental Hotel Rawalpindi  " << endl;
	cout << "---------------------------------------" << endl << endl;
}

void menu() // The front end interface for the program.
{
	while (true)
	{
		int RequestedFloorNo;
		int command;
		int menucommand;
		int SimulationDays;
		int RoomNumber;
		system("CLS");
		Banner();
		cout << "Enter \'1\' to run a Simulation" << endl;
		cout << "Enter \'2\' to Enter Staff Management System" << endl;
		cout << "Enter \'3\' to Exit the Application" << endl << '>';
		cin >> menucommand;
		if (menucommand == 1)
		{
			system("CLS");
			Banner();
			cout << "Enter Number of Days to run the Simulation" << endl << '>';
			cin >> SimulationDays;
			simulation(SimulationDays);
		}
		if (menucommand == 2)
		{
			system("CLS");
			Banner();
			cout << "STAFF MANAGEMENT SYSTEM " << endl << endl;
			cout << "Enter \'1\' to get the Reports for all Rooms on all Floors" << endl;
			cout << "Enter \'2\' to get the Reports for all Rooms on a Particular Floor" << endl;
			cout << "Enter \'3\' to get Full Booking Details for a Particular Room" << endl;
			cout << "Enter \'4\' to go back to Main Menu" << endl << '>';
			cin >> command;
			if (command == 1)
			{
				system("CLS");
				cout << "Fetching Reports for all Rooms in All Floors" << endl;
				TimeDelay(3);
				for (int floors = 1; floors <= 3; floors++)
				{
					RoomsinFloorsReport(floors);
				}
			}
			if (command == 2)
			{
				cout << "Please Enter the Floor No. For Which You Want The Info of All Rooms (1-3) : " << endl;
				cin >> RequestedFloorNo;
				RoomsinFloorsReport(RequestedFloorNo);
			}
			if (command == 3)
			{
				cout << "Please Enter Room No. for which you want full booking details and history " << endl;
				cin >> RoomNumber;
				Report(RoomNumber);
			}
			if (command == 4)
			{
				menu();
			}
		}
		if (menucommand == 3)
		{
			return;
		}
	}	
}