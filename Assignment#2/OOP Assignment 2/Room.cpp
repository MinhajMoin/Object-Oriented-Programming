#include "stdafx.h"
#include "Room.h"

using namespace std;

Room::Room(int RoomNo, int FloorNo) //Ctor taking Floor no and room no (2 digits only) to create room
{
	Room_No = (FloorNo * 100) + (RoomNo);
	Phone_No = "0" + to_string(Room_No);
	BookedTo = new string[Occupancy];
	Guests = new Person[Occupancy];
	Floor_No = FloorNo;
	CustomerNo = 0;
	Consumed_Drinks = 0;
}

Room::Room() //default ctor
{

}

void Room::DisplayBookingInfo() //Display Details when person hasn't checkout yet
{
	cout << endl;
	cout << "ROOM INFORMATION :" << endl;
	cout << "Room No : " << Room_No << endl;
	cout << "Phone No : " << Phone_No << endl;
	cout << "Occupancy : " << AllCustomers[CustomerNo].RoomOccupancy << endl << endl;
	cout << "BOOKING INFORMATION : " << endl;
	cout << "Booking Date : " << AllCustomers[CustomerNo].BookingDate.ShowDate() << endl;
	cout << "Booking Time : " << AllCustomers[CustomerNo].Booktime.ShowTime() << endl;
	cout << "Booked for Duration : " << StayDays << " Days" << endl;
	cout << "Rent : " << Charges << endl << endl;
	cout << "GUEST INFORMATION :" << endl;
	for (int i = 0; i < Occupancy; i++)
	{
		cout << "Name : " << Guests[i].GetName() << endl;
		cout << "CNIC : "<< Guests[i].GetCNIC() << endl;
		cout << "Birthday : "<< Guests[i].GetDOB() << endl << endl;
	}
	cout << "Refrigerator Status : " << endl;
	Display_Refrigerator();
	cout << endl;
}

void Room::DisplayBookingInfo(Date& outdate,Time& outtime)//Display details of person's stay when they have checked out
{
	cout << endl;
	cout << "ROOM INFORMATION :" << endl;
	cout << "Room No : " << Room_No << endl;
	cout << "Floor No : " << Floor_No << endl;
	cout << "Phone No : " << Phone_No << endl;
	cout << "Occupancy : " << AllCustomers[CustomerNo].RoomOccupancy << endl << endl;
	cout << "BOOKING INFORMATION : " << endl;
	cout << "Booking Date : " << AllCustomers[CustomerNo].BookingDate.ShowDate() << endl;
	cout << "Booking Time : " << AllCustomers[CustomerNo].Booktime.ShowTime() << endl;
	cout << "Booked for Duration : " << StayDays << " Days" << endl;
	cout << "Rent : " << Charges << endl << endl;

	cout << "DEPARTURE INFORMATION : " << endl;
	cout << "Checkout Date : " << outdate.ShowDate() << endl;
	cout << "Checkout Time : " << outtime.ShowTime() << endl;
	cout << "Stayed for Days : " << StayDays << endl;
	cout << "ColdDrinks Consumed : " << Consumed_Drinks << endl << endl;

	cout << "GUEST INFORMATION :" << endl;
	for (int i = 0; i < Occupancy; i++)
	{
		cout << "Name : " << Guests[i].GetName() << endl;
		cout << "CNIC : " << Guests[i].GetCNIC() << endl;
		cout << "Birthday : " << Guests[i].GetDOB() << endl << endl;
	}
	cout << "Refrigerator Status : " << endl;
	Display_Refrigerator();
	cout << endl;
}


void Room::DisplayBookingInfo(stringstream& ss,Date& outdate,Time& outtime) //same as the above one, just puts everything into a stream rather than console output
{
	ss << endl;
	ss << "ROOM INFORMATION :" << endl;
	ss << "Room No : " << Room_No << endl;
	ss << "Floor No : " << Floor_No << endl;
	ss << "Phone No : " << Phone_No << endl;
	ss << "Occupancy : " << AllCustomers[CustomerNo].RoomOccupancy << endl << endl;
	ss << "BOOKING INFORMATION : " << endl;
	ss << "Booking Date : " << AllCustomers[CustomerNo].BookingDate.ShowDate() << endl;
	ss << "Booking Time : " << AllCustomers[CustomerNo].Booktime.ShowTime() << endl;
	ss << "Booked for Duration : " << StayDays << " Days" << endl;
	ss << "Rent : " << Charges << endl << endl;

	ss << "DEPARTURE INFORMATION : " << endl;
	ss << "Checkout Date : " << outdate.ShowDate() << endl;
	ss << "Checkout Time : " << outtime.ShowTime() << endl;
	ss << "Stayed for Days : " << StayDays << endl;
	ss << "ColdDrinks Consumed : " << Consumed_Drinks << endl << endl;

	ss << "GUEST INFORMATION :" << endl;
	for (int i = 0; i < Occupancy; i++)
	{
		ss << "Name : " << Guests[i].GetName() << endl;
		ss << "CNIC : " << Guests[i].GetCNIC() << endl;
		ss << "Birthday : " << Guests[i].GetDOB() << endl << endl;
	}
	ss << "Refrigerator Status : " << endl;
	Display_Refrigerator(ss);
	ss << endl;
}

void Room::DisplayBookingInfo(stringstream& ss) //put details of a person's stay to a stream when they haven't checked out yet
{
	ss << endl;
	ss << "ROOM INFORMATION :" << endl;
	ss << "Room No : " << Room_No << endl;
	ss << "Floor No : " << Floor_No << endl;
	ss << "Phone No : " << Phone_No << endl;
	ss << "Occupancy : " << AllCustomers[CustomerNo].RoomOccupancy << endl << endl;
	ss << "BOOKING INFORMATION : " << endl;
	ss << "Booking Date : " << AllCustomers[CustomerNo].BookingDate.ShowDate() << endl;
	ss << "Booking Time : " << AllCustomers[CustomerNo].Booktime.ShowTime() << endl;
	ss << "Booked for Duration : " << StayDays << " Days" << endl;
	ss << "Rent : " << Charges << endl << endl;

	ss << "GUEST INFORMATION :" << endl;
	for (int i = 0; i < Occupancy; i++)
	{
		ss << "Name : " << Guests[i].GetName() << endl;
		ss << "CNIC : " << Guests[i].GetCNIC() << endl;
		ss << "Birthday : " << Guests[i].GetDOB() << endl << endl;
	}
	ss << "Refrigerator Status : " << endl;
	Display_Refrigerator(ss);
	ss << endl;
}

void Room::Refrigerator_Fill() // Fill the Refrigerator
{
	for (int i = 0; i < 10; i++)
	{
		Refrigerator[i] = ColdDrink();
	}
}

void Room::Display_Refrigerator() // Show the Drinks remaining in the Refrigerator
{
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << ") " << Refrigerator[i].GetBrand() << " " << Refrigerator[i].GetSize() << " ml" << " :";
		if (Refrigerator[i].isempty)
		{
			cout << "Empty" << endl;
		}
		else
		{
			cout << "Full" << endl;
		}
	}
}

void Room::Display_Refrigerator(stringstream& ss) //Write the Refrigerator Drinks status into a stream
{
	for (int i = 0; i < 10; i++)
	{
		ss << i + 1 << ") " << Refrigerator[i].GetBrand() << " " << Refrigerator[i].GetSize() << " ml" << " :";
		if (Refrigerator[i].isempty)
		{
			ss << "Empty" << endl;
		}
		else
		{
			ss << "Full" << endl;
		}
	}
}

void Room::Checkout() //Checkout the current customer living in the room
{
	for (int i = 0; i < Occupancy; i++)
	{
		Guests[i] = Person();
	}
	isBooked = false;
	Bookedon = Date();
	AllCustomers[CustomerNo].CheckoutDate = Checkouton;
	for (int i = 0; i < 10; i++)
	{
		AllCustomers[CustomerNo].Refrigerator[i] = Refrigerator[i];
	}
}