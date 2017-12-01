#include "Bullet.h"

Bullet::Bullet(LTexture* texture, Board* gameBoard, Paddle* paddle, int bulletPosition):Smasher(texture, gameBoard, paddle), bulletPosition(bulletPosition)
{
    spriteClips[0].x = 258;
    spriteClips[0].y = 27;
    spriteClips[0].w = 9;
    spriteClips[0].h = 20;

    width = 6;
    height = 12;
    speed = 5;
    fired = false;
    delay = 0;
    type = BULLET;
    bulletPositionOffset = 2;

    boardBounds = gameBoard->getBounds();
    initializePosition();
    setBounds();
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::render(long int& frame, SDL_Renderer* gRenderer)
{
    //SDL_RenderDrawRect(gRenderer,&bounds);
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

void Bullet::move(List*)
{
    if (!smashed)
    {
        pos.y -= speed;
    }

    if (pos.y <= boardBounds.y)
    {
        smashed = true;
        setAlive(0);
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

void Bullet::initializePosition()
{
    if (bulletPosition == LEFT)
    {
        pos.x = paddle->getPos().x + bulletPositionOffset;
        pos.y = paddle->getPos().y - height - 10;
    }

    else if (bulletPosition == RIGHT)
    {
        pos.x = paddle->getPos().x + paddle->getWidth() - width - bulletPositionOffset;
        pos.y = paddle->getPos().y - height - 10;
    }
}

void Bullet::setAlive(bool alive)
{
    this->alive=alive;
    if(!alive)
    {
        smashed=true;
    }
}
