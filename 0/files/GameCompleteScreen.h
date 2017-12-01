#ifndef GAMECOMPLETESCREEN_H
#define GAMECOMPLETESCREEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "Menu.h"
#include "Text.h"

class GameCompleteScreen : public Menu
{
    public:
        /** Default constructor */
        GameCompleteScreen(LTexture* image,Point pos = Point());
        /** Default destructor */
        virtual ~GameCompleteScreen();
        void render(long int& frame,SDL_Renderer* gRenderer);
        void handleEvents(SDL_Event& e);
        void setDimensions(int SCREEN_WIDTH,int SCREEN_HEIGHT);
        enum Buttons{NEXT,QUIT,BUTTONSMAX};
        int proceed = -1;
        Menu* mainMenu = NULL;
        SDL_Texture* auxtexture = NULL;

    protected:
    private:
        Text* heading;
};

#endif // GAMECOMPLETESCREEN_H
