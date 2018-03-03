#pragma once
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Date // Date Struct. detailed comments in the respective cpp file
{
	Date();
	Date(string);
	Date DateAfterDays(int);
	string ShowDate();
	void AddDays(int);
	string DatePart;
	int day;
	int month;
	int year;
};

