#ifndef MOBILEBRICKY_H
#define MOBILEBRICKY_H
#include "MobileBrick.h"


class MobileBrickY : public MobileBrick
{
public:
    MobileBrickY(LTexture*,Board*,Point);
    void move(List*);

protected:

private:
};

#endif // MOBILEBRICKY_H
