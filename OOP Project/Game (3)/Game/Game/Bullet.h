#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "Smasher.h"

class Bullet : public Smasher
{

public:
    Bullet(LTexture*, Board*, Point= Point());
    virtual ~Bullet();
    void render(long int&, SDL_Renderer*);
    void setPosition(Point);
    void move();
    bool isFired();
    void fire();

protected:
    SDL_Rect spriteClips[1];
    bool fired;
    SDL_Rect boardBounds;
    int delay;
};

#endif // BULLET_H_INCLUDED
