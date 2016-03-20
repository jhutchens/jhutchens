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

#ifndef PLAYER_H
#define PLAYER_H

#include <Character.h>


class Player : public Character
{
    public:
        /** Default constructor */

        //takes a renderer, texture and initial coordinates
        Player(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y);


        /** Default destructor */
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_H
