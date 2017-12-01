#ifndef STEELBRICK_H
#define STEELBRICK_H
#include "Brick.h"
class SteelBrick:public Brick
{
public:
    SteelBrick(LTexture*,Board*,Point);
    void render(long int&, SDL_Renderer*);
};

#endif // STEELBRICK_H
