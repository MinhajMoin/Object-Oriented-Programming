#include "Game.h"

Game::Game()
{
    static bool seeded=false;
    if(!seeded)
    {
        srand(time(NULL));
    }
    init();
}

void Game::loadMenus()
{
    pauseMenu = new PauseMenu(&pauseMenuTexture);
    gameOver = new GameOver(&pauseMenuTexture);
    loadState = new LoadGameScreen(&mainMenuTexture);
    mainMenu = new MainMenu(&mainMenuTexture);
    splashScreen = new Screen(&splash);
    levelComplete = new GameCompleteScreen(&pauseMenuTexture);


    gameGUI = new GUI(&mainMenuTexture);

    Menus.push_back(pauseMenu);
    Menus.push_back(mainMenu);
    Menus.push_back(gameOver);
    Menus.push_back(loadState);

    Screens.push_back(splashScreen);

    for (int i=0;i<Menus.size();i++)
    {
        Menus[i]->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    }
    for (int i=0;i<Screens.size();i++)
    {
        Screens[i]->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    }

    levelComplete->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);

    gameGUI->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    gameOver->mainMenu = mainMenu;
    pauseMenu->mMenu = mainMenu;
    loadState->parentMenu = mainMenu;
    mainMenu->loadState = loadState;
    pauseMenu->saveState = loadState;
    levelComplete->mainMenu = mainMenu;

    pauseMenu->setAlive(false);
    loadState->setAlive(false);
    gameOver->setAlive(false);
    splashScreen->setAlive(true);
}

Game::~Game()
{
    //dtor
}

bool Game::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //DISABLE CURSOR BEING SHOWN
        //SDL_ShowCursor(SDL_DISABLE);
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create windows
        gWindow = SDL_CreateWindow( "BRICRUMBLE!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    if(loadMedia())
    {
        loadMenus();
        gameLoop();  //instead of going into the gameloop directly, go to the menu
        //testLoop();
    }

    return success;
}

bool Game::loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "Images/spritesheetnew.png", gRenderer,0,255,255  )
            || !bgTexture.loadFromFile("Images/bgday.png",gRenderer,0,255,255)
            || !mainMenuTexture.loadFromFile("Images/Menu 1.png",gRenderer,255,0,0)
            || !pauseMenuTexture.loadFromFile("Images/Menu 1.png",gRenderer,255,0,0)
            || !splash.loadFromFile("Images/Splash.png",gRenderer,0,0,0))
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    //std::cout << gSpriteSheetTexture.getWidth() << " " << bgTexture.getWidth() << std :: endl;
    return success;
}

void Game::close()
{
    //Free loaded images
    gSpriteSheetTexture.free();
    bgTexture.free();
    mainMenuTexture.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    gameBoard = NULL;
    mainMenu = NULL;

    gameGUI = NULL;
    pauseMenu = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

void Game::gameLoop()
{


    //Variable for controlling backgournd color modulation
    int r,g,b;
    r=255;
    g=255;
    b=255;

    GameCompleteScreen* comp = new GameCompleteScreen(&pauseMenuTexture);
    comp->setDimensions(1024,768);
    //setting rect for background
    SDL_Rect bgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};


    gameBoard=new Board(&gSpriteSheetTexture);
    gameBoard->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);

    //levelLoader("Levels/lev10.txt");
    Paddle* pad;
    Ball* ball;
    pad=new Paddle(&gSpriteSheetTexture,gameBoard);//,NULL);
    ball=new Ball(&gSpriteSheetTexture,gameBoard,pad);
    pad->setBall(ball);

    playerEnt.append(pad);
    playerEnt.append(ball);
    playerEnt.resetEntities();
    worldEnt.empty();
    levelLoader();

    SDL_Event e;
    bool quit=false;
    long int frame=0;
    float scrollingOffset = 0;
    bool mouseUp = false;
    bool mouseDown = false;

    bool pause;

    bool dayChange=0;
    Uint32 firstTick = SDL_GetTicks();
    bool gamerun = false;
    static bool day = 1;//start off as day bground
    while( !quit )                          //Game loop
    {
        while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
        {
            int menuAlive = 0;
            for (int i=0;i<Menus.size();i++)
            {
                if (Menus[i]->getAlive())
                {
                    Menus[i]->handleEvents(e);
                    menuAlive++;
                    break;
                }
            }
            if (menuAlive==0 && !splashScreen->getAlive()) {gamerun = true;}
            if (levelComplete->getAlive()) levelComplete->handleEvents(e);

            //User requests quit
            if( e.type == SDL_QUIT || mainMenu->getOption() == MainMenu::QUIT )
            {
                quit = true;
            }

            if (gamerun)
            {
                if (e.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT && !mainMenu->getAlive())
                    {
                        if(ball->isStuck())
                        {
                            ball->setStick(false);
                        }
                    }
                }
            }
            if (pauseMenu->resetGame || gameOver->resetGame)
            {
                playerEnt.resetEntities();
                worldEnt.empty();
                pauseMenu->resetGame = gameOver->resetGame = false;
                levelLoader("Levels/lev2.txt");
                firstTick = SDL_GetTicks();
            }
            if (gamerun)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_1:
                        ball->setBallType(1);
                        break;
                    case SDLK_2:
                        ball->setBallType(2);
                        break;
                    case SDLK_3:
                        ball->setBallType(3);
                        break;
                    case SDLK_4:
                        ball->setBallType(0);
                        break;
                    case SDLK_5:
                        pad->fireUp();
                        break;
                    case SDLK_6:
                        pad->turtleDown();
                        break;
                    case SDLK_7:
                        pad->restoreMode();
                        break;
                    case SDLK_8:
                        pad->diminish();
                        break;
                    case SDLK_9:
                        pad->restoreSize();
                        break;
                    case SDLK_0:
                        pad->enlarge();
                        break;
                    case SDLK_ESCAPE:
                        pauseMenu->setAlive(true);
                        gamerun = false;
                        break;
                    }
                }
            }
            handleEvents(e, mouseUp, mouseDown);
            if (mouseUp == true && pad->getPaddleMode() == Paddle::FIRE)
            {
                Bullet* leftBullet = new Bullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::LEFT);
                Bullet* rightBullet = new Bullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::RIGHT);
                playerEnt.append(leftBullet);
                playerEnt.append(rightBullet);
            }
            mouseUp = false;
        }
        frame++;
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );    //Clear screen
        SDL_RenderClear( gRenderer );
        stringstream cc;
        cc << "BRICRUMBLE | Frame = " << frame;
        SDL_SetWindowTitle(gWindow,cc.str().c_str());
        bgTexture.setColor(r,g,b);
        if (splashScreen->getAlive()) splashScreen->render(frame,gRenderer);
        if (splashScreen->getAlive()) mainMenu->setAlive(true);

        if (lives<0)
        {
            gameOver->setAlive(true);
            lives = 5;
        }
        if (loadState->alive && !mainMenu->getAlive())
        {
            loadState->render(frame,gRenderer);
        }
        else if (gamerun)//!mainMenu->getAlive() && !splashScreen->getAlive() && !gameOver->getAlive() && !loadState->getAlive())
        {
            if (pauseMenu->getAlive())
            {
                pauseMenu->render(frame,gRenderer);
            }
            else
            {
                scrollingOffset-=0.5;
                if( scrollingOffset < -bgTexture.getWidth() )
                {
                    scrollingOffset = 0;
                }

                //BACKGROUND MOVING AND CHANGE FROM DAY TO NIGHT
                bgTexture.render(scrollingOffset,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
                bgTexture.render(scrollingOffset+bgTexture.getWidth(),0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
                int gameTimer=(SDL_GetTicks() - firstTick)/1000;//stores current game timer in sec
                if(gameTimer%DAYTIME==0 && gameTimer!=0)
                {
                    dayChange=1;
                }
                if(dayChange)
                {
                    if(r==128 && g==128)
                    {
                        gameGUI->toggleColor();
                    }
                    if(day)//change from day to night
                    {

                        if(r>0 && g>0)
                        {
                            r-=1;
                            g-=1;
                        }
                        else//day has been changed
                        {
                            dayChange=0;
                            day=0;
                        }

                    }
                    else
                    {
                        if(r<255 && g<255)
                        {
                            r+=1;
                            g+=1;
                        }
                        else//day has been changed
                        {
                            dayChange=0;
                            day=1;
                        }

                    }
                }
                //Collision checking and handling
                collisionHandler(&playerEnt,&worldEnt);
                collisionHandler(ball,pad);

                //Rendering Game Board (boundaries)
                gameBoard->render(frame,gRenderer);
                worldEnt.render(frame,gRenderer);
                playerEnt.render(frame,gRenderer);
                if (!pause) playerEnt.move();
                // cout << "FIRSTTICK: " << (SDL_GetTicks() - firstTick)/1000 << endl;
                gameGUI->setLives(lives);
                gameGUI->setTime(firstTick);
                gameGUI->setScore(score);
                gameGUI->render(frame,gRenderer);

                // BLOCK FOR SEEING DESTROY ANIMATION FOR BRICKS
                if(worldEnt.size()>0)
                {
                    if (!pause) worldEnt.move();//for moving objects that will move
                }
                if(frame%60==0)
                {
                    worldEnt.clean();//bricks will get deallocaated after every 60 frames
                    playerEnt.clean();
//                    cout << "BRICK COUNT: " << worldEnt.getBrickCount() << endl;
                }

                    cout << "proceed = " << levelComplete->proceed << endl;
                if (levelComplete->proceed == 0)
                {
                    pause = false;
                    worldEnt.empty();//force clean all bricks if any before loadin next level
                    while(playerEnt.size()>2)//remove any additional entities(such as bullets) from the list if any remain, keep only ball and pad
                    {
                        playerEnt.removeNodeAtInd(playerEnt.size() - 1);
                    }
                    playerEnt.resetEntities();
                    levelLoader();
                    levelComplete->proceed = -1;
                }
                if(worldEnt.getBrickCount()==0)
                {
                    levelComplete->setAlive(true);
                    pause = true;
                }
                ///RESET THE TIMER HERE, ADD BONUS SCORE DEPENDING UPON TIMER

            }
        }
        //else
        else if (!splashScreen->getAlive() && !loadState->getAlive() && mainMenu->getAlive())
        {
            mainMenu->render(frame,gRenderer);
        }
        if (pauseMenu->getAlive()) pauseMenu->render(frame,gRenderer);

        if (gameOver->getAlive()) {gameOver->render(frame,gRenderer);}

        if (levelComplete->getAlive())
        {
            levelComplete->render(frame,gRenderer);
        }

        SDL_RenderPresent(gRenderer);
    }
    delete gameBoard;
    close();
}
void Game::handleEvents(SDL_Event e, bool& mouseUp, bool& mouseDown)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        mouseDown = true;
    }
    if (e.type == SDL_MOUSEBUTTONUP && mouseDown)
    {
        mouseUp = true;
        mouseDown = false;
    }
}
void Game::levelLoader(string level)
{
    static int levelNum=1;
    stringstream stream;
    stream << "Levels/lev" << levelNum << ".txt";
    string filename;
    if (level=="") filename = stream.str();
    else filename = level;
    FileIO file;//by default uses LOAD_LEVEL mode of FileIO
    //generating generic filenames, of the form "Levels/levX.txt"
    if (file.openFile(filename) && file.checkFile())//if the file is opened successfully & checked for proper format, load it onto the board
    {
        file.handleFile(&worldEnt,gameBoard);
        levelNum++;
    }//file close handled in FileIO destructor
    else
    {
        cerr << "Error loading file " << filename << " in Game::levelLoader()" << endl;
        cout << "Loading default level" << endl;
        file.closeFile();
        file.openFile("Levels/default.txt");
        if(file.checkFile())
        {
            file.handleFile(&worldEnt,gameBoard);
            levelNum++;
        }
        else
        {
            cout << "Error loading default level file." << endl;
            exit(-1);
        }
    }
}

void Game::collisionHandler(Entity* ent1,Entity* ent2) //For handling ball-brick collisions and also ball-pad collisions
{

    //BALL BOARD COLLISIONS (DOWNWARDS)
    if (ent1->getType() == ent1->ENTITIES::BALL)
    {
        SDL_Rect ball=ent1->getBounds();
        SDL_Rect board=gameBoard->getBounds();
        if  (ball.y + ball.h + 10> board.y + board.h)
        {
            ent1->stickToPaddle();
            if (lives>=0) lives-=1;
        }
    }

    //BALL-BRICK COLLISIONS
    if (ent1->getType() == ent1->ENTITIES::BALL && ent2->getType() != ent1->ENTITIES::PADDLE && ent2->getType() != ent1->ENTITIES::POWERUP && ent2->getAlive()!=0)
    {

        SDL_Rect ball=ent1->getBounds();
        //Point ballCenter=Point(ent1->getPos().x + ent1->getWidth()/2,ent1->getPos().y + ent1->getHeight()/2);
        SDL_Rect brick=ent2->getBounds();

        SDL_Rect intersectRect;
        if (SDL_IntersectRect(&ball,&brick,&intersectRect))// && (brickCollisionGap > 2000 || prevEnt != ent1))//if there's a collision
        {
            //prevEnt = ent1;
//            cout << "Ball-brick collision." << endl;
            score+=25;
            //Generating a powerup if the brick had a probability
            int check_life = ent2->incrementDmg();//increase damage on the brick,collision has been detected,also store if brick would yield powerup
            if (check_life == 1)//brick has been killed
            {
                score+=50;
                if (ent2->getPower())
                {
                    Point powPos(ent2->getPos().x+ent2->getWidth()/2,ent2->getPos().y+ent2->getHeight()/2);
                    PowerUp* pow = new PowerUp(&gSpriteSheetTexture,gameBoard,powPos);
                    worldEnt.append(pow);
                }
            }
            if (intersectRect.w >= intersectRect.h)//TOP OR BOTTOM COLLISION
            {
                //if ball collides with brick from top, its dy has to be +ve
                ent1->setDir(ent1->getDX(),ent1->getDY()*-1);//reverse y dir of ball

                //IF COLLISION IS TOP, BALL Y HAS TO BE SMALLER THAN BRICK Y

                if(ent1->getPos().y<ent2->getPos().y)//TOP COLLISION
                {
                    ent1->setPosY(ent2->getPos().y - ent1->getHeight());
                }
                else // DOWN COLLISION
                {
                    ent1->setPosY(ent2->getPos().y + ent2->getHeight());
                }
            }
            else// if(intersectRect.w < intersectRect.h)//LEFT or RIGHT COLLISION
            {
                ent1->setDir(ent1->getDX()*-1,ent1->getDY());//reverse x dir of ball
                //IF COLLISION IS LEFT, BALL X HAS TO BE LESS THAN BRICK X
                if(ent1->getPos().x < ent2->getPos().x)//LEFT Collision
                {
                    ent1->setPosX(ent2->getPos().x - ent1->getWidth());
                }
                else//RIGHT COLLISION
                {
                    ent1->setPosX(ent2->getPos().x + ent2->getWidth());
                }
            }
            ent1->move();
        }
        else
        {
            return;
        }
    }
    //PADDLE POWERUP COLLISIONS
    if (ent1->getType() == ent1->ENTITIES::PADDLE && (ent2->getType() == ent1->ENTITIES::POWERUP))
    {
        SDL_Rect paddle=ent1->getBounds();
        SDL_Rect pow=ent2->getBounds();
        if(SDL_HasIntersection(&paddle,&pow))
        {
            score+=50;
//            cout << "Paddle PowerUp collision." << endl;
            ent2->setAlive(0);
            ent1->setPower(ent2);
            int ind = worldEnt.getEntInd(ent2);
            worldEnt.removeNodeAtInd(ind);
        }
        else
        {
            return;
        }
    }
    //BALL-PADDLE COLLISIONS
    if (ent1->getType() == ent1->ENTITIES::BALL && ent2->getType() == ent1->ENTITIES::PADDLE)// && paddleCollisionGap >= 5000)// && ent2->getAlive()!=0)
    {
        //cout << paddleCollisionGap << endl;
        //BALL Bounce angle is independent of the direction at which it hits the paddle
        SDL_Rect ball=ent1->getBounds();
        SDL_Rect paddle=ent2->getBounds();
        SDL_Rect intersectRect;

        if (SDL_IntersectRect(&ball,&paddle,&intersectRect))
        {
//            cout << "Ball-Paddle collision." << endl;
//            cout << paddleCollisionGap << endl;
            //   cout << intersectRect.x << ", " << intersectRect.y << ", " << intersectRect.w << ", " << intersectRect.h << ", " << endl;
            if(intersectRect.w > intersectRect.h)//TOP OR BOTTOM COLLISION
            {
                float ballMidX = ball.x +  ball.w/2;
                float padStartX =  paddle.x;
                float hitPosX = (ballMidX - padStartX)/paddle.w;
                float relativeDirX = hitPosX*4 - 2;
                float denominator = sqrt(pow(relativeDirX,2) + 1);
                ent1->setDir(relativeDirX/denominator, -1/denominator);
            }
            else//if(intersectRect.w <= intersectRect.h)
            {

                ent1->stickToPaddle();
                lives-=1;

            }
        }
        else
        {
            return;
        }
        //paddleCollisionGap = 0;
    }
    //BULLET BRICK COLLISIONS
    if (ent1->getType() == ent1->ENTITIES::BULLET && ent2->getType() != ent1->ENTITIES::PADDLE && ent2->getType() != ent1->ENTITIES::POWERUP && ent2->getType() != ent1->ENTITIES::BALL && ent2->getAlive()!=0 && ent1->getAlive()!=0)
    {
        SDL_Rect bullet=ent1->getBounds();
        SDL_Rect brick=ent2->getBounds();
        if (SDL_HasIntersection(&bullet,&brick))//if there's a collision
        {
            score+=25;
            ent2->setAlive(0);//bullet brick collision, kill both on impact
            ent1->setAlive(0);
            if (ent2->getPower())
            {
                Point powPos(ent2->getPos().x+ent2->getWidth()/2,ent2->getPos().y+ent2->getHeight()/2);
                PowerUp* pow = new PowerUp(&gSpriteSheetTexture,gameBoard,powPos);
                worldEnt.append(pow);
            }
        }
        else
        {
            return;
        }
    }

    //paddleCollisionGap++;
}

void Game::collisionHandler(Entity* ent1,List* worldEnt)
{
    Node* tmp=worldEnt->start;
    while(tmp)
    {
        collisionHandler(ent1,tmp->ent);
        tmp=tmp->next;
    }
}

void Game::collisionHandler(List* playerEnt,List* worldEnt)
{
    Node* tmp = playerEnt->start;
    while(tmp)
    {
        collisionHandler(tmp->ent, worldEnt);
        tmp=tmp->next;
    }
}
