#pragma once
#include <iostream>
#include <string>

using namespace std;

class ColdDrink //Create colddrink class. detailed comments in the respective cpp file
{
public:
	ColdDrink();
	string GetBrand();
	int GetSize();
	bool isempty;
private:
	string brands[3] = {"Pepsi","Fanta","Sprite"};
	int sizes[3] = { 200,250,300 };
	string brand;
	int size;
};

