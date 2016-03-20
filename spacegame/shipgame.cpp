/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "Character.h"



using namespace std;

//Screen dimension constants
/*const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;*/

const Uint8* gkeystates = SDL_GetKeyboardState(NULL);
SDL_Texture* sheep = NULL;

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
		printf("%d, %d", scanCode, state);
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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


bool init()
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
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
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
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


void close()
{
	//Free loaded images
	SDL_DestroyTexture( sheep );

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if(!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Flip type
			SDL_Surface* loadedSurface = IMG_Load("res/arrow.png");

			sheep = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if(sheep == NULL)
			{
				printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			}
			SDL_FreeSurface(loadedSurface);

			Character player1(*gRenderer,*sheep,100,100);
			Character player2(*gRenderer,*sheep,100,100);


			//While application is running
			while(!quit)
			{
				SDL_PumpEvents();
				Z_up.update();Z_left.update();Z_right.update();Z_space.update();
				Z_w.update();Z_a.update();Z_d.update();Z_shift.update();
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				if(Z_up.held())
				{
					/*sped[0]+=.25*sin(degrees *(3.14/180));
					sped[1]-=.25*cos(degrees *(3.14/180));//modify the speed vector
					 */
					player1.increaseSpeed();
				}
				if(Z_w.held())player2.increaseSpeed();
				if(Z_a.held())player2.steerLeft();
				else if(Z_d.held())player2.steerRight();

				if(Z_right.held())player1.steerRight();
				else if(Z_left.held())player1.steerLeft();
				//if(Z_space.newpress()){do something here}

				player1.updatePosition();
				player2.updatePosition();
					//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x44, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_Point center;
				center.x=21;
				center.y=20;

				//Render arrow
				//gArrowTexture.render( shipx%SCREEN_WIDTH, shipy%SCREEN_HEIGHT, NULL, degrees, &center, flipType );
				player1.render();
				player2.render();
				//Update screen
				SDL_RenderPresent(gRenderer);
				SDL_Delay(5);
			}//end game loop

	}//end init() code block

	//Free resources and close SDL
	close();

	return 0;//terminate
}

