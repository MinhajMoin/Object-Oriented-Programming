#include "Paddle.h"
#include "Ball.h"
Paddle::Paddle(LTexture* image, Board* gameBoard):Entity(image),gameBoard(gameBoard),ball(NULL)
{
    // ((16,133), (32,14)), ((120,131),(32,15)), (223,132), (32,14))
    // ((16,159), (54,14)), ((120,157), (54,15)), ((223,158), (54,14))
    // ((16,185), (82,14)), ((120,183), (82,15)), ((223, 184), (82,14))

    //Setting position of paddle a/c to the board

    // this->pos.x=(gameBoard->getBounds().x + gameBoard->getBounds().w)/2;
    padPowerTime = 0;
    ballPowerTime = 0;
    this->pos.x = gameBoard->getBounds().x + gameBoard->getBounds().w/2.0f;
    this->pos.y=(gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f;
    int xList[] = {16,120,223};
    int yList[] = {133,131,132};
    widthList[SMALL] = 32;
    widthList[MEDIUM] = 54;
    widthList[LARGE] = 82;
    heightList[NORMAL] = 14;
    heightList[FIRE] = 15;
    heightList[TURTLE] = 14;
    for(int i=NORMAL; i<NUM_PADDLE_MODES; i++)
    {
        for(int j=SMALL; j<NUM_PADDLE_SIZES; j++)
        {
            spriteClips[i][j].x=xList[i];
            spriteClips[i][j].y=yList[j]+ 26*j;
            spriteClips[i][j].w=widthList[j];
            spriteClips[i][j].h=heightList[i];
        }
    }

    //Starting with default
    mode = NORMAL;
    size = MEDIUM;
    restoreMode();
    type=PADDLE;
    speed = 10;
    //amoSize = 10;
    //bulletsUsed = 0;
    // firing = false;
    //bulletPositionOffset = 2;
    boardBounds = gameBoard->getBounds();
    // bullets = new Bullet*[NUM_BULLET_POSITIONS*amoSize];

    // for (int i=0; i<NUM_BULLET_POSITIONS*amoSize; i++)
    {
        //    bullets[i] = new Bullet(image, gameBoard);
    }
}
Paddle::~Paddle()
{
    //delete bullets;
    gameBoard=NULL;
//    bullets = NULL;
}

void Paddle::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    spriteSheetTexture->render(pos.x,pos.y,&spriteClips[mode][size],0.0, NULL, SDL_FLIP_NONE, gRenderer);
    SDL_RenderDrawRect(gRenderer,&bounds);
    /*   for (int i=0; i<NUM_BULLET_POSITIONS*amoSize; i++)
       {
           if (bullets[i] != NULL)
           {
               if (bullets[i]->isFired())
               {
                   bullets[i]->render(frame, gRenderer);
               }
           }
       }*/
}

void Paddle::setDimensions()
{
    width = widthList[size];
    height = heightList[mode];
}

void Paddle::fireUp()
{
    mode = FIRE;
    speed=15;
    setDimensions();
    setBounds();
}

void Paddle::turtleDown()
{
    mode = TURTLE;
    speed = 3;
    setDimensions();
    setBounds();
}

void Paddle::restoreMode()
{
    mode = NORMAL;
    speed=10;
    setDimensions();
    setBounds();
}

void Paddle::diminish()
{
    pos.x = pos.x + widthList[size]/2 - widthList[SMALL]/2;
    size = SMALL;
    setDimensions();
    setBounds();
}

void Paddle::enlarge()
{
    pos.x = pos.x + widthList[size]/2 - widthList[LARGE]/2;
//    cout << pos.x << ", " << widthList[LARGE] << ", " << boardBounds.x << ", " << boardBounds.w << endl;
    if (pos.x + widthList[LARGE] > boardBounds.x + boardBounds.w)
    {
//        cout << "true" << endl;
        pos.x = boardBounds.x + boardBounds.w - widthList[LARGE];
    }
    else if (pos.x < boardBounds.x)
    {
        pos.x = boardBounds.x;
    }
    size = LARGE;
    setDimensions();
    setBounds();
}

void Paddle::restoreSize()
{
    pos.x = pos.x + widthList[size]/2 - widthList[MEDIUM]/2;
    size = MEDIUM;
    setDimensions();
    setBounds();
}
void Paddle::handleEvents(SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION)//if the event is moving mouse
    {
        //Get mouse position
        SDL_GetMouseState(&mouseX,NULL);
    }
    /*
    if (e.type == SDL_MOUSEBUTTONDOWN && mode == FIRE)
    {
        firing = true;
    }

    if (e.type == SDL_MOUSEBUTTONUP && mode == FIRE && firing)
    {
        firePair();
        firing = false;
    }*/

}
void Paddle::move(List*)
{
    //Move part
    SDL_GetMouseState(&mouseX,NULL);
    if (pos.x + bounds.w <= boardBounds.x + boardBounds.w && pos.x >= boardBounds.x)
    {
        int expectedPos=0;
        if (mouseX > pos.x + width/2)
        {
            expectedPos = pos.x + speed;
            if (expectedPos + width/2 < mouseX && expectedPos + width <= boardBounds.x + boardBounds.w)
            {
                pos.x = expectedPos;
            }
            else if (mouseX <= boardBounds.x + boardBounds.w - width/2)
            {
                pos.x = mouseX - width/2;
            }
            else
            {
                pos.x = boardBounds.x + boardBounds.w - width;
            }
        }

        else if (mouseX < pos.x + width/2)
        {
            expectedPos = pos.x - speed;
            if (expectedPos + width/2 > mouseX && expectedPos >= boardBounds.x)
            {
                pos.x = expectedPos;
            }
            else if (mouseX >= boardBounds.x + width/2)
            {
                pos.x = mouseX - width/2;
            }
            else
            {
                pos.x = boardBounds.x;
            }
        }
    }
    /*
    for (int i=0; i<NUM_BULLET_POSITIONS*amoSize; i++)
    {
        if (bullets[i] != NULL)
        {
            if (bullets[i]->isFired())
            {
                if (!bullets[i]->isSmashed()) //getPos().y <= boardBounds.y)
                {
                    bullets[i]->move();
                }
                else if (bullets[i]->isFinished())
                {
                    delete bullets[i];
                    bullets[i] = NULL;
                }
            }
        }
    }*/
    setDimensions();
    setBounds();
    /* Restoring pad or ball after time being elapsed, done here as this function is continuously being called, hence saving work
    to be done in game and that of making getters and setters*/
    if (((time(NULL) - padPowerTime)>10) && padPowerTime != 0) setPower(this,1);
    if (((time(NULL) - ballPowerTime)>10) && ballPowerTime != 0 ) setPower(this,0,1);
}

/*
void Paddle::firePair()
{
    static int leftIndex = LEFT;
    static int rightIndex = RIGHT;
    if (bulletsUsed < amoSize)
    {
        bullets[leftIndex]->setPosition(getLeftBulletPosition(leftIndex));
        bullets[rightIndex]->setPosition(getRightBulletPosition(rightIndex));
        bullets[leftIndex]->fire();
        bullets[rightIndex]->fire();
        leftIndex += NUM_BULLET_POSITIONS;
        rightIndex += NUM_BULLET_POSITIONS;
        bulletsUsed++;
    }
}

Point Paddle::getLeftBulletPosition(int index)
{
    int x = pos.x + bulletPositionOffset;
    int y = pos.y - bullets[index]->getHeight();
    return Point(x,y);
}

Point Paddle::getRightBulletPosition(int index)
{
    int x = pos.x + width - bullets[index]->getWidth() - bulletPositionOffset;
    int y = pos.y - bullets[index]->getHeight();
    return Point(x,y);
}
*/
int Paddle::getPaddleMode()
{
    return mode;
}

void Paddle::setPower(Entity* give, int restPad, int restBall)
{
    currentPower = give;
    if (currentPower->getWhich() == PowerUp::RESTORE_PAD || restPad)
    {
        restoreMode();
        restoreSize();
        padPowerTime = 0;
        cout << "restore pad"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::ELONGATE)
    {
        enlarge();
        padPowerTime=time(NULL);
        cout << "enlarge pad"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::SHORTEN)
    {
        diminish();
        padPowerTime=time(NULL);
        cout << "shorten pad"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::TURTLE)
    {
        turtleDown();
        padPowerTime=time(NULL);
        cout << "turtle the pad"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::BULLET)
    {
        fireUp();
        padPowerTime=time(NULL);
        cout << "golian"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::MISSILE)
    {
        padPowerTime=time(NULL);
        cout << "missile bro"<<endl;
    }         //missile_up when made
    else if (currentPower->getWhich() == PowerUp::RESTORE_BALL || restBall)
    {
        ball->setBallType(ball->BALL_MODE::NORMAL);
        ballPowerTime = 0;
        cout << "restore ball"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::FIREBALL)
    {
        ball->setBallType(ball->BALL_MODE::FIRE);
        ballPowerTime=time(NULL);
        cout << "fiery ball"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::SPEEDBALL)
    {
        ball->setBallType(ball->BALL_MODE::SPEED);
        ballPowerTime=time(NULL);
        cout << "speedy ball on"<<endl;
    }
    else if (currentPower->getWhich() == PowerUp::STICKYBALL)
    {
        ball->setBallType(ball->BALL_MODE::STICK);
        ballPowerTime=time(NULL);
        cout << "sticky ball on"<<endl;
    }
    else
    {
        cout << "abhi yeh set nhi huay"<<endl;
    }

}

void Paddle::setBall(Ball* ball)
{
    this->ball=ball;
}

void Paddle::reset()
{
    restoreMode();
    restoreSize();
    this->pos.x = 70;
    this->pos.y=(gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f;
}
