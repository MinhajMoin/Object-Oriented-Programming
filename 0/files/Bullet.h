#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "Smasher.h"

class Bullet : public Smasher
{

public:
    Bullet(LTexture*, Board*, Paddle*, int);
    virtual ~Bullet();
    void render(long int&, SDL_Renderer*);
    enum BULLET_POSITIONS {LEFT, RIGHT, NUM_BULLET_POSITIONS};
    void setPosition(Point);
    void move(List* = NULL);
    bool isFired();
    void fire();
    void initializePosition();
    void setAlive(bool alive);//OVERRIDING METHOD FROM ENTITY
protected:
    SDL_Rect spriteClips[1];
    bool fired;
    SDL_Rect boardBounds;
    int delay;
    int bulletPosition;
    int bulletPositionOffset;
};

#endif // BULLET_H_INCLUDED
