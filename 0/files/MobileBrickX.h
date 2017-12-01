#ifndef MOBILEBRICKX_H
#define MOBILEBRICKX_H
#include "MobileBrick.h"

class MobileBrickX: public MobileBrick
{
public:
    MobileBrickX(LTexture*,Board*,Point);
    void move(List*);
};

#endif // MOBILEBRICKX_H
