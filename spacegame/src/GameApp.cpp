/**
 * @authors: Zach DeCook, Jon Hutchens
 *
 *
 */
#include "Character.h"
#include "Player.h"
#include "GameApp.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const Uint8* gkeystates = SDL_GetKeyboardState(NULL);
struct Z_Key
{
	bool state;
	bool pstate;
	SDL_Scancode scanCode;
	Z_Key(SDL_Scancode code)
	{
		scanCode=code;
		pstate=gkeystates[scanCode];
		state=gkeystates[scanCode];
	}
	void update()
	{
		pstate=state;
		state=gkeystates[scanCode];
		//printf("%d, %d", scanCode, state);
	}
	bool newpress()
	{
		return (state&&!pstate);
	}
	bool held()
	{
		return state;
	}
	bool released()
	{
		return (!state&&pstate);
	}
};
Z_Key Z_up(SDL_SCANCODE_UP);
Z_Key Z_left(SDL_SCANCODE_LEFT);
Z_Key Z_right(SDL_SCANCODE_RIGHT);
Z_Key Z_space(SDL_SCANCODE_SPACE);

Z_Key Z_w(SDL_SCANCODE_W);
Z_Key Z_a(SDL_SCANCODE_A);
Z_Key Z_d(SDL_SCANCODE_D);
Z_Key Z_shift(SDL_SCANCODE_LSHIFT);



GameApp::GameApp(int numPlayers)
{

    //ctor

    //The window we'll be rendering to
    //gWindow = NULL;

    //The window renderer
    //gRenderer = NULL;

    //sheep = NULL;

    this->numPlayers=numPlayers;

    //Player player1;
    //Player player2;

    quit=false;//main loop exit flag

}

GameApp::~GameApp()
{
    //dtor
}



bool GameApp::init()
{
	/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
	 and may not be redistributed without written permission.*/
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	
	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}
	
	//Create window
	gWindow = SDL_CreateWindow( "Shipgame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	
	//Create vsynced renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	
	return true;
}

bool GameApp::createPlayers()
{
    player1 = new Player(*gRenderer,*sheep,100,200,43,44);
    player2 = new Player(*gRenderer,*sheep,300,100,43,44);
	missile = new Player(*gRenderer,*rocket,400,400,16,32);
    return true;//@todo return false if failed
}

void GameApp::close()
{
	delete player1;
	delete player2;
	delete missile;
	//Free loaded images
	SDL_DestroyTexture( sheep );
	SDL_DestroyTexture( rocket );

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void GameApp::start()
{
    //Start up SDL and create window
	if(!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		run();

	}//end else code block for main game functions

	//Free resources and close SDL
	close();
}

void GameApp::playGame()
{
    //While application is running
		while(!quit)
		{
			//SDL_PumpEvents();
			
			//Handle events on queue
			while(SDL_PollEvent(&e) != 0)//PollEvent implicitly calls PumpEvents
			{
				//User requests quit
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			Z_up.update();Z_left.update();Z_right.update();Z_space.update();
			Z_w.update();Z_a.update();Z_d.update();Z_shift.update();

			if(Z_up.held()){player1->increaseSpeed();printf("Fuel (P1): %d\t",player1->getFuel());}
			if(Z_w.held()){player2->increaseSpeed();printf("Fuel (P2): %d\n",player2->getFuel());}

			if(Z_a.held())player2->steerLeft();
			else if(Z_d.held())player2->steerRight();

			if(Z_right.held())player1->steerRight();
			else if(Z_left.held())player1->steerLeft();
			//if(Z_space.newpress()){do something here}

			if(Z_space.newpress()){player1->shoot();printf("Energy (P1): %d\t",player1->getEnergy());}
			if(Z_shift.newpress()){player2->shoot();printf("Energy (P2): %d\n",player2->getEnergy());}

			player1->process();
			player2->process();
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x44, 0xFF);
			SDL_RenderClear(gRenderer);

			player1->render();
			player2->render();
			missile->render();
			//Update screen
			SDL_RenderPresent(gRenderer);
			SDL_Delay(5);
		}//end game loop
}

void GameApp::run()
{
	loadedSurface = IMG_Load("res/arrow.png");
    sheep = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(sheep == NULL)
    {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        quit=true;
    }
    SDL_FreeSurface(loadedSurface);
	
	loadedSurface = IMG_Load("res/rightm.png");
	rocket = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if(sheep == NULL)
	{
		printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
		quit=true;
	}
	SDL_FreeSurface(loadedSurface);
	
	createPlayers();

    playGame();
}
