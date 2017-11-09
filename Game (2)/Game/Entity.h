#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"
//#include "Rect.h"
#include "LTexture.h"

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
    virtual void move() {};
    bool insideBounds(int,int);
    friend class Game;
    virtual void incrementDmg()
    {
        std::cout << "BOOP";
    };
    friend class FileIO;
protected:
    Point pos;
    SDL_Rect bounds;
    bool alive;
    int width;
    int height;
    float dx;
    float dy;
    int expFrame;
    LTexture* spriteSheetTexture;
};
#endif // ENTITY_H
