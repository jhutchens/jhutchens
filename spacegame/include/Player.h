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

#include "Character.h"

#define NUM_WEAPONS 5//Number of possible weapons to acquire & use (besides lasers)

class Player : public Character
{
    public:
        /** Default constructor */

        //takes a renderer, texture and initial coordinates
        Player(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y, int=30, int=40);


        /** Default destructor */
        virtual ~Player();

        //overrides the Character process() to include additional processing
        void process();
        void increaseSpeed();//overrides to include fuel consumption
        void shoot();//shoot a laser beam
        int getFuel();//returns current fuel level
        int getShield();//returns current shield level
        int getEnergy();//returns current energy level



    protected:
        //the laser's ammo is based on energy levels; therefore it is not in the weapons[] array

        int shield,energy;//shield and energy levels
        int laserEnergy;//energy consumed when shooting laser
        int weapons[NUM_WEAPONS];//number/ammo of each weapon (where each weapons[x] corresponds to a different weapon)

        //amount of fuel left, steady loss of fuel from engine running, & fuel used each frame for motion
        int fuel,fuelLoss,fuelConsumed;

        bool hasMap;//has the player acquired a map? (default is false)



        void setFuelLoss(int newFuelLoss);
        void setFuelConsumed(int newRate);
        void updateStocks();


    private:
};

#endif // PLAYER_H
