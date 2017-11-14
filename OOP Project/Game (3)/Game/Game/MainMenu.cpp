#include "MainMenu.h"

MainMenu::MainMenu(LTexture* image,Point pos):Entity(image,pos)
{
    SCREEN_HEIGHT = 0;
    SCREEN_WIDTH = 0;
    menuSprite = {0,0,1024,768};
    this->height = menuSprite.h;
    this->width = menuSprite.w;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(250,300+(i*100));
    }
    buttons[0].buttonText->setText("Play");
    buttons[1].buttonText->setText("Load");
    buttons[2].buttonText->setText("Credits");
    buttons[3].buttonText->setText("Quit");
    this->alive = true;
    option = -1;
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = _SCREEN_WIDTH;
    this->SCREEN_HEIGHT = _SCREEN_HEIGHT;
}

void MainMenu::render(long int& frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->render(0,0,&menuSprite,0.0,NULL,SDL_FLIP_NONE,gRenderer);
    for (int i=0; i<BUTTONSMAX; i++) buttons[i].render(frame,gRenderer);
}

int MainMenu::getOption()
{
    return option;
}

void MainMenu::handleEvents(SDL_Event& e)
{
    if ( e.key.keysym.sym == SDLK_e)
    {
        this->setAlive(false);
    }
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        //cout << x << ' ' << y <<endl;
        for (int i =0; i<BUTTONSMAX ; i++)
        {
            if (buttons[i].insideBounds(x,y))
            {
                buttons[i].State = 1;
            }
            else buttons[i].State = 0;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) // change the click position of the mouse
        {
            if (e.button.button == SDL_BUTTON_LEFT) // Undo Button
            {
                if (buttons[0].insideBounds(x,y))
                {
                    option = PLAY;
                }
                if (buttons[3].insideBounds(x,y))
                {
                    option = QUIT;
                }
            }
        }
    }
}
