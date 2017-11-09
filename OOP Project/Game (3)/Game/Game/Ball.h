#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include <math.h>
#include "Board.h"
#include <SDL.h>
#define PI 3.14159265

class Ball: public Entity
{
public:

    Ball(LTexture*,Board*,Point=Point(511,652));      //constructor

    virtual ~Ball();                            //destructor

    enum BALL_MODE {NORMAL,STICK,SPEED,FIRE,NUM_BALL_MODES};

    void handleEvents(SDL_Event& e);

    void render(long int&, SDL_Renderer*);          //Rendering function

    void setBallType(int);

    int getBallType();

    bool startMove(SDL_Event&);

    void move(double);

private:
    SDL_Rect spriteClips[NUM_BALL_MODES];             // To store ball sprites

    SDL_Rect sparkleSpriteClips[8];              //To store the sparkle sprites

    int BallType;       //Flag to check what type of ball it is

    int leftBoundary;

    int rightBoundary;

    int upperBound;

    int lowerBound;

    Board* gameBoard;
};

#endif // BALL_H
