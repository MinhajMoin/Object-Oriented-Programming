#ifndef MENU_H
#define MENU_H

#include "Entity.h"
#include "Button.h"
#include <vector>

class Menu : public Entity
{
    public:
        /** Default constructor */
        Menu(LTexture* image,Point pos = Point());
        /** Default destructor */
        virtual ~Menu();
        virtual void render(long int&,SDL_Renderer* gRenderer);
        virtual void setDimensions(int,int);
        virtual void handleEvents(SDL_Event& e);
        int getOption();
        void setOption(int opt);

    protected:
        vector <Button> buttons;
        int option;
        int SCREEN_HEIGHT, SCREEN_WIDTH;
        int MAXBUTTONS = 4;
        SDL_Rect menuSprite;
    private:
};

#endif // MENU_H
