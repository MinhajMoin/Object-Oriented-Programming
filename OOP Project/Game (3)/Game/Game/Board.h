#ifndef BOARD_H
#define BOARD_H

#include "Entity.h"


class Board : public Entity
{
public:
    Board(LTexture*,Point=Point());
    virtual ~Board();
    enum NUM_BOARD_FRAMES {NUM_BOARD_FRAMES = 4};
    SDL_Rect spriteClips[NUM_BOARD_FRAMES];
    void render(long int&, SDL_Renderer*);
    void setDimensions(int,int);
    friend class FileIO;
    friend class MobileBrick;
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    LTexture* gSpriteSheetTexture;
};

#endif // BOARD_H
