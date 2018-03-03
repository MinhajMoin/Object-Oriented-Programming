#pragma once
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Time // Time Struct. detailed comments in the respective cpp file
{
	Time();
	Time(string);
	string ShowTime();
	string TimePart;
	int seconds;
	int minutes;
	int hours;
	string am_pm;
};
