// OOPAssignment2.cpp : Defines the entry point for the console application.
// This is the main file which calls all other Files.

#include "stdafx.h"

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Person.h"
#include "Room.h"
#include "Floor.h"
#include "Date.h"
#include <chrono>
#include <iomanip>
#include "Time.h"
#include "Functions.h"


using namespace std;

int main()
{
	srand(time(NULL)); //take the local time as seed of the rand() function
	if (GetGuestNames()) 
	{ //parse the names.txt file and put the names into object array
		menu();
	}
	cout << endl <<"Closing Application" << endl;
	TimeDelay(3);
	return 1;
}