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

#ifndef CHARACTER_H
#define CHARACTER_H
class Character
{
    public:
        /** Default constructor */
        Character(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y);//takes a texture and initial coordinates
        /** Default destructor */
        virtual ~Character();

        SDL_Texture *texture;
        SDL_Renderer *renderer;
        SDL_Rect rect;
        //SDL_Point center;

        void kill();//decrease health to zero
        void damage();//reduce the health by 1
        void setHealth(int newHealth);//set the health to newHealth
        void increaseSpeed();//increases character speed
        void steerLeft();//turn direction left
        void steerRight();//turn direction right

        void process();//processes all forces and current actions, calls updatePosition()
        void updatePosition();//set x,y position based on current direction and speed, uses friction()
        void render();//draw character to screen


    protected:
        bool isAlive;//is the character alive or dead?
        int health;//character's current health
        int x,y;//x,y position
        double direction;//facing which direction? (angle)
        float speed[2];//current x-speed (speed[0]) and y-speed (speed[1])
		float omega=0;

		void destroy();//destroys the character
        void friction();//resists forward movement and slows down character when not accelerating

    private:

};

#endif // CHARACTER_H
