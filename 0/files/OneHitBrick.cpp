#include "OneHitBrick.h"

OneHitBrick::OneHitBrick(LTexture* image,Board* gameBoard,Point pos):Brick(image,gameBoard,pos)
{
    brickHealth=1;
    type=ONEHITBRICK;
}

void OneHitBrick::render(long int& frame, SDL_Renderer* gRenderer)
{
    //std::cout << "ONEHIT" << std::endl;
    static int delay=0;
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    // std::cout << expFrame << std::endl;
    //comment to hide bounding rectangle
    if(alive)
    {
        if(brickDamage==0)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][FRAME0],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else
        {
            alive=0;
        }
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
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_NONE, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks)
        }
    }
    // SDL_RenderDrawRect(gRenderer,&bounds);
}



