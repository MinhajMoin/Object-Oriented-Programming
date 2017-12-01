#include "LoadGameScreen.h"

LoadGameScreen::LoadGameScreen(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[STATE1].buttonText->setText("State 1");
    buttons[STATE2].buttonText->setText("State 2");
    buttons[STATE3].buttonText->setText("State 3");
    buttons[CANCEL].buttonText->setText("Cancel");
}

void LoadGameScreen::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
        case STATE1:
        {
            if (mode == SAVE)
            {
                cout << "SAVE 1" << endl;
                //Save the game
            }
            else if (mode == LOAD)
            {
                cout << "LOAD 1" << endl;
                //Load the game
            }
            mode = -1;
            option = -1;
            break;
        }
        case STATE2:
        {
            if (mode == SAVE)
            {
                cout << "SAVE 2" << endl;
                //Save the game
            }
            else if (mode == LOAD)
            {
                cout << "LOAD 2" << endl;
                //Load the game
            }
            mode = -1;
            option = -1;
            break;
        }
        case STATE3:
        {
            cout << "WD";
            if (mode == SAVE)
            {
                cout << "SAVE 3" << endl;
                //Save the game
            }
            else if (mode == LOAD)
            {
                cout << "LOAD 3" << endl;
                //Load the game
            }
            mode = -1;
            option = -1;
            break;
        }
        case CANCEL:
        {
            cout << "CANCEL" << endl;
            option = -1;
            this->alive = false;
            parentMenu->setAlive(true);
        }
    }
}
