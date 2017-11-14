#ifndef SMASHER_H_INCLUDED
#define SMASHER_H_INCLUDED
#include "Entity.h"
#include "Board.h"

class Smasher : public Entity
{

public:
    Smasher(LTexture*, Board*, Point);
    virtual ~Smasher();
    enum EXPLODING_FRAMES {START, POWERUP1, POWERUP2, BLOW, POWERDOWN1, POWERDOWN2, FINISH, NUM_EXPLODING_FRAMES};
    virtual void render(long int&, SDL_Renderer*)=0;
    bool isSmashed();
    bool isFinished();
    virtual void move()=0;

protected:
    SDL_Rect expSpriteClips[NUM_EXPLODING_FRAMES];
    bool smashed;
    bool finished;
    Board* gameBoard;
    int offsetX;
    int offsetY;
};


#endif // SMASHER_H_INCLUDED
