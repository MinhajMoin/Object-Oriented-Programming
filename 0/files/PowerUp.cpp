#include "PowerUp.h"

PowerUp::PowerUp(LTexture* texture, Board* gameBoard,Point pos):Entity(texture,pos),gameBoard(gameBoard)
{
    alive = true;
    int x = 1;
    int y = 249;
    width = 25;
    height = 26;
    int i = 0;
    for (; i < 3; i++)
    {
        spriteClips[i] = {x,y,width,height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < 6; i++)
    {
        spriteClips[i] = {x,y,width,height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < 9; i++)
    {
        spriteClips[i] = {x,y,width,height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < NUM_POWERUPS; i++)
    {
        spriteClips[i] = {x,y,width,height};
        y += height;
    }

    type = POWERUP;
    which = (rand() % 12);
    dx = 0;
    dy = 1;
    speed = 3;

    setBounds();
}

PowerUp::~PowerUp()
{
    //dtor
}
void PowerUp::render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    //SDL_RenderDrawRect(gRenderer,&bounds);
    spriteSheetTexture->render(pos.x,pos.y,&spriteClips[which],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void PowerUp::move(List*)
{
    if (!(pos.y > (gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f + 80))
    {
        pos.y += speed;
        setBounds();
    }
    else
    {
        alive = false;
    }
}

int PowerUp::getWhich()
{
    return which;
}



