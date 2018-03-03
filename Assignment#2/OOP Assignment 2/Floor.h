#pragma once
#include "Room.h"

using namespace std;

// Floor Struct .detailed comments in the respective cpp file

struct Floor
{
	Room Rooms[10];
	Floor();
	Floor(int);
};
