/**
 * @authors: Zach DeCook, Jon Hutchens
 *
 *
 */
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
#include "Player.h"
#include "GameApp.h"

using namespace std;

int main( int argc, char* args[] )
{
	GameApp shipgame;
	shipgame.start();
	return 0;//terminate
}//end main
