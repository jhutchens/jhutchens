/**
 * @authors: Zach DeCook, Jon Hutchens
 *
 *
 */

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

#ifndef GAMEAPP_H
#define GAMEAPP_H


class GameApp
{
    public:
        /** Default constructor */
        GameApp(int numPlayers);
        /** Default destructor */
        virtual ~GameApp();




        //starts the game; calls the init, run, & close functions
        void start();

        //how many ships?
        int numPlayers;

        Player* player1;
        Player* player2;

bool init();

    protected:

        //Starts up SDL and creates window; calls createPlayers


        //initializes player creation
        bool createPlayers();

        //Frees media and shuts down SDL
        void close();

        //runs the game loop
        void run();

        void playGame();


        //The window we'll be rendering to
        SDL_Window* gWindow = NULL;

        //The window renderer
        SDL_Renderer* gRenderer = NULL;

        SDL_Texture* sheep = NULL;
        SDL_Event e;//event handler

        //Flip type
        SDL_Surface* loadedSurface = IMG_Load("res/arrow.png");

        bool quit;

    private:
};

#endif // GAMEAPP_H
