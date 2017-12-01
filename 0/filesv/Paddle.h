#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
#include "Entity.h"
#include "Board.h"
#include "PowerUp.h"

//#include "Ball.h"
//#include "Bullet.h"
class Ball;
class Paddle : public Entity
{
public:
    Paddle(LTexture*, Board*);//, Ball*);
    virtual ~Paddle();
    enum PADDLE_MODES {NORMAL,FIRE,TURTLE,NUM_PADDLE_MODES};
    enum PADDLE_SIZES {SMALL,MEDIUM,LARGE,NUM_PADDLE_SIZES};
    void render(long int&, SDL_Renderer*);
    void setDimensions();
    void fireUp();
    void turtleDown();
    void restoreMode();
    void diminish();
    void enlarge();
    void restoreSize();
    //void setMouseX(SDL_Event&);
    void move(List* = NULL);
    //void firePair();
    Point getLeftBulletPosition(int);
    Point getRightBulletPosition(int);
    void handleEvents(SDL_Event&);
    int getPaddleMode();
    void setPower(Entity*,int = 0, int = 0);
    void setBall(Ball*);
    void reset();
protected:
    SDL_Rect spriteClips[NUM_PADDLE_MODES][NUM_PADDLE_SIZES];
    int mode;
    int size;
    int widthList[NUM_PADDLE_SIZES];
    int heightList[NUM_PADDLE_MODES];
    int mouseX;
    Board* gameBoard;
    Entity* currentPower;
    int padPowerTime;
    int ballPowerTime;
    //int amoSize;
    //int bulletsUsed;
    // Bullet** bullets;
    //LTexture* image;
    SDL_Rect boardBounds;
    Ball* ball;
    // bool firing;
    //int bulletPositionOffset;
};

#endif // PADDLE_H_INCLUDED
