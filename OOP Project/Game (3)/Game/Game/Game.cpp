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

        //Create window
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
        gameLoop(); //instead of going into the gameloop directly, go to the menu
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
            || !bgTexture.loadFromFile("Images/background5.png",gRenderer,0,255,255)
            || !mainMenuTexture.loadFromFile("Images/Menu 1.png",gRenderer,255,0,0)
            || !splashScreen.loadFromFile("Images/Splash.jpg",gRenderer,0,0,0)) //change this to the sprite sheet to be loaded
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

void Game::showSplash(long int& frame)
{
    SDL_Rect splashRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    splashScreen.setAlpha((frame*2)%256);
    splashScreen.render(0,0,&splashRect,0.0,NULL,SDL_FLIP_NONE,gRenderer);
}

void Game::hideSplash(long int& frame)
{
    SDL_Rect splashRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    splashScreen.setAlpha(255 -(frame*2)%256);
    splashScreen.render(0,0,&splashRect,0.0,NULL,SDL_FLIP_NONE,gRenderer);
}

void Game::Splash(long int& frame,int delay)
{

//        if ((float)(SDL_GetTicks()-firstTick)/1000 == delay+2.55) break;
}

void Game::gameLoop()
{
    bool splashLife = true;
    mainMenu = new MainMenu(&mainMenuTexture);
    mainMenu->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    //setting rect for background
    SDL_Rect bgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    gameBoard=new Board(&gSpriteSheetTexture);
    gameBoard->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    levelLoader();
    //levelLoader("Levels/lev2.txt");
    Paddle pad(&gSpriteSheetTexture,gameBoard);
    Ball ball(&gSpriteSheetTexture,gameBoard);
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
    Uint32 sd = SDL_GetTicks();
    long int frame=0;
    long int testframe =0;
    bool ballMoving = false;
    while( !quit )                          //Game loop
    {
        if (splashLife) Splash(frame,3); splashLife =false;
        while( SDL_PollEvent( &e ) != 0  && !splashLife)   //Handle events on queue
        {
            if (mainMenu->getAlive()) mainMenu->handleEvents(e);
            ball.handleEvents(e);
            //User requests quit
            if( e.type == SDL_QUIT || mainMenu->getOption() == MainMenu::QUIT )
            {
                quit = true;
            }
            if (mainMenu->getOption() == MainMenu::PLAY)
            {
                mainMenu->alive = false;
            }
        }

        {
            long int splashFrame = 0;
            Uint32 firstTick = SDL_GetTicks();
            bool show = true;
            if (show)
            {
                showSplash(frame);
            }
            if ((SDL_GetTicks()-firstTick)/1000 == delay)
            {
                show = false;
            }
            if (!show)
            {
                hideSplash(frame);
            }
        }

        frame++;
        //string title = to_string(frame);
        SDL_SetWindowTitle(gWindow,"BRICRUMBLE CHUSS");
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
        SDL_RenderClear( gRenderer );

        if (!mainMenu->getAlive())
        {
            //Rendering background
            bgTexture.render(0,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
            //worldEnt.clean();
            bgTexture.render(0,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
            //Rendering Game Board (boundaries)
            gameBoard->render(frame,gRenderer);
            worldEnt.render(frame,gRenderer);

            if (!ballMoving)  ballMoving=ball.startMove(e);
            else ball.move(90);
            ball.render(frame,gRenderer);

            pad.render(frame,gRenderer);
            pad.setMouseX(e);
            //copy.render(frame,gRenderer);


            /* BLOCK FOR SEEING DESTROY ANIMATION FOR BRICKS*/
            if(worldEnt.size()>0)
            {
                //CRASHING AT
                //worldEnt.end->ent->incrementDmg();


                //simulating a hit
                //worldEnt.end->ent->incrementDmg(); //IMP CONDITION
                worldEnt.start->ent->incrementDmg(); //IMP CONDITION
                worldEnt.move();//for moving objects that will move
                //or
                //simulating death
                //worldEnt.start->ent->setAlive(0);
            }
            if(frame%60==0)
            {
                worldEnt.clean();//bricks will get deallocaated after every 60 frames
                std::cout << worldEnt.size() << std::endl;
            }
        }
        else if (!splashLife)
        {
            mainMenu->render(frame,gRenderer);
//            cout << frame-testframe << ' ';
//            if ((frame*2)%256 == 254) cout << endl;
//            showSplash(frame);
//            cout <<frame << ' ' << (SDL_GetTicks() - sd)/1000  << ' '  << frame/(SDL_GetTicks() - sd)/1000 <<' '<< (frame*2)%256<< '\r';
//            if ((frame*2)%256 == 254)testframe = frame;
        }

        SDL_RenderPresent(gRenderer);
    }
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
