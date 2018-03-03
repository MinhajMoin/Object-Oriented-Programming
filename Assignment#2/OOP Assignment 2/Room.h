#pragma once
#include <string>
#include <iostream>
#include "Person.h"
#include "ColdDrink.h"
#include "Date.h"
#include "Time.h"
#include "CustomersInfo.h"

using namespace std;

struct Room // Room Struct. detailed comments for the methods in the respective cpp file
{
	Room();
	Room(int, int);
	void Refrigerator_Fill();
	void Display_Refrigerator();
	void DisplayBookingInfo();
	void DisplayBookingInfo(Date&,Time&);
	void Display_Refrigerator(stringstream&);
	void DisplayBookingInfo(stringstream&,Date&,Time&);
	void DisplayBookingInfo(stringstream&);
	void Checkout();
	int Room_No;
	int Floor_No;
	int Occupancy = 2 + rand() % 4;
	Person* Guests;
	string Phone_No;
	ColdDrink Refrigerator[10];
	string* BookedTo;
	bool isBooked = false;
	Date Bookedon;
	Date Checkouton;
	Time BookingTime;
	Time CheckoutTime;
	int StayDays;
	int Charges;
	int CustomerNo;
	int Consumed_Drinks;
	CustomersInfo AllCustomers[8]; // Each Room will hold info about 8 different guests checking in and out in the same room
};