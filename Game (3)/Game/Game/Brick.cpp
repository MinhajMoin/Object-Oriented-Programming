#include "Brick.h"

Brick::Brick(LTexture* image, Board* gameBoard, Point pos):Entity(image,pos),gameBoard(gameBoard)
{
    int x=0;
    int y=0;
    brickHealth=0;
    brickDamage=0;
    width=48;
    height=18;
    for(int i=PURPLE; i<NUM_BRICK_COLORS; i++)
    {
        y=0;
        for(int j=FRAME0; j<NUM_BRICK_FRAMES; j++)
        {
            spriteClips[i][j].x=x;
            spriteClips[i][j].y=y;
            spriteClips[i][j].w=width;
            spriteClips[i][j].h=height;
            y+=height;
        }
        x+=width;
    }

    bounds.x=pos.x;
    bounds.y=pos.y;
    bounds.w=width;
    bounds.h=height;

    color=rand()%(NUM_BRICK_COLORS-1);// Subtracting 1 since last brick is steel one, its color will be set separately

}

Brick::~Brick()
{
    //dtor
}

void Brick::incrementDmg()
{
    //std::cout << brickDamage << " " << brickHealth << std::endl;
    //std::cout << alive << std::endl;
    if(brickHealth==10)
    {
        return;//condition for steel brick, should die only if hit by bullet or missile
    }
    if(brickDamage++>=brickHealth)
    {
        setAlive(0);
    }
}

