#include "SteelBrick.h"

SteelBrick::SteelBrick(LTexture* image,Point pos):Brick(image,pos)
{
    brickHealth=10;
    color=GRAY;
}

void SteelBrick::render(long int& frame, SDL_Renderer* gRenderer)
{
    //std::cout << "ONEHIT" << std::endl;
    static int delay=0;
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    // std::cout << expFrame << std::endl;
    //comment to hide bounding rectangle
    //SDL_RenderDrawRect(gRenderer,&bounds);
    if(alive)
    {
        spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][FRAME0],0.0, NULL, SDL_FLIP_NONE, gRenderer);
    }
    if(!alive)
    {
        if(delay%5==0)
        {
            if(expFrame++ > 2)
            {
                expFrame=3;
            }
            //expFrame++;
        }
        if(expFrame==3) return;
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_VERTICAL, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks)
        }
    }
}

