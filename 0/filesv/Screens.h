#ifndef SCREENS_H
#define SCREENS_H

#include "LTexture.h"

class Screen
{
    public:
        /** Default constructor */
        Screen(LTexture* texture);
        bool ScreenIn(long int& frame,SDL_Renderer* gRenderer);
        bool ScreenOut(long int& frame,SDL_Renderer* gRenderer);
        void ScreenStay(long int& frame,SDL_Renderer* gRenderer);
        void render(long int& frame,SDL_Renderer* gRenderer,int delay=1);
        bool getAlive();
        void setAlive(bool isAlive);
        void setDimensions(int width,int height);
        /** Default destructor */
        virtual ~Screen();

    protected:
        LTexture* screenTexture;
        int SCREEN_WIDTH = 1024;
        int SCREEN_HEIGHT = 768;
        bool show;
        bool hide;
        bool stay;
        bool alive;
        Uint32 splTick = 0;

    private:
        SDL_Rect imageRect;
        SDL_Rect outputRect;
};

#endif // SCREENS_H
