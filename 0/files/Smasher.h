#ifndef SMASHER_H_INCLUDED
#define SMASHER_H_INCLUDED
#include "Entity.h"
#include "Paddle.h"
#include "Board.h"


class Smasher : public Entity
{
public:
    Smasher(LTexture*, Board*, Paddle*);
    virtual ~Smasher();
    enum EXPLODING_FRAMES {START, POWERUP1, POWERUP2, BLOW, POWERDOWN1, POWERDOWN2, FINISH, NUM_EXPLODING_FRAMES};
    virtual void render(long int&, SDL_Renderer*)=0;
    bool isSmashed();
    bool isFinished();
    virtual void move(List* = NULL)=0;

protected:
    SDL_Rect expSpriteClips[NUM_EXPLODING_FRAMES];
    bool smashed;
    bool finished;
    Board* gameBoard;
    int offsetX;
    int offsetY;
    Paddle* paddle;
};


#endif // SMASHER_H_INCLUDED
