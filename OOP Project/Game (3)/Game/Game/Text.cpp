#include "Text.h"

Text::Text(string word,LTexture* image,Point pos):Entity(image,pos)
{
    SCREEN_HEIGHT = 0;
    SCREEN_WIDTH = 0;
    for (int i = 0; i < 13; i++ )
    {
        SDL_Rect charRect = {377+(40*i),800,40,40};
        Characters.insert ( pair<char,SDL_Rect>((char)(i+97),charRect) );
    }
    for (int i = 13; i < 26; i++ )
    {
        SDL_Rect charRect = {377+(40*(i-13)),839,40,40};
        Characters.insert ( pair<char,SDL_Rect>((char)(i+97),charRect) );
    }
    this->text = word;
    this->height = 40;
    this->width = word.length()*40;
    color = 0;
}

Text::~Text()
{
    //dtor
}

void Text::setText(string str)
{
    this->text = str;
    this->width = str.length()*40;
}

void Text::setPosition(float x, float y)
{
    this->pos.x = x;
    this->pos.y = y;
}

void Text::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = _SCREEN_WIDTH;
    this->SCREEN_HEIGHT = _SCREEN_HEIGHT;
}

void Text::render(long int& frame, SDL_Renderer* gRenderer)
{
    for (unsigned int i = 0; i<text.length(); i++)
    {
        char Char = text[i] ;
        if ((int)text[i] >= 65 && (int)text[i] < 97)
        {
            Char = (char)((int)text[i] + 32);
        }
        SDL_Rect renderQuad = {Characters[Char].x,Characters[Char].y,Characters[Char].w,Characters[Char].h};
        if (color == 1 )
        {
            renderQuad.y += 110;
        }
        spriteSheetTexture->render(pos.x-width/2+(i*40),pos.y-height/2,&renderQuad,0.0,NULL,SDL_FLIP_NONE,gRenderer);
    }
}
