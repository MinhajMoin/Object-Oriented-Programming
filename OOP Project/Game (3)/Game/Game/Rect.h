#ifndef RECT_H
#define RECT_H
#include "Point.h"

struct Rect
{
    Rect(Point,Point,Point,Point);
    Point topLeft;
    Point topRight;
    Point botLeft;
    Point botRight;
    int width;
    int height;
    bool isInside(Point&);
    bool isIntersecting(Rect&);
};

#endif // RECT_H
