#include "Button.h"

Button::Button(LTexture* image,Point pos):Entity(image,pos)
{
    buttonRects[0] = {457,1089,512,74};
    buttonRects[1] = {457,1174,512,74};
    this->height = buttonRects[0].h;
    this->width = buttonRects[0].w;
    this->bounds = {(int)pos.x,(int)pos.y,width,height};
    this->buttonText = new Text(" ",image,pos);
    buttonText->setPosition(x+width/2,y+height/2);
}

Button::~Button()
{
    //dtor
}
void Button::render(long int& frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->render(pos.x,pos.y,&buttonRects[State],0.0,NULL,SDL_FLIP_NONE,gRenderer);
    buttonText->color = State;
    buttonText->render(frame,gRenderer);
}

void Button::setPosition(int x, int y)
{
    this->pos.x = x;
    this->pos.y = y;
    this->bounds = {x,y,width,height};
    buttonText->setPosition(x+width/2,y+height/2);
}
