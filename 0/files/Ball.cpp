#include "Ball.h"

Ball::Ball(LTexture* texture, Board* gameBoard,Paddle* paddle):Entity(texture),gameBoard(gameBoard),paddle(paddle)
{
    float x=246.0f;
    int y=3;
    this->width=12;
    this->height=12;

    for (int i=NORMAL; i<NUM_BALL_MODES; i++)
    {
        spriteClips[i]= {(int)x,y,width,height};
        x+=13;
    }

    setBounds();

    /*SPRITESHEET UPDATED,RESET THESE
    sparkleSpriteClips[0]= {96,272,16,16};

    sparkleSpriteClips[1]= {114,272,16,16};

    sparkleSpriteClips[2]= {130,272,16,16};

    sparkleSpriteClips[3]= {148,272,16,16};

    sparkleSpriteClips[4]= {165,272,16,16};

    sparkleSpriteClips[5]= {182,272,16,16};

    sparkleSpriteClips[6]= {199,272,16,16};

    sparkleSpriteClips[7]= {216,272,16,16};
    */
    type=BALL;
    setBallType(NORMAL);
    stick = true;
}

Ball::~Ball() {}

void Ball::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect(gRenderer,&bounds);
    spriteSheetTexture->render(pos.x,pos.y,&spriteClips[ballType],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void Ball::setBallType(int ballType)
{
    this->ballType=ballType;
    if(ballType==FIRE)
    {
        speed=3;
    }
    else if (ballType==STICK)
    {
        //stickToPaddle();
        //setDir(0,-1);
        speed=3;
    }
    else if(ballType==SPEED)
    {
        speed=7;
    }
    else if (ballType==NORMAL)
    {
        speed=5;
    }
}

int Ball::getBallType()
{
    return ballType;
}

void Ball::stickToPaddle()
{
    this->pos.x=paddle->getPos().x+(paddle->getWidth()/2) - width/2;
    this->pos.y=paddle->getPos().y-height;
    setBounds();
    stick=true;
//    int dirX = rand()%200 - 100;
//    int dirY = rand()%100;
//    int denom = sqrt(pow(dirX, 2) + pow(dirY, 2));
    setDir(1/sqrt(2),-1/sqrt(2));
    //setDir(dirX/denom,dirY/denom);//setting initial direction, normalized
}

void Ball::move(List* worldEnt)
{
    /*if(stick)
    {
        cout << stick << endl;
        stickToPaddle();
        if(BallType==STICK)
        {
            setBallType(STICK);
        }
    }*/
    if (stick == false)
    {
        SDL_Rect boardCopy=gameBoard->getBounds();
        //TOP BOARD COLLISION
        if(this->pos.y <= boardCopy.y)
        {
            pos.y=boardCopy.y;
            setDir(dx,dy*-1);
        }
        //LEFT BOARD COLLISION
        else if(this->pos.x + this->width >= boardCopy.x + boardCopy.w)
        {
            pos.x= boardCopy.x + boardCopy.w - this->width;
            setDir(dx*-1,dy);
        }
        //RIGHT BOARD COLLISION
        else if(this->pos.x  <= boardCopy.x )
        {
            pos.x= boardCopy.x;
            setDir(dx*-1,dy);
        }
        //DOWN COLLISION Handled in Game::collisionHandler

        pos.y+=dy*speed;
        pos.x+=dx*speed;
    }

    else
    {
        stickToPaddle();
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

void Ball::reset()
{
    setDir(1/sqrt(2),-1/sqrt(2));
    setBallType(NORMAL);
    stick = true;
}
