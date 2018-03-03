#pragma once
#include <string>
#include "Date.h"

using namespace std;

class Person //Person Class. detailed comments in the respective cpp file
{
public:
	Person(string , string , string );
	Person();
	string GetName();
	string GetCNIC();
	string GetDOB();
	bool inRoom;
private:
	string Name;
	string CNIC;
	Date DOB;
};