#ifndef BALL_H
#define BALL_H
#include "Entity.h"
#include <math.h>
#include "Board.h"
#include <SDL.h>
#define PI 3.14159265
#include "Paddle.h"
#include "Rect.h"

class Ball: public Entity
{
public:

    Ball(LTexture*,Board*,Paddle*);      //constructor

    virtual ~Ball();                            //destructor

    enum BALL_MODE {NORMAL,STICK,SPEED,FIRE,NUM_BALL_MODES};

    void render(long int&, SDL_Renderer*);          //Rendering function

    void setBallType(int);

    int getBallType();

    bool startMove(SDL_Event&);

    void move(List* = NULL);

    void stickToPaddle();

    bool isStuck();

    void setStick(bool);

    void setDir(float,float);

    void reset();
private:

    SDL_Rect spriteClips[NUM_BALL_MODES];             // To store ball sprites

    SDL_Rect sparkleSpriteClips[8];              //To store the sparkle sprites

    int ballType;       //Flag to check what type of ball it is

    Board* gameBoard;

    Paddle* paddle;

    bool stick;
};

#endif // BALL_H
