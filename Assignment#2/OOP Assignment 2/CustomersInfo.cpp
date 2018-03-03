#include "stdafx.h"
#include "CustomersInfo.h"


CustomersInfo::CustomersInfo() // Default Constructor for Declaring array in Room
{

}

CustomersInfo::CustomersInfo(int Occupancy,Date Book,Time Bktime,Person Guests[]) // Overload Ctor taking info for the Guest
{
	RoomOccupancy = Occupancy;
	StayingGuests = new Person[Occupancy];
	BookingDate = Book;
	Booktime = Bktime;
	for (int i = 0; i < Occupancy; i++)
	{
		StayingGuests[i] = Guests[i];
	}
}
