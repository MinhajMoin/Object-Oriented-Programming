#include <iostream>
#include "include/list.h"

using namespace std;

//<< operator overload Function Definition is below the main function
ostream& operator<<(ostream&,mylist&);

int main()
{
    mylist l;


    return 0;
}

ostream& operator<<(ostream& os,mylist& List)
{
    return os << List.display();
}
