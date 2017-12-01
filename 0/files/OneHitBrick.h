#ifndef ONEHITBRICK_H
#define ONEHITBRICK_H
#include "Brick.h"

class OneHitBrick:public Brick
{
public:
    OneHitBrick(LTexture*,Board*,Point);
    void render(long int&, SDL_Renderer*);
};

#endif // ONEHITBRICK_H
