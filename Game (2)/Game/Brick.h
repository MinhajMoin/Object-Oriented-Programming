#ifndef BRICK_H
#define BRICK_H
#include "Entity.h"


class Brick : public Entity //ABSTRACT CLASS, ADD MOVING AND STEEL BRICKS
{
public:
    Brick(LTexture*,Point);
    virtual ~Brick();
    enum BRICK_FRAMES {FRAME0,FRAME1,FRAME2,FRAME3,FRAME4,NUM_BRICK_FRAMES};
    enum COLORS {PURPLE,RED,YELLOW,TURQ,GRAY,NUM_BRICK_COLORS};

protected:
    SDL_Rect spriteClips[NUM_BRICK_COLORS][NUM_BRICK_FRAMES];
    int brickHealth;
    int brickDamage;
    int color;

    void setDimensions(int,int);
    void incrementDmg();
};

#endif // BRICK_H
