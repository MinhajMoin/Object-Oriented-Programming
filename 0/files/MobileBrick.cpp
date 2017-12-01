#include "MobileBrick.h"

MobileBrick::MobileBrick(LTexture* image,Board* gameBoard, Point pos):OneHitBrick(image,gameBoard,pos)
{
    speed=this->width/25.0f;
}

void MobileBrick::reverseDir()
{
    if (dx==LEFT)
    {
        dx=RIGHT;
    }
    else if (dx==RIGHT)
    {
        dx=LEFT;
    }
    if (dy==UP)
    {
        dy=DOWN;
    }
    else if (dy==DOWN)
    {
        dy = UP;
    }
}
int MobileBrick::checkCollisions(List* worldEnt)
{
    int ind = worldEnt->getEntInd(this);// ind has address of the current mobile brick in the list
    Node* tmp = worldEnt->getNodeAtInd(0);
    if (ind == -1) return -1;
    while(tmp)
    {
        if(tmp->ent != this)//To skip checking for collision with itself
        {
            SDL_Rect prevBrick=tmp->ent->getBounds();
            if(this->type==MOBILEBRICKX)
            {
                if(dx==LEFT)
                {
                    prevBrick.x += 2;//for correcting offset for better surrounded collisions
                    if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                    {
                        return RIGHT;
                    }
                }
                else
                {
                    prevBrick.x -=2;//for correcting offset for better surrounded collisions
                    if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                    {
                        return LEFT;
                    }

                }
            }
            else if(this->type==MOBILEBRICKY)
            {
                if(dy==UP)
                {
                    prevBrick.y+=2;//for correcting offset for better surrounded collisions
                    if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                    {
                        return DOWN;
                    }
                }
                else
                {
                    prevBrick.y-=2;//for correcting offset for better surrounded collisions
                    if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                    {
                        return UP;
                    }
                }
            }
        }
        tmp=tmp->next;
    }
    return NONE;
}
