#include "Rect.h"


Rect::Rect(SDL_Rect& a)
{
    topLeft=Point(a.x,a.y);
    topRight=Point(a.x+a.w,a.y);
    botLeft=Point(a.x,a.y+a.h);
    botRight=Point(a.x+a.w,a.y+a.h);
    width=a.w;
    height=a.h;
}

bool Rect::isInside(Point& p)
{
    return (p.x >= topLeft.x && p.x <= topRight.x && p.y >= topLeft.y && p.y <=botLeft.y);
}
int Rect::isColliding(Rect& B,float dx,float dy)//B is BALL
{
    float midB_Y=B.topLeft.y + B.height/2.0f;
    float midB_X=B.topLeft.x + B.width/2.0f;
    //INDIRECT COLLISIONS, ONE VERTEX OF BALL INTERSECTS
    if( (isInside(B.topLeft) || isInside(B.topRight)) &&  this->botLeft.y < midB_Y && this->botLeft.x < midB_X  && !isInside(B.botLeft) && !isInside(B.botRight) && dy <0)//if any two top vertices of rect B (ball) are inside the brick bounds and y midpoint of ball has higher value, Down collision
    {
        cout << "DOWN COLLISION" << endl;
        return DOWN;
    }
    else if (  (isInside(B.botLeft) || isInside(B.botRight)) && this->topLeft.y> midB_Y && this->topLeft.x < midB_X && !isInside(B.topLeft) && !isInside(B.topRight) && dy > 0)//if any two bottom vertices of rect B (ball) are inside the brick bounds, Up collision
    {
        cout << "TOP COLLISION" << endl;
        return TOP;
    }
    else if (  (isInside(B.topLeft) || isInside(B.botLeft)) && this->topRight.x < midB_X && this->topRight.y < midB_Y && !isInside(B.topRight) && !isInside(B.botRight) && dx < 0)//if any of the two left vertices of the ball are inside the brick bounds, Right collision
    {
        cout << "RIGHT COLLISION" << endl;
        return RIGHT;
    }
    else if ( (isInside(B.topRight) || isInside(B.botRight)) && this->topLeft.x > midB_X && this->topLeft.y < midB_Y  && !isInside(B.botLeft) && !isInside(B.topLeft) && dx > 0)//if any of the two right vertices of the ball are inside the brick bounds, Left collision
    {
        cout << "LEFT COLLISION" << endl;
        return LEFT;
    }
    else
        return NONE;//NO COLLISIONS
}
int Rect::isInside(Rect& B)//B IS Ball
{
    if (B.topLeft.y <= this->topLeft.y)//TOP COLLISION
    {
        return TOP;
    }
    else if (B.botLeft.y >= this-> botLeft.y)//DOWN COLLISION
    {
        return DOWN;
    }
    else if (B.topLeft.x <= this->topLeft.x)//LEFT COLLISION
    {
        return LEFT;
    }
    else if(B.topRight.x >= this->topRight.x)//RIGHT COLLISION
    {
        return RIGHT;
    }
    else//NO COLLISIONS, rect B is inside rect A
    {
        return NONE;
    }

}
