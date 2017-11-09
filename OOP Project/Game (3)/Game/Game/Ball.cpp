#include "Ball.h"

Ball::Ball(LTexture* texture, Board* gameBoard,Point pos):Entity(texture,pos),gameBoard(gameBoard)
{
    int x=242;
    int y=2;
    this->width=17;
    this->height=18;
    for (int i=NORMAL; i<NUM_BALL_MODES; i++)
    {
        spriteClips[i].x = x;
        spriteClips[i].y = y;
        spriteClips[i].w = width;
        spriteClips[i].h = height;
        x+=22;
    }
    setBounds();

    sparkleSpriteClips[0] = {96,272,16,16};
    sparkleSpriteClips[1] = {114,272,16,16};
    sparkleSpriteClips[2] = {130,272,16,16};
    sparkleSpriteClips[3] = {148,272,16,16};
    sparkleSpriteClips[4] = {165,272,16,16};
    sparkleSpriteClips[5] = {182,272,16,16};
    sparkleSpriteClips[6] = {199,272,16,16};
    sparkleSpriteClips[7] = {216,272,16,16};

    bounds.x = pos.x;
    bounds.y = pos.y;
    bounds.h = 18;
    bounds.w = 20;

    BallType = 0;

    SDL_Rect gbBound = gameBoard->getBounds();

    leftBoundary = gbBound.x;
    rightBoundary = gbBound.x + gbBound.w;
    upperBound = gbBound.y;
    lowerBound = gbBound.y + gbBound.h;

    dx = 0;
    dy = 0;

    BallType = NORMAL;
}

Ball::~Ball() {}

void Ball::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    //comment to hide bounding rectangle
    SDL_RenderDrawRect(gRenderer,&bounds);
    spriteSheetTexture->render(bounds.x,bounds.y,&spriteClips[BallType],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}
static int check = 0;
bool Ball::startMove(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (check>4)
        {
            return true;
        }++check;
        return false;
    }
    else
        return false;
}

void Ball::move(double angle)
{
    if (bounds.x < rightBoundary-20 && bounds.y > upperBound )
    {
        if (BallType == SPEED)
        {
            bounds.x += 6*cos(angle*(PI/180));
            bounds.y -= 6*sin(angle*(PI/180));
        }
        else if (BallType == FIRE)
        {
            bounds.x += 3*cos(angle*(PI/180));
            bounds.y -= 3*sin(angle*(PI/180));
        }
        else
        {
            bounds.x += 2*cos(angle*(PI/180));
            bounds.y -= 2*sin(angle*(PI/180));
        }
    }
}

void Ball::setBallType(int BallType)
{
    if (BallType >= 0 && BallType < NUM_BALL_MODES)
    {
        this->BallType = BallType;
    }
}

int Ball::getBallType()
{
    return BallType;
}

void Ball::handleEvents(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_f:
                setBallType(FIRE);
                break;
            case SDLK_s:
                setBallType(SPEED);
                break;
            case SDLK_v:
                setBallType(STICK);
                break;
            case SDLK_n:
                setBallType(NORMAL);
                break;
        }
    }
}
