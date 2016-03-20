#include "Player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


Player::Player(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y):Character(renderer,texture,x,y)
{
    //constructor
    shield=0;
    energy=100;
    for(int i=0;i<sizeof(weapons);i++){
        weapons[i]=0;//initialize all special weapons to have zero ammo
    }
    fuel=100;
    hasMap=false;
}

Player::~Player()
{
    //destructor
}
