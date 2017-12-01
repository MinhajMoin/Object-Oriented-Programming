#include "Smasher.h"

Smasher::Smasher(LTexture* image, Board* gameBoard, Paddle* paddle):Entity(image),gameBoard(gameBoard),paddle(paddle)
{
    int xList[] = {25, 61, 97, 137, 179, 219, 258};
    int y = 206;
    int w = 38;
    int h = 38;
    int yList[] = {214, 209, 206, 206, 206, 206, 206};
    int widthList[] = {21, 31, 38, 38, 36, 36, 37};
    int heightList[] = {20, 31, 38, 37, 37, 37, 37};
    for (int i=START; i<=NUM_EXPLODING_FRAMES; i++)
    {
        // (25,214), (21,20)
        // (61,209), (31,31)
        // (97,206), (38,38)
        // (137,206), (38,37)
        // (179,206), (36,37)
        // (219,206), (36,37)
        // (258,206), (37,37)
        expSpriteClips[i].x = xList[i];
        expSpriteClips[i].y = yList[i];
        expSpriteClips[i].w = widthList[i];
        expSpriteClips[i].h = heightList[i];
    }

    smashed = false;
    finished = false;
    expFrame = 0;
    offsetX = 13;
    offsetY = 13;
    paddle=paddle;
}

Smasher::~Smasher()
{
    //dtor
}

bool Smasher::isSmashed()
{
    return smashed;
}

bool Smasher::isFinished()
{
    return finished;
}
