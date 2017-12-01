#include "MainMenu.h"

MainMenu::MainMenu(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[0].buttonText->setText("New Game");
    buttons[1].buttonText->setText("Load");
    buttons[2].buttonText->setText("Credits");
    buttons[3].buttonText->setText("Quit");
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
        case PLAY:
        {
            alive = false;
            option = -1;

            break;
        }
        case LOAD:
        {
            alive = false;
            option = -1;
            cout << "LOAD GAME SCREEN" << endl;
            if (loadState)
            {
                loadState->mode = LoadGameScreen::LOAD;
                loadState->parentMenu = this;
                loadState->setAlive(true);
            }
            break;
        }
        case CREDITS:
        {
            break;
        }
    }
}
