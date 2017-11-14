#include "Ball.h"

Ball::Ball(LTexture* texture, Board* gameBoard,Paddle* paddle):Entity(texture),gameBoard(gameBoard),paddle(paddle)
{
    float x=245.0f;
    int y=2;
    this->width=14;
    this->height=13;

    for (int i=NORMAL; i<NUM_BALL_MODES; i++)
    {
        spriteClips[i]= {(int)x,y,width,height};
        x+=17.5;
    }

    setBounds();

    sparkleSpriteClips[0]= {96,272,16,16};

    sparkleSpriteClips[1]= {114,272,16,16};

    sparkleSpriteClips[2]= {130,272,16,16};

    sparkleSpriteClips[3]= {148,272,16,16};

    sparkleSpriteClips[4]= {165,272,16,16};

    sparkleSpriteClips[5]= {182,272,16,16};

    sparkleSpriteClips[6]= {199,272,16,16};

    sparkleSpriteClips[7]= {216,272,16,16};

    type=BALL;
    setBallType(NORMAL);
    stickToPaddle();
}

Ball::~Ball() {}

void Ball::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect(gRenderer,&bounds);
    spriteSheetTexture->render(pos.x,pos.y,&spriteClips[BallType],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void Ball::setBallType(int BallType)
{
    this->BallType=BallType;
    if(BallType==FIRE)
    {
        speed=3;
    }
    else if (BallType==STICK)
    {
        stickToPaddle();
        setDir(0,-1);
        speed=3;
    }
    else if(BallType==SPEED)
    {
        speed=6;
    }
    else if (BallType==NORMAL)
    {
        speed=5.5f;
    }
}

int Ball::getBallType()
{
    return BallType;
}

void Ball::stickToPaddle()
{
    this->pos.x=paddle->getPos().x+(paddle->getWidth()/2) - width/2;
    this->pos.y=paddle->getPos().y-height;
    setBounds();
    stick=true;
    setDir(1,-1);
}

void Ball::move(List* worldEnt)
{
    if(stick)
    {
        stickToPaddle();
        if(BallType==STICK)
        {
            setBallType(STICK);
        }
    }

    else
    {
        //checking Ball Board collisions
        Rect a=bounds;
        SDL_Rect boardCopy=gameBoard->getBounds();
        Rect b=boardCopy;
        int collisionType=b.isInside(a);
        if (collisionType==b.COLLISIONS::LEFT || collisionType==b.COLLISIONS::RIGHT)
        {
            setDir(dx*-1,dy);
        }
        else if(collisionType==b.COLLISIONS::TOP)
        {
            setDir(dx,dy*-1);
        }
        else if (collisionType==b.COLLISIONS::DOWN)
        {
            stickToPaddle();
        }
        //BALL-BRICK and BALL-PADDLE collisions are being handled in game.cpp
        //Updating ball position
        pos.y+=dy*speed;
        pos.x+=dx*speed;
    }
    //Updating bounding rectangle
    setBounds();
}

bool Ball::isStuck()
{
    return stick;
}

void Ball::setStick(bool stick)
{
    this->stick=stick;
}

void Ball::setDir(float dx,float dy)
{
    this->dx=dx;
    this->dy=dy;
}
