#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include "LTexture.h"
#include "Board.h"
#include "FileIO.h"
//#include "Brick.h"
#include "OneHitBrick.h"
#include "TwoHitBrick.h"
#include "ThreeHitBrick.h"
#include "SteelBrick.h"
#include "Point.h"
#include "List.h"
#include "Paddle.h"
#include "MainMenu.h"

class Game
{
public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void close();
    void gameLoop();
    void collisionHandler(Entity*,Entity*);
    void collisionHandler(Entity*,List*);
    void levelLoader();
    void showSplash(long int&);
    List playerEnt;
    List worldEnt;
protected:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    //The gameboard, i.e. walls
    Board* gameBoard=NULL;
    //The Main Menu
    MainMenu* mainMenu = NULL;

private:
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    int SCRNHT = SCREEN_HEIGHT;
    int SCRNWT = SCREEN_WIDTH;
    //The spritesheet
    LTexture gSpriteSheetTexture;
    //Texture for background
    LTexture bgTexture;
    //Texture for Main Menu
    LTexture mainMenuTexture;
    //Texture for Splash Screen
    LTexture splashScreen;
};

#endif // GAME_H
