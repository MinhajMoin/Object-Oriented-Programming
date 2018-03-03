#pragma once
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
#include <Windows.h>


// File containing custom functions used. detailed comments in the respective cpp file
void TimeDelay(int);
void BookRoom(Room&, Person[], Date&, Time&);
void ChkoutRoom(Room&, Date);
bool GetGuestNames();
Date DateToday();
Time TimeNow();
void simulation(int);
void Report(int);
void menu();
void Banner();