#include "PauseMenu.h"


PauseMenu::PauseMenu(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = PauseMenu::BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[RESUME].buttonText->setText("Resume");
    buttons[SAVE].buttonText->setText("Save");
    buttons[QUIT].buttonText->setText("Quit");
}

void PauseMenu::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
//    if (e.key.keysym.sym == SDLK_ESCAPE)
//    {
//        this->alive = true;
//        option = -1;
//    }
    switch(option)
    {
        case RESUME:
        {
            this->alive = false;
            option = -1;
            break;
        }
        case SAVE:
        {
            cout << "SAVE GAME SCREEN" << endl;
            this->alive = false;
            if (saveState)
            {
                saveState->mode = LoadGameScreen::SAVE;
                saveState->parentMenu = this;
                saveState->setAlive(true);
            }
            option = -1;
            break;
        }
        case QUIT:
        {
            this->alive = false;
            option = -1;
            if (mMenu)
            {
                mMenu->setAlive(true);
            }
            resetGame = true;
            break;
        }
    }
}
