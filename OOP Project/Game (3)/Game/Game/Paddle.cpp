#include "Paddle.h"

Paddle::Paddle(LTexture* image, Board* gameBoard, Point pos):Entity(image,pos),gameBoard(gameBoard)
{
    // ((16,133), (32,14)), ((120,131),(32,15)), (223,132), (32,14))
    // ((16,159), (54,14)), ((120,157), (54,15)), ((223,158), (54,14))
    // ((16,185), (82,14)), ((120,183), (82,15)), ((223, 184), (82,14))
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
            spriteClips[i][j].y=yList[j]+26*j;
            spriteClips[i][j].w=widthList[j];
            spriteClips[i][j].h=heightList[i];
        }
    }

    //Starting with default

    position = pos;
    mode = TURTLE;
    size = LARGE;

    rightBoundary = 992;
    leftBoundary = 30;
    setBounds();

}
Paddle::~Paddle()
{
    //dtor
}

void Paddle::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect(gRenderer,&bounds);
    spriteSheetTexture->render(position.x,position.y,&spriteClips[mode][size],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void Paddle::setBounds()
{
    bounds.x=position.x;
    bounds.y=position.y;
    bounds.w=widthList[size];
    bounds.h=heightList[mode];
}

void Paddle::fireUp()
{
    mode = FIRE;
    setBounds();
}

void Paddle::turtleDown()
{
    mode = TURTLE;
    setBounds();
}

void Paddle::restoreMode()
{
    mode = NORMAL;
    setBounds();
}

void Paddle::diminish()
{
    position.x = position.x + widthList[size]/2 - widthList[SMALL]/2;
    size = SMALL;
    setBounds();
}

void Paddle::enlarge()
{
    position.x = position.x + widthList[size]/2 - widthList[LARGE]/2;
    size = LARGE;
    setBounds();
}

void Paddle::restoreSize()
{
    position.x = position.x + widthList[size]/2 - widthList[MEDIUM]/2;
    size = MEDIUM;
    setBounds();
}

void Paddle::setMouseX(SDL_Event &e)
{
    if(e.type == SDL_MOUSEMOTION)//if the event is moving mouse
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x,&y);
        SDL_Rect boardBounds=gameBoard->getBounds();
        setBounds();
        if(x <= boardBounds.x || (x+bounds.w)>=(boardBounds.x+boardBounds.w))//If pad is colliding with the board, keep it at its position
        {
            return;
        }
        else
        {
            position.x=x;//movement only in x direction
            setBounds();
        }
    }
}

void Paddle::move()
{
    Point midPos(bounds.x+bounds.w/2, bounds.y+bounds.h/2);
    if (mouseX>midPos.x && bounds.x+bounds.w<rightBoundary)
    {
        if (mode == NORMAL)
        {
            position.x+=2;
        }

        else if (mode == FIRE)
        {
            position.x+=4;
        }

        else if (mode == TURTLE)
        {
            position.x+=1;
        }
    }

    else if (mouseX<midPos.x && bounds.x>leftBoundary)
    {
        if (mode == NORMAL)
        {
            position.x-=2;
        }

        else if (mode == FIRE)
        {
            position.x-=4;
        }

        else if (mode == TURTLE)
        {
            position.x-=1;
        }
    }

    setBounds();
}
