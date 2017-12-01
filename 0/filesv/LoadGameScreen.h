#ifndef LoadGameSCREEN_H
#define LoadGameSCREEN_H

#include "Menu.h"
#include <vector>
#include "Button.h"


class LoadGameScreen : public Menu
{
public:
    /** Default constructor */
    LoadGameScreen(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~LoadGameScreen() {};
    enum Buttons {STATE1,STATE2,STATE3,CANCEL,BUTTONSMAX};
    enum modes{SAVE,LOAD};
    void handleEvents(SDL_Event& e);
    Menu* parentMenu;
    int mode = -1;

protected:

private:

};

#endif // LoadGameSCREEN_H
