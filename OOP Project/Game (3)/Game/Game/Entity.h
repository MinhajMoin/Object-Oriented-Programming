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
    Entity(LTexture*,Point);
    virtual ~Entity();
    int getWidth();
    int getHeight();
    SDL_Rect getBounds();
    virtual void render(long int&, SDL_Renderer*)=0;
    void setAlive(bool);
    bool getAlive();
    virtual void move(List* = NULL) //will be redefined in object classes that move,, the argumment is to be used only for moving objects
    {
        /*cout << "Ent move called" << endl;*/
    };
    bool insideBounds(int,int);
    friend class Game;
    virtual void incrementDmg()
    {
        std::cout << "BOOP";
    };
    friend class FileIO;
    int getType();
    Point getPos();
    void setBounds();
    enum ENTITIES {ONEHITBRICK,TWOHITBRICK,THREEHITBRICK,STEELBRICK,MOBILEBRICK};
protected:
    Point pos;
    SDL_Rect bounds;
    bool alive;
    int width;
    int height;
    float dx;//used for storing direction of movement
    float dy;
    float speedX;
    float speedY;
    int expFrame;
    int type;

    LTexture* spriteSheetTexture;
};
#endif // ENTITY_H
