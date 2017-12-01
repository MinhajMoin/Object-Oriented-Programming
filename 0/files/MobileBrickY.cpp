#include "MobileBrickY.h"

MobileBrickY::MobileBrickY(LTexture* image,Board* gameBoard,Point pos):MobileBrick(image,gameBoard,pos)
{
    dy=UP;
    type=MOBILEBRICKY;
}

void MobileBrickY::move(List* worldEnt)//instead of passing the entire list, pass two entities, prev and for bricks
{
    if(!alive)
        return;
    SDL_Rect boardBounds=gameBoard->getBounds();
    if (dy==UP)
    {
        if (boardBounds.y + 2 < this->pos.y )//moves the brick inside the bounds of the board//moves the brick inside the bounds of the board
        {
            int collisionType=checkCollisions(worldEnt);

            if (collisionType==DOWN)
            {
                reverseDir();
            }
            else
            {
                pos.y -= speed;
            }
            setBounds();
        }
        else
        {
            reverseDir();
        }
    }
    else //if (dy==DOWN)
    {
        if (boardBounds.y + boardBounds.h/2 > pos.y)//keeps the brick inside the bounds of the board
        {
            int collisionType=checkCollisions(worldEnt);
            if(collisionType==UP)//board.COLLISIONS::TOP && checkCollisions(worldEnt)!=0)//==board.COLLISIONS::RIGHT)
            {
                reverseDir();
            }
            else
            {
                pos.y += speed;
            }
            setBounds();
        }
        else
        {
            reverseDir();
        }
    }
}


