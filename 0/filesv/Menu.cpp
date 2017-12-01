#include "Menu.h"

Menu::Menu(LTexture* image,Point pos):Entity(image,pos)
{
    menuSprite = {0,0,1024,768};
    this->height = menuSprite.h;
    this->width = menuSprite.w;

}

Menu::~Menu()
{
    //dtor
}

void Menu::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = this->width = this->menuSprite.w = _SCREEN_WIDTH;
    this->SCREEN_HEIGHT = this->height = this->menuSprite.h = _SCREEN_HEIGHT;
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setPosition(SCREEN_WIDTH/2 - buttons[i].getWidth()/2, SCREEN_HEIGHT/2 - buttons[i].getHeight()/2 + i*(buttons[i].getHeight()+20));
    }
}

void Menu::render(long int& frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->render(pos.x,pos.y,&menuSprite,0.0,NULL,SDL_FLIP_NONE,gRenderer);
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].render(frame,gRenderer);
    }
}

int Menu::getOption()
{
    return option;
}

void Menu::setOption(int opt)
{
    option = opt;
}

void Menu::handleEvents(SDL_Event& e)
{
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        //cout << x << ' ' << y <<endl;
        for (int i =0; i<MAXBUTTONS ; i++)
        {
            if (buttons[i].insideBounds(x,y))
            {
                buttons[i].State = 1;
            }
            else
            {
                buttons[i].State = 0;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) // change the click position of the mouse
        {
            if (e.button.button == SDL_BUTTON_LEFT) // Undo Button
            {
                for (int i=0;i<Menu::MAXBUTTONS;i++)
                {
                    if (buttons[i].insideBounds(x,y))
                    {
                        option = i;
                    }
                }
            }
        }
    }
}
