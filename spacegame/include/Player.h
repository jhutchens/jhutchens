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

#define NUM_WEAPONS 5//Number of possible weapons to acquire & use (besides lasers)

class Player : public Character
{
    public:
        /** Default constructor */

        //takes a renderer, texture and initial coordinates
        Player(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y);


        /** Default destructor */
        virtual ~Player();

    protected:
        //the laser's ammo is based on energy levels; therefore it is not in the weapons[] array

        int shield,energy;//shield and energy levels
        int weapons[NUM_WEAPONS];//number/ammo of each weapon (where each weapons[x] corresponds to a different weapon)
        double fuel;//amount of fuel left
        bool hasMap;//has the player acquired a map? (default is false)


    private:
};

#endif // PLAYER_H
