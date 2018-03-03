#include "stdafx.h"
#include "Time.h"
#include <iostream>
#include <cstring>
#include <stdlib.h> 

using namespace std;

Time::Time() //Default Constructor
{
}


Time::Time(string InputTime) //Overload Ctor. when time is given as HH/mm/ss as a string, it creates a time object
{
	string TimeComponents[3];
	int i = 0;
	istringstream TimeBuild = istringstream(InputTime);
	while (getline(TimeBuild, TimePart, '/'))
	{
		TimeComponents[i] = TimePart;
		i++;
	}
	hours = atoi(TimeComponents[0].c_str());
	minutes = atoi(TimeComponents[1].c_str());
	seconds = atoi(TimeComponents[2].c_str());
}



string Time::ShowTime() //return the time object as a string
{
	string FormattedSeconds = to_string(seconds);
	string FormattedMinutes = to_string(minutes);
	string FormattedHours = to_string(hours);
	if (seconds<10)
	{
		FormattedSeconds = "0" + FormattedSeconds;
	}
	if (minutes<10)
	{
		FormattedMinutes = "0" + FormattedMinutes;
	}
	if (hours < 10)
	{
		FormattedHours = "0" + FormattedHours;
	}
	return (FormattedHours + ":" + FormattedMinutes + ":" + FormattedSeconds);
}