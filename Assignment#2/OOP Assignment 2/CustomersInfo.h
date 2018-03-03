#pragma once
#include "ColdDrink.h"
#include "Person.h"
#include "Time.h"

struct CustomersInfo// Customer Info Class. upto 8 customer records can be made in a room. detailed comments in the respective cpp file
{
	CustomersInfo();
	CustomersInfo(int,Date,Time,Person []);
	int RoomOccupancy;
	ColdDrink Refrigerator[10];
	Date BookingDate;
	Date CheckoutDate;
	Time Booktime;
	Time Chkouttime;
	int DaysStayed;
	int rentpaid;
	int Drinksdrunk = 0;
	ColdDrink ConsumedDrinks[70];
	Person* StayingGuests;
};

