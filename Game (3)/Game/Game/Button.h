#ifndef BUTTON_H
#define BUTTON_H

#include <map>
#include "Entity.h"
#include "Text.h"
#include "SDL.h"

class Button : public Entity
{
public:
    /** Default constructor */
    Button(LTexture*,Point pos = Point());
    /** Default destructor */
    virtual ~Button();
    void render(long int&, SDL_Renderer*);
    void setRect(SDL_Rect&);
    void setPosition(int x, int y);
    SDL_Rect buttonRects[2];
    int State = 0;
    Text* buttonText = NULL;

protected:

private:
    int x;
    int y;
};

#endif // BUTTON_H
