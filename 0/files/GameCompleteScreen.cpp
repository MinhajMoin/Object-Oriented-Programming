#include "GameCompleteScreen.h"

GameCompleteScreen::GameCompleteScreen(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[QUIT].buttonText->setText("QUIT");
    buttons[NEXT].buttonText->setText("Next");
    heading = new Text("LEVEL COMPLETE",image , pos);
    heading->setSize(0.8);
    heading->color = 1;

//    SDL_SetTextureBlendMode(backGround, SDL_BLENDMODE_BLEND);
//    SDL_SetTextureAlphaMod(backGround,100);
//    SDL_SetRenderTarget(ren, backGround);
}

GameCompleteScreen::~GameCompleteScreen()
{
    //dtor
}

void GameCompleteScreen::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    Menu::setDimensions(_SCREEN_WIDTH,_SCREEN_HEIGHT);
    heading->setPosition(_SCREEN_WIDTH/2,_SCREEN_HEIGHT/3);
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setSize(0.6);
        buttons[i].setPosition(_SCREEN_WIDTH/2 - buttons[i].getWidth()/2, 3*(_SCREEN_HEIGHT/5)+ i*(buttons[i].getHeight() + 10));
    }
}

void GameCompleteScreen::render(long int& frame,SDL_Renderer* gRenderer)
{
    auxtexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(gRenderer, auxtexture);
    //render what we want
    SDL_SetRenderDrawColor(gRenderer,0,0,0,150);
    SDL_RenderFillRect(gRenderer,&menuSprite);

    //change the target back to the default and then render the aux

    SDL_SetRenderTarget(gRenderer, NULL); //NULL SETS TO DEFAULT
    SDL_RenderCopy(gRenderer, auxtexture, NULL, &menuSprite);
    this->bounds = {width/4,height/4,menuSprite.w,menuSprite.h};
    //spriteSheetTexture->render(width/4,height/4,&menuSprite,0.0,NULL,SDL_FLIP_NONE,gRenderer,0.5);
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].render(frame,gRenderer);
    }
    SDL_DestroyTexture(auxtexture);
    heading->render(frame,gRenderer);
}

void GameCompleteScreen::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
        case NEXT:
        {
            alive = false;
            option = -1;
            proceed = 0;
            break;
        }
        case QUIT:
        {
            alive = false;
            mainMenu->setAlive(true);
            option = -1;
            proceed = -1;
            break;
        }
    }
}


