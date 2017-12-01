#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Menu.h"
#include "Button.h"
#include "LTexture.h"
#include "MainMenu.h"


class GameOver : public Menu
{
public:
    /** Default constructor */
    GameOver(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~GameOver() {};
    enum Buttons {CONTINUE,QUIT,BUTTONSMAX};
    void handleEvents(SDL_Event& e);
    MainMenu* mainMenu = NULL;
    bool resetGame;
    void render(long int& frame,SDL_Renderer* gRenderer);
    void setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT);

protected:

private:
    Text* gameOverText;
    Text* gameOverCounter;
};

#endif // GAMEOVER_H
