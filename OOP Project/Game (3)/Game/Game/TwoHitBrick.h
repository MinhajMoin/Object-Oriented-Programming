#ifndef TWOHITBRICK_H
#define TWOHITBRICK_H
#include "Brick.h"
class TwoHitBrick:public Brick
{
public:
    TwoHitBrick(LTexture*,Board*,Point);
    void render(long int&, SDL_Renderer*);
};
#endif // TWOHITBRICK_H
