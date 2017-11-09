#include "MobileBrick.h"

MobileBrick::MobileBrick(LTexture* image,Board* gameBoard, Point pos):OneHitBrick(image,gameBoard,pos)
{
    dx=LEFT;
    type=MOBILEBRICK;
    speedX=this->width/20.0f;
}

void MobileBrick::move(List* worldEnt)//instead of passing the entire list, pass two entities, prev and for bricks
{
    int ind=worldEnt->getEntInd(this);
    if (ind==-1) return; //movable brick not found in the list, has been deallocated, no need to move
    Entity* nextBrick = worldEnt->getEntAtInd(ind+1);
    Entity* prevBrick = worldEnt->getEntAtInd(ind-1);
    if (dx==RIGHT)
    {
        if (gameBoard->bounds.x + gameBoard->bounds.w >= this->pos.x + this->width + 2 )//moves the brick inside the bounds of the board
        {
            if (nextBrick == NULL || nextBrick->getPos().x >= this->pos.x + this->width || nextBrick->getPos().y > this->pos.y) //allowing brick movement only if the next brick doesn't collide, change direction otherwise
                pos.x += speedX;
            else
                dx=LEFT;
        }
        else
        {
            dx=LEFT;
        }
    }
    else
    {
        if (gameBoard->bounds.x + 2 <= pos.x)//keeps the brick inside the bounds of the board
        {
            if (prevBrick == NULL || prevBrick->getPos().x + prevBrick->getWidth() < this->pos.x || prevBrick->getPos().y < this->pos.y) //allowing brick movement only if the next brick doesn't collide, change direction otherwise
                pos.x -= speedX;
            else
                dx=RIGHT;
        }
        else
        {
            dx=RIGHT;
        }
    }
    setBounds();
}

