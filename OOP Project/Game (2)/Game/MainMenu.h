#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stack>
#include <vector>
#include "Entity.h"
#include "Button.h"


class MainMenu:public Entity
{
public:
    // Default constructor
    MainMenu(LTexture*,Point pos = Point());
    // Default destructor
    virtual ~MainMenu();
    // Copy constructor
    MainMenu(const MainMenu& other);
    void render(long int&,SDL_Renderer* gRenderer);
    void setDimensions(int,int);
    enum Buttons {PLAY,LOAD,CREDITS,QUIT,BUTTONSMAX};
    void handleEvents(SDL_Event& e);
    int getOption();
protected:

private:
    vector <Button> buttons;
    int option;
    int SCREEN_HEIGHT, SCREEN_WIDTH;
    SDL_Rect menuSprite;
};

#endif // MAINMENU_H
