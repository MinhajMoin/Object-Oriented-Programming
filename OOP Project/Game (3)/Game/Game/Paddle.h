#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
#include "Entity.h"
#include "Board.h"
class Paddle : public Entity
{

public:
    Paddle(LTexture*, Board*, Point = Point(484, 670));
    virtual ~Paddle();
    enum PADDLE_MODES {NORMAL,FIRE,TURTLE,NUM_PADDLE_MODES};
    enum PADDLE_SIZES {SMALL,MEDIUM,LARGE,NUM_PADDLE_SIZES};
    void render(long int&, SDL_Renderer*);
    void setBounds();
    void fireUp();
    void turtleDown();
    void restoreMode();
    void diminish();
    void enlarge();
    void restoreSize();
    void setMouseX(SDL_Event&);
    void move();

protected:
    SDL_Rect spriteClips[NUM_PADDLE_MODES][NUM_PADDLE_SIZES];
    int mode;
    int size;
    Point position;
    int widthList[NUM_PADDLE_SIZES];
    int heightList[NUM_PADDLE_MODES];
    int rightBoundary;
    int leftBoundary;
    int mouseX;
    Board* gameBoard;
    //int color;
};

#endif // PADDLE_H_INCLUDED
