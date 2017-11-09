#ifndef MOBILEBRICK_H
#define MOBILEBRICK_H
#include "OneHitBrick.h"
#include "List.h"
class MobileBrick: public OneHitBrick
{
public:
    MobileBrick(LTexture*,Board*,Point);
    void move(List*);
    enum DIRECTIONS {LEFT,RIGHT};
protected:

private:
};

#endif // MOBILEBRICK_H
