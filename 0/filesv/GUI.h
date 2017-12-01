#ifndef GUI_H
#define GUI_H

#include "Entity.h"
#include "Text.h"
#include <string>
#include <sstream>

class GUI : public Entity
{
public:
    /** Default constructor */
    GUI(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~GUI();
    void setTime(Uint32& initialTicks);
    void setScore(int& score);
    void setLives(int& lives);
    void setDimensions(int x,int y);
    void render(long int& frame,SDL_Renderer* gRenderer);
    void toggleColor();
    void setPowerUp(int& powerup);

protected:

private:
    Uint32 time = 0;
    int currentPowerup=0;
    Text* scoreText = NULL;
    Text* timeText = NULL;
    Text* livesText = NULL;
    Text* timeHeading = NULL;
    Text* powerupText = NULL;
    SDL_Rect powerupIcons[12];
    SDL_Rect GUIBg;
    int SCREEN_HEIGHT;
    int SCREEN_WIDTH;

};

#endif // GUI_H
