#include "GUI.h"
#include <SDL.h>

GUI::GUI(LTexture* image,Point pos):Entity(image,pos)
{
    this->height = 0;
    this->width = 0;
    this->alive = true;
    this->scoreText = new Text("0",image);
    scoreText->color = 0;
    this->timeText = new Text("0",image);
    timeText->color = 0;
    this->livesText = new Text("0",image);
    livesText->color = 0;
    timeHeading = new Text("Time",image);
    timeHeading->setSize(0.7);
    powerupText = new Text("PowerUp",image);
    powerupText->setSize(0.7);
    for (int i=0; i<4; i++)
    {
        powerupIcons[i] = {909+(26*i),937,26,26};
        powerupIcons[i+4] = {909+(26*i),937+26,26,26};
        powerupIcons[i+8] = {909+(26*i),937+(26*2),26,26};
    }
}

void GUI::setDimensions(int w, int h)
{
    this->SCREEN_WIDTH = w;
    this->SCREEN_HEIGHT = h;
    scoreText->setPosition(150 - scoreText->getWidth()/2 ,40);
    timeHeading->setPosition(SCREEN_WIDTH/2,40);
    timeText->setPosition(SCREEN_WIDTH/2,80);
    livesText->setPosition(160 - livesText->getWidth()/2 ,80);
    powerupText->setPosition(SCREEN_WIDTH-(2*powerupText->getWidth())/3,40);
    GUIBg = {0,0,SCREEN_WIDTH,90};
}

void GUI::setTime(Uint32& initialTicks)
{
    time = (SDL_GetTicks() - initialTicks)/1000;
    stringstream ss;
    if (time/60 < 10) ss << '0';
    ss << time/60 << ':';
    if (time%60 < 10) ss << '0';
    ss << (time%60);
    timeText->setText(ss.str());
    timeText->setSize(0.7);
}
void GUI::setPowerUp(int& powerup)
{
    this->currentPowerup = powerup;
}
void GUI::setScore(int& score)
{
    stringstream ss;
    stringstream sp;
    sp<<score;
    ss<< "Score:";
    ss << string(5-sp.str().length(),'0') << score;
    scoreText->setText(ss.str());
    scoreText->setSize(0.7);
    scoreText->setPosition(scoreText->getWidth()/2 + 20,40);
}

void GUI::setLives(int& lives)
{
    stringstream ss;
    ss<<"Lives:"<< lives;
    livesText->setText(ss.str());
    livesText->setSize(0.7);
    livesText->setPosition(livesText->getWidth()/2 + 20,80);
}


GUI::~GUI()
{
    //dtor
}

void GUI::render(long int& frame,SDL_Renderer* gRenderer)
{
    //SDL_SetRenderDrawColor(gRenderer,0,150,15,rand()%255);
    //SDL_RenderFillRect(gRenderer,&GUIBg);
    timeText->render(frame,gRenderer);
    timeHeading->render(frame,gRenderer);
    livesText->render(frame,gRenderer);
    scoreText->render(frame,gRenderer);
    powerupText->render(frame,gRenderer);
    spriteSheetTexture->render(powerupText->getPos().x,powerupText->getPos().y+10,&powerupIcons[currentPowerup],0.0,NULL,SDL_FLIP_NONE,gRenderer);
}
void GUI::toggleColor()
{
    timeText->color=!(timeText->color);
    livesText->color=!(livesText->color);
    scoreText->color=!(scoreText->color);
    timeHeading->color=!(timeHeading->color);
    powerupText->color=!(powerupText->color);
}


