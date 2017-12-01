#ifndef RECT_H
#define RECT_H
#include "Point.h"
#include <SDL.h>
struct Rect
{
    Rect(SDL_Rect);
    Point topLeft;
    Point topRight;
    Point botLeft;
    Point botRight;
    int width;
    int height;
    bool isInside(Point&,bool code = true);
    int isColliding(Rect&,float,float,bool code= true);//code is basically a flag, default 1 is for ball, 0 for mobilebricks
    int isInside(Rect&);
    enum COLLISIONS {NONE,RIGHT,TOP,LEFT,DOWN};
    enum CODES {XBRICK,BALL,YBRICK};
};

#endif // RECT_H
