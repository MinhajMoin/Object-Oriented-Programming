#include "stdafx.h"
#include "ColdDrink.h"
#include <string>

using namespace std;

ColdDrink::ColdDrink() //Ctor for the class
{
	brand = brands[rand() % 3]; //set a random brand from the array made in the header file.
	size = sizes[rand() % 3];//set a random size from the array made in the header file.
	isempty = false; // Set the Drink Flag as false
}

string ColdDrink::GetBrand() //fetch the private attribute brand of the drink
{
	return brand;
}

int ColdDrink::GetSize() //fetch the private attribute size of the drink
{
	return size;
}