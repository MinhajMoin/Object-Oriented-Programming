#ifndef TEXT_H
#define TEXT_H
#include <map>
#include "Entity.h"
#include "SDL.h"

using namespace std;

class Text:public Entity
{
public:
    // Default constructor
    Text(string text,LTexture*,Point pos = Point());
    // Default destructor
    virtual ~Text();
    // Copy constructor
    Text(const Text& other);
    void render(long int&,SDL_Renderer* gRenderer);
    void setSize(float tSize);
    void handleEvents(SDL_Event& e);
    void setPosition(float x, float y);
    void setText(string str);
    int color;
protected:

private:
    map<char,SDL_Rect> Characters;
    float textSize = 1;
    int SCREEN_WIDTH,SCREEN_HEIGHT;
    string text;
};

#endif // TEXT_H
