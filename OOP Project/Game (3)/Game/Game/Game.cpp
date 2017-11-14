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
//     UN COMMENT THIS
    if( !gSpriteSheetTexture.loadFromFile( "Images/spritesheet.png", gRenderer,0,255,255  )
            || !bgTexture.loadFromFile("Images/background.png",gRenderer,0,255,255)
            || !mainMenuTexture.loadFromFile("Images/Menu 1.png",gRenderer,255,0,0) ) //change this to the sprite sheet to be loaded
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
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

void Game::gameLoop()
{
    mainMenu = new MainMenu(&mainMenuTexture);
    mainMenu->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    //setting rect for background
    SDL_Rect bgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    gameBoard=new Board(&gSpriteSheetTexture);
    gameBoard->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    //levelLoader();
    levelLoader("Levels/lev2.txt");
    Paddle* pad=new Paddle(&gSpriteSheetTexture,gameBoard);
    Ball* ball=new Ball(&gSpriteSheetTexture,gameBoard,pad);
    playerEnt.append(pad);
    playerEnt.append(ball);
    //ball.stickToPaddle();
    //board loader
    //with different brick classes

    //List copy=worldEnt;
    //Nice pattern

    //for(int i=0;i<40;i++)
    // worldEnt.removeNodeAtInd(i);

    //worldEnt.empty();
    //worldEnt.removeNodeAtInd(0);
    //std::cout << num << std::endl;

    //KILLING A BRICK
    /*
    worldEnt.start->ent->setAlive(0);//works properly,
    worldEnt.start->ent->incrementDmg();
    worldEnt.clean();
    worldEnt.removeNodeAtInd(0);*/
    //worldEnt.empty();
    // worldEnt.start->ent->incrementDmg();
    //worldEnt.start->ent->incrementDmg();
    //worldEnt.start->ent->incrementDmg();
    //worldEnt.clean();
    //worldEnt.start->ent->incrementDmg();
    SDL_Event e;
    bool quit=false;
    long int frame=0;
    while( !quit )                          //Game loop
    {
        while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
        {
            if(mainMenu->getAlive())
                mainMenu->handleEvents(e);
            //User requests quit
            if( e.type == SDL_QUIT || mainMenu->getOption() == MainMenu::QUIT )
            {
                quit = true;
            }
            if (e.type==SDL_MOUSEBUTTONDOWN)// && !mainMenu->getAlive())
            {
                if (e.button.button == SDL_BUTTON_LEFT && !mainMenu->getAlive())
                    if(ball->isStuck())
                    {
                        ball->setStick(false);
                    }
            }
            if (mainMenu->getOption() == MainMenu::PLAY)
            {
                mainMenu->setAlive(false);
            }
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
                }
            }
        pad->handleEvents(e);
        }
        frame++;
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
        SDL_RenderClear( gRenderer );
        if (!mainMenu->getAlive())
        {
            //Rendering background
            //bgTexture.render(0,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
            //worldEnt.clean();
            bgTexture.render(0,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
            //Rendering Game Board (boundaries)
            gameBoard->render(frame,gRenderer);
            worldEnt.render(frame,gRenderer);
            playerEnt.render(frame,gRenderer);
            playerEnt.move();

            /* BLOCK FOR SEEING DESTROY ANIMATION FOR BRICKS*/
            if(worldEnt.size()>0)
            {
                //CRASHING AT
                //worldEnt.end->ent->incrementDmg();


                //simulating a hit
                //worldEnt.end->ent->incrementDmg(); //IMP CONDITION
                //worldEnt.start->ent->incrementDmg(); //IMP CONDITION
                worldEnt.move();//for moving objects that will move
                collisionHandler(ball,&worldEnt);
                collisionHandler(ball,pad);
                //or
                //simulating death
                //worldEnt.start->ent->setAlive(0);
            }
            if(frame%60==0)
            {
                worldEnt.clean();//bricks will get deallocaated after every 60 frames
                //std::cout << worldEnt.size() << std::endl;
            }
        }
        else
        {
            mainMenu->render(frame,gRenderer);
        }
        SDL_RenderPresent(gRenderer);
    }
    //paddle=NULL;ball=NULL;
    delete gameBoard;
    close();
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
//        cout << "Level successfully loaded from file " << filename << endl;
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

void Game::testLoop()///ONLY FOR TESTING, DELETE AFTER COMPLETION
{
    SDL_Rect bgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    gameBoard=new Board(&gSpriteSheetTexture);
    gameBoard->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_Event e;

    //LOADING LEVEL

    const int offsetX=2;//can be corrected for all resolutions with a little fitting, CORRECT THIS
    const int offsetY=2;

    Point spawnPoint(gameBoard->bounds.x + offsetX,gameBoard->bounds.y + offsetY);//offset of 2 for 1024 added to correct spawn points
    Brick* b = NULL;

    b=new OneHitBrick(&gSpriteSheetTexture,gameBoard,spawnPoint);
    worldEnt.append(b);
    spawnPoint++;

    b=new TwoHitBrick(&gSpriteSheetTexture,gameBoard,spawnPoint);
    worldEnt.append(b);
    spawnPoint++;


    b=new ThreeHitBrick(&gSpriteSheetTexture,gameBoard,spawnPoint);
    worldEnt.append(b);
    ++spawnPoint;

    b=new SteelBrick(&gSpriteSheetTexture,gameBoard,spawnPoint);
    worldEnt.append(b);


    //TEST HITS
    bool quit=false;
    long int frame=0;
    bool ballMoving = false;
    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT)
            {
                quit = true;
            }
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
            SDL_RenderClear( gRenderer );
            bgTexture.render(0,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
            //Rendering Game Board (boundaries)
            gameBoard->render(frame,gRenderer);

            worldEnt.render(frame,gRenderer);
            SDL_RenderPresent(gRenderer);

            if(frame++ % 15==0)
            {
                worldEnt.start->ent->incrementDmg();
                worldEnt.clean();
            }

        }
    }
}


void Game::collisionHandler(Entity* ent1,Entity* ent2) //For handling ball-brick collisions and also ball-pad collisions
{
    //BALL-BRICK COLLISIONS
    if (ent1->getType() == ent1->ENTITIES::BALL && ent2->getType() != ent1->ENTITIES::PADDLE && ent2->getAlive()!=0)
    {
        SDL_Rect ballCopy=ent1->getBounds();
        SDL_Rect brickCopy=ent2->getBounds();
        Rect ball=ballCopy;
        Rect brick=brickCopy;
        int collisionType=brick.isColliding(ball,ent1->getDX(),ent1->getDY());
        if (collisionType==ball.COLLISIONS::NONE)
        {
            return;
        }
        else //A Ball brick collision has been detected
        {
            ent2->incrementDmg();//increase damage on the brick
            //Setting bounce direction of the ball
            if(collisionType==ball.COLLISIONS::DOWN || collisionType==ball.COLLISIONS::TOP)
            {
                ent1->setDir(ent1->getDX(),ent1->getDY()*-1);
                ent1->move();
            }
            else if(collisionType==ball.COLLISIONS::LEFT || collisionType==ball.COLLISIONS::RIGHT)
            {
                ent1->setDir(ent1->getDX()*-1,ent1->getDY());
                ent1->move();
            }
        }
    }
    //BALL-PADDLE COLLISIONS
    else if (ent1->getType() == ent1->ENTITIES::BALL && ent2->getType() == ent1->ENTITIES::PADDLE)// && ent2->getAlive()!=0)
    {
        //BALL Bounce angle is independent of the direction at which it hits the paddle
        SDL_Rect ballCopy=ent1->getBounds();
        SDL_Rect paddleCopy=ent2->getBounds();
        Rect ball=ballCopy;
        Rect paddle=paddleCopy;
        int collisionType=paddle.isColliding(ball,ent1->getDX(),ent1->getDY());
        if(paddle.isColliding(ball,ent1->getDX(),ent1->getDY()))
        {
            if(collisionType==ball.COLLISIONS::TOP)
            {
                //float ballcenterX=ball.topLeft.x + ball
                int hitPosX = ball.botLeft.x + ball.width/2; //x position of the ball at which it hit the pad

                //hitPosX -= ent2->getWidth();
                if (hitPosX < 0)
                {
                    hitPosX = 0;
                }
                else if (hitPosX > ent2->getWidth())
                {
                    hitPosX = ent2->getWidth();
                }

                // Everything to the left of the center of the paddle is reflected to the left
                // while everything right of the center is reflected to the right
                hitPosX -= ent2->getWidth() / 2.0f;
                ent1->setDir(2.0f*(hitPosX/(ent2->getWidth()/2.0f)),-1);
            }
            else if (collisionType!=ball.COLLISIONS::NONE)
            {
                ent1->stickToPaddle();
            }
        }
    }
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
