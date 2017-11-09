#include "ThreeHitBrick.h"

ThreeHitBrick::ThreeHitBrick(LTexture* image,Point pos):Brick(image,pos)
{
    brickHealth=3;
}

void ThreeHitBrick::render(long int& frame, SDL_Renderer* gRenderer)
{
    // std::cout << "TWOHIT" << std::endl;

    static int delay=0;
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    //comment to hide bounding rectangle
    //SDL_RenderDrawRect(gRenderer,&bounds);
    if(alive)
    {
        //std::cout << "LOL\n";
        if(brickDamage==0)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][FRAME0],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else if(brickDamage==1)
        {
            //std::cout << "FRAME1" << std::endl;
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][FRAME1],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else if(brickDamage==2)
        {
            //std::cout << "FRAME1" << std::endl;
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][FRAME2],0.0, NULL, SDL_FLIP_NONE, gRenderer);
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
        }
        if(expFrame==3) return;
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_NONE, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks)
        }
    }
}
