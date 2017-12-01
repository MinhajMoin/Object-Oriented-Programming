#ifndef INVISIBLEBRICK_H
#define INVISIBLEBRICK_H
#include "TwoHitBrick.h"


class InvisibleBrick: public TwoHitBrick
{
public:
    InvisibleBrick(LTexture*,Board*,Point);
    void render(long int&, SDL_Renderer*);
protected:

private:
};

#endif // INVISIBLEBRICK_H
