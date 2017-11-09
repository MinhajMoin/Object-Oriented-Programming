#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;

struct Point
{
    Point():x(0),y(0) {}
    Point(float x,float y):x(x),y(y) {}
    Point(const Point& toCopy):x(toCopy.x),y(toCopy.y) {}
    void operator=(const Point& toAssign)
    {
        x=(toAssign.x);
        y=(toAssign.y);
    }
    float x;
    float y;
    void operator++(int)//post increment operator, shifts current point to the left by one brick unit
    {
        x+=48;
    }
    void operator++()//pre increment operator, shifts current point down by one brick unit
    {
        y+=18;
    }

    //EXTRA OPERATORS, REMOVE?!
    void operator--(int)//post increment operator, shifts current point to the left by one brick unit
    {
        x-=48;
    }
    void operator--()//pre increment operator, shifts current point down by one brick unit
    {
        y-=18;
    }

};
ostream& operator <<(ostream& a,const Point& toPrint);


#endif // POINT_H
