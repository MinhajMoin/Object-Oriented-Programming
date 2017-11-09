#ifndef ONEHITBRICK_H
#define ONEHITBRICK_H
#include "Brick.h"

class OneHitBrick:public Brick
{
public:
    OneHitBrick(LTexture*,Point);
    void render(long int&, SDL_Renderer*);
};

#endif // ONEHITBRICK_H
