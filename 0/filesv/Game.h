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
#include "OneHitBrick.h"
#include "TwoHitBrick.h"
#include "ThreeHitBrick.h"
#include "SteelBrick.h"
#include "MobileBrickX.h"
#include "MobileBrickY.h"
#include "InvisibleBrick.h"
#include "Point.h"
#include "List.h"
#include "Paddle.h"
#include "MainMenu.h"
#include "Ball.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "LoadGameScreen.h"
#include "Screens.h"
#include "GameOver.h"
#include "GameCompleteScreen.h"

class Game
{
public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void loadMenus();
    void close();
    void gameLoop();
    void handleEvents(SDL_Event, bool&, bool&);
    void collisionHandler(Entity*,Entity*);
    void collisionHandler(Entity*,List*);
    void collisionHandler(List*, List*);
    void levelLoader(string = "");
    bool showSplash(long int& frame);
    bool hideSplash(long int& frame);
    void Splash();
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
    //Game GUI
    GUI* gameGUI = NULL;
    //Splash Screen
    Screen* splashScreen = NULL;
    //Pause Menu
    PauseMenu* pauseMenu = NULL;
    //Load States Screen
    LoadGameScreen* loadState = NULL;
    //GameOver Screen
    GameOver* gameOver = NULL;
    //levelComplete Screen
    GameCompleteScreen* levelComplete = NULL;
    //Vector of Menus
    vector <Menu*>Menus;
    //Vector of Screens
    vector <Screen*> Screens;

private:
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;
    const int DAYTIME = 15;//time in seconds after which day/night will switch
    //The spritesheet

    int lives =10;
    int score =0;
    LTexture gSpriteSheetTexture;
    //Texture for background
    LTexture bgTexture;
    //Texture for Main Menu
    LTexture mainMenuTexture;
    //Texture for Pause Menu
    LTexture pauseMenuTexture;
    //Texture for Splash Screen
    LTexture splash;
};

#endif // GAME_H
