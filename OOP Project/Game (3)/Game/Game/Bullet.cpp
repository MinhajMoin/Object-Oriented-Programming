#include "Bullet.h"

Bullet::Bullet(LTexture* image, Board* gameBoard, Point pos):Smasher(image, gameBoard, pos)
{
    spriteClips[0].x = 258;
    spriteClips[0].y = 30;
    spriteClips[0].w = 6;
    spriteClips[0].h = 12;

    width = 6;
    height = 12;
    setBounds();
    speed = 5;
    fired = false;
    delay = 0;

    boardBounds = gameBoard->getBounds();
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::render(long int& frame, SDL_Renderer* gRenderer)
{
    if (!smashed)
    {
        spriteSheetTexture->render(pos.x, pos.y, &spriteClips[0], 0, NULL, SDL_FLIP_NONE, gRenderer);
    }

    else
    {
        delay++;
        if(delay%5==0)
        {
            expFrame++;
        }

        if (expFrame < NUM_EXPLODING_FRAMES)
        {
            spriteSheetTexture->render(pos.x-offsetX, pos.y-offsetY, &expSpriteClips[expFrame], 0, NULL, SDL_FLIP_NONE, gRenderer);
        }

        else
        {
            finished = true;
        }
    }
}

void Bullet::move()
{
    if (!smashed)
    {
        pos.y -= speed;
    }

    if (pos.y <= boardBounds.y)
    {
        smashed = true;
    }

    setBounds();
}

void Bullet::setPosition(Point position)
{
    pos = position;
}

bool Bullet::isFired()
{
    return fired;
}

void Bullet::fire()
{
    fired = true;
}
