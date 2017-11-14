#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"
//#include "Rect.h"
#include "LTexture.h"
class List;
//ABSTRACT CLASS

class Entity
{
public:
    Entity(LTexture*,Point=Point());
    virtual ~Entity();
    int getWidth();
    int getHeight();
    SDL_Rect getBounds();
    virtual void render(long int&, SDL_Renderer*)=0;
    void setAlive(bool);
    bool getAlive();
    virtual void move(List* = NULL) {} //will be redefined in object classes that move,, the argumment is to be used only for moving objects
    bool insideBounds(int,int);
    friend class Game;
    virtual void incrementDmg() {};//Here to support polymorphic call for bricks
    virtual void setDir(float,float) {};//Here to support polymorphic call for ball
    virtual void stickToPaddle() {};
    //friend class FileIO;
    int getType();
    Point getPos();
    void setBounds();
    float getDX() {return dx;}
    float getDY() {return dy;}
    enum ENTITIES {ONEHITBRICK,TWOHITBRICK,THREEHITBRICK,STEELBRICK,MOBILEBRICK,PADDLE,BALL};
protected:
    Point pos;
    SDL_Rect bounds;
    bool alive;
    int width;
    int height;
    float dx;//used for storing direction of movement, dx&dy both behave as 2d direction vectors for the ball
    float dy;
    float speed;
    int expFrame;
    int type;
    LTexture* spriteSheetTexture;
};
#endif // ENTITY_H
