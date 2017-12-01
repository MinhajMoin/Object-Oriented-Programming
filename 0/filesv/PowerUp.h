#ifndef POWERUP_H
#define POWERUP_H

#include "Entity.h"
#include "Board.h"
#include <SDL.h>


class PowerUp : public Entity
{
public:
    PowerUp(LTexture*,Board*,Point);
    enum POWERUP_TYPE {RESTORE_PAD,SHORTEN,ELONGATE,RESTORE_BALL,TURTLE,SPEEDBALL,BULLET,FIREBALL,STICKYBALL,MISSILE,EXTRA_LIFE,MULTIBALL,NUM_POWERUPS};
    ~PowerUp();
    void render(long int&, SDL_Renderer*);
    void move(List* = NULL);
    int getWhich();

private:
    int which;
    Board* gameBoard;
    SDL_Rect spriteClips[NUM_POWERUPS];
};

#endif // POWERUP_H
