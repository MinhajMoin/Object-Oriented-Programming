#ifndef PauseMenu_H
#define PauseMenu_H

#include <vector>
#include "Point.h"
#include "Button.h"
#include "LTexture.h"
#include "LoadGameScreen.h"
#include "MainMenu.h"

class PauseMenu : public Menu
{
public:
    /** Default constructor */
    PauseMenu(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~PauseMenu() {};
    enum Buttons {RESUME,SAVE,QUIT,BUTTONSMAX};
    void handleEvents(SDL_Event& e);
    MainMenu* mMenu = NULL;
    LoadGameScreen* saveState = NULL;
    bool resetGame = false;

protected:

private:
};

#endif // PauseMenu_H
