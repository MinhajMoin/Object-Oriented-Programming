#include "stdafx.h"
#include "Date.h"
#include <iostream>
#include <cstring>
#include <stdlib.h> 

using namespace std;

Date::Date() //Default Ctor
{
	day = 0;
	month = 0;
	year = 0;
}


Date::Date(string InputDate) // When a date is input in the format DD/MM/YYYY as a string it converts it into a Date Object
{
	string DateComponents[3];
	int i = 0;
	istringstream DateBuild = istringstream(InputDate);
	while (getline(DateBuild, DatePart,'/'))
	{
		DateComponents[i] = DatePart;
		i++;
	}
	day = atoi(DateComponents[0].c_str());
	month = atoi(DateComponents[1].c_str());
	year = atoi(DateComponents[2].c_str());
}



string Date::ShowDate() // Return the Date Object as a String
{
	string FormattedDay = to_string(day);
	string FormattedMonth = to_string(month);
	if (day<10)
	{
		FormattedDay = "0" + FormattedDay;
	}
	if (month<10)
	{
		FormattedMonth = "0" + FormattedMonth;
	}
	return (FormattedDay + "/" + FormattedMonth + "/" + to_string(year));
}

void Date::AddDays(int addDays) //Add Days to the Date. Modifies the original Date Object to the one coming after the given days
{
	int MonthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (addDays + day > MonthDays[month])
	{
		day = (day + addDays) - MonthDays[month];
		if (month == 12)
		{
			month = 1;
			year++;
		}
		else
			month++;
	}
	else
		day += addDays;
}

Date Date::DateAfterDays(int days) // Add Days to the Date but instead of modifiying the original
{								  //Date object it returns a modified copy of the object after the given days
	int _day, _month, _year;
	_day = day;
	_month = month;
	_year = year;
	int MonthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (days + _day > MonthDays[_month])
	{
		_day = (_day + days) - MonthDays[_month];
		if (_month == 12)
		{
			_month = 1;
			_year++;
		}
		else
			_month++;
	}
	else
		_day += days;
	return Date(to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year));
}