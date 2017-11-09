#include "Rect.h"


Rect::Rect(Point a,Point b,Point c,Point d):topLeft(a),topRight(b),botLeft(c),botRight(d)
{
    width=b.x - a.x;
    height=c.y-a.y;
}

bool Rect::isInside(Point& p)
{
    return (p.x >= topLeft.x && p.x <= topRight.x && p.y >= topLeft.y && p.y <=botLeft.y);
}
bool Rect::isIntersecting(Rect& B)
{
    return (isInside(B.topLeft) || isInside(B.topRight) || isInside(B.botLeft) || isInside(B.botRight));
}
