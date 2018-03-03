#include "stdafx.h"
#include "Person.h"

Person::Person() //Default Ctor
{
}

string Person::GetName() //get the name. nuff said.
{
	return Name;
}

string Person::GetCNIC() //get the CNIC of the Person
{
	return CNIC;
}

string Person::GetDOB() //get the Birthday of the Person
{
	return DOB.ShowDate();
}

Person::Person(string _Name, string _DOB, string _CNIC) //Overload Ctor taking name cnic and dob.
{
	Name = _Name;
	DOB = Date(_DOB);
	CNIC = _CNIC;
}