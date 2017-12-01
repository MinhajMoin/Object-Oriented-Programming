#include "InvisibleBrick.h"

InvisibleBrick::InvisibleBrick(LTexture* image,Board* gameBoard,Point pos):TwoHitBrick(image,gameBoard,pos)
{
    type=INVBRICK;
}
void InvisibleBrick::render(long int& frame, SDL_Renderer* gRenderer)
{
    // std::cout << "TWOHIT" << std::endl;

    static int delay=0;
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    //comment to hide bounding rectangle
    //SDL_RenderDrawRect(gRenderer,&bounds);
    if(alive)
    {
        //std::cout << "LOL\n";
        if(brickDamage==0)//if brick hasn't been hit, won't be rendered even though it is alive, hence inv brick
        {
            return;
        }
        else if(brickDamage==1)//first frame (intact brick) will be rendered after first hit, hence brck will reveal after first collision
        {
            //std::cout << "FRAME1" << std::endl;
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
        }
        if(expFrame==3) return;
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_NONE, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks)
        }
    }

}
