#ifndef RECT_H
#define RECT_H
#include "Point.h"
#include <SDL.h>
struct Rect
{
    Rect(SDL_Rect&);
    Point topLeft;
    Point topRight;
    Point botLeft;
    Point botRight;
    int width;
    int height;
    bool isInside(Point&);
    int isColliding(Rect&,float,float);
    int isInside(Rect&);
    enum COLLISIONS{NONE,RIGHT,TOP,LEFT,DOWN};
};

#endif // RECT_H
