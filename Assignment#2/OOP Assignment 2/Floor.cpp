#include "stdafx.h"
#include "Floor.h"

Floor::Floor() //Default Ctor
{
}

Floor::Floor(int Floor_No) //OverLoad Ctor which initializes the declared array of rooms and fills all refrigerators
{
	for (int i = 0; i < 10; i++)
	{
		Rooms[i] = Room(i + 1, Floor_No);
		Rooms[i].Refrigerator_Fill();
	}
}
