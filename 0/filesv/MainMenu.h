#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Menu.h"
#include "Button.h"
#include "LoadGameScreen.h"

class MainMenu: public Menu
{
public:
    // Default constructor
    MainMenu(LTexture*,Point pos = Point());
    // Default destructor
    virtual ~MainMenu();
    enum Buttons {PLAY,LOAD,CREDITS,QUIT,BUTTONSMAX};
    void handleEvents(SDL_Event& e);
    LoadGameScreen* loadState = NULL;

protected:

private:
    Uint32 firstTick = 0;

};

#endif // MAINMENU_H
