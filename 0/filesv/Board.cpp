#include "Board.h"

Board::Board(LTexture* image,Point pos):Entity(image,pos)
{
    SCREEN_HEIGHT=0;
    SCREEN_WIDTH=0;
    // rows=0;
    //s cols=0;
    //setting clips of boundary walls (the 4 boxes at the bottom right corner of the sprite sheet)
    spriteClips[0].x = 267;
    spriteClips[0].y = 253;
    spriteClips[0].w = 30;
    spriteClips[0].h = 30;

    spriteClips[1].x = 297;
    spriteClips[1].y =  253;
    spriteClips[1].w = 30;
    spriteClips[1].h = 30;

    spriteClips[2].x = 267;
    spriteClips[2].y =  283;
    spriteClips[2].w =  30;
    spriteClips[2].h =  30;

    spriteClips[3].x =  297;
    spriteClips[3].y =  283;
    spriteClips[3].w =  30;
    spriteClips[3].h =  30;

    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;

    gSpriteSheetTexture=image;
}

Board::~Board()
{
    //dtor
}
void Board::render(long int& frame, SDL_Renderer* gRenderer)
{
    int sprite=0;
    //Rendering top stripe
    for (int i=width/2; i<SCREEN_WIDTH - width; i+=height)
    {
        spriteSheetTexture->render(i,3*height,&spriteClips[sprite%NUM_BOARD_FRAMES],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }
    //Rendering left strip
    for (int i=3*height; i<SCREEN_HEIGHT; i+=height)
    {
        spriteSheetTexture->render(0,i,&spriteClips[sprite%NUM_BOARD_FRAMES],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }
    //Rendering right stripe
    sprite=1;
    for (int i=3*height; i<SCREEN_HEIGHT; i+=height)
    {
        spriteSheetTexture->render(SCREEN_WIDTH - height,i,&spriteClips[sprite%NUM_BOARD_FRAMES],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    //comment to hide bounding rectangle
    SDL_RenderDrawRect(gRenderer,&bounds);
}
void Board::setDimensions(int SCREEN_WIDTH,int SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH=SCREEN_WIDTH;
    this->SCREEN_HEIGHT=SCREEN_HEIGHT;
    bounds.x= width;
    bounds.y = 4*height;
    bounds.w= SCREEN_WIDTH-2*width;
    bounds.h=SCREEN_HEIGHT-4*height;
}
