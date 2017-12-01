#include "Screens.h"

using namespace std;

Screen::Screen(LTexture* texture)
{
   this->screenTexture = texture;
   imageRect = {0,0,screenTexture->getWidth(),screenTexture->getHeight()};
   outputRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
   show = true;
   hide = false;
   stay = false;
}

Screen::~Screen()
{
    //dtor
}

bool Screen::ScreenIn(long int& frame,SDL_Renderer* gRenderer)
{
    if ((frame*2)%256 >= 252)
    {
        return true;
    }
    screenTexture->setAlpha((frame*2)%256);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
    return false;
}

bool Screen::ScreenOut(long int& frame,SDL_Renderer* gRenderer)
{
    if (255 - (frame*2)%256 <= 2)
    {
        return true;
    }
    screenTexture->setAlpha(255 -(frame*2)%256);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
    return false;
}

void Screen::ScreenStay(long int& frame,SDL_Renderer* gRenderer)
{
    screenTexture->setAlpha(255);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
}

void Screen::setDimensions(int width,int height)
{
    this->SCREEN_HEIGHT = height;
    this->SCREEN_WIDTH = width;
    outputRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
}

bool Screen::getAlive()
{
    return alive;
}

void Screen::setAlive(bool isAlive)
{
    this->alive = isAlive;
}

void Screen::render(long int& frame,SDL_Renderer* gRenderer,int delay)
{
    if (show)
    {
        stay = ScreenIn(frame,gRenderer);
        if (stay)
        {
            splTick = SDL_GetTicks();
        }
    }
    if (stay)
    {
        show = false;
        ScreenStay(frame,gRenderer);
        if ((SDL_GetTicks()-splTick)/1000 >= delay && (frame*2)%256 == 0)
        {
            hide = true;
            stay = false;
        }
    }
    if (hide)
    {
        if (ScreenOut(frame,gRenderer))
        {
            alive = false;
        }
    }
}
