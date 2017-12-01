#ifndef MOBILEBRICK_H
#define MOBILEBRICK_H
#include "Rect.h"
#include "OneHitBrick.h"
#include "List.h"
class MobileBrick: public OneHitBrick
{
public:
    MobileBrick(LTexture*,Board*,Point);
    virtual void move(List*)=0;
    enum DIRECTIONS {NONE,LEFT,RIGHT,UP,DOWN};
    void reverseDir();
    int checkCollisions(List*);//Used for checking brick-brick collisions

protected:

private:
};

#endif // MOBILEBRICK_H
