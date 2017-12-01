#include "GameOver.h"

GameOver::GameOver(LTexture* image,Point pos):Menu(image,pos)
{
    gameOverText = new Text("Game Over",image,pos);
    gameOverCounter = new Text("02:23",image,pos);
    gameOverText->setSize(2);
    gameOverText->color = 1;
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[CONTINUE].buttonText->setText("Continue");
    buttons[QUIT].buttonText->setText("Quit");
    option = -1;
}

void GameOver::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    Menu::setDimensions(_SCREEN_WIDTH,_SCREEN_HEIGHT);
//    cout << _SCREEN_WIDTH/2 << ' ' << gameOverText->getWidth()/2;
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setPosition(SCREEN_WIDTH/2 - buttons[i].getWidth()/2, SCREEN_HEIGHT/2 + i*(buttons[i].getHeight()+20));
    }
    gameOverText->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3);
//    cout << SCREEN_WIDTH/2 << ' ' << SCREEN_HEIGHT/3 << endl;
}

void GameOver::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
        case CONTINUE:
        {
            option = -1;
            resetGame = true;
            alive = false;
            break;
        }
        case QUIT:
        {
            option = -1;
            resetGame = true;
            if (mainMenu)
            {
                mainMenu->setAlive(true);
            }
            this->alive = false;
            break;
        }
    }
}

void GameOver::render(long int& frame,SDL_Renderer* gRenderer)
{
    Menu::render(frame,gRenderer);
    gameOverText->render(frame,gRenderer);

}

