#include "Player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


Player::Player(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y, int w, int h):Character(renderer,texture,x,y,w,h)
{
    //constructor
    shield=0;//starting shield level
    energy=100;//starting energy level
    laserEnergy=2;//starting cost of shooting laser
    for(int i=0;i<sizeof(weapons);i++){
        weapons[i]=0;//initialize all special weapons to have zero ammo
    }
    fuel=10000;//starting amount of fuel
    fuelLoss=1;//constant fuel loss from engine running
    fuelConsumed=30;//only taken into account when accelerating

    //turnFuel=3;//fuel consumed for steering
    //^prolly not a good idea - so that players can still aim & shoot even if out of fuel

    hasMap=false;//no map to start
}

void Player::increaseSpeed()
{
    //can only accelerate if player has fuel left
    if(fuel<fuelConsumed)
    {
        fuel=0;
    }else
    {
        fuel-=fuelConsumed;
        Character::increaseSpeed();
    }

}

void Player::process()
{
    //update fuel & energy levels
    updateStocks();
    //printf("Player::process() function operating...\n");
    Character::process();//then run normal processing
}

void Player::updateStocks()
{
    if(fuel<fuelLoss)
    {
        fuel=0;
    }else
    {
        fuel-=fuelLoss;
    }
    //@todo update energy levels



}

void Player::shoot()
{
    if(laserEnergy<=energy)
    {
        //@todo shoot laser
        energy-=laserEnergy;
    }else
    {
        printf("Error: not enough energy to shoot laser! %d, %d\n",laserEnergy,energy);
    }


}

//sets the rate of steady fuel loss (should be very low - less than 3)
void Player::setFuelLoss(int newFuelLoss)
{
    if(newFuelLoss<0)
    {
        printf("Error: fuelLoss cannot be less than zero. \n");
    }else
    {
        fuelLoss=newFuelLoss;
    }

}

//sets the additional rate of fuel loss when accelerating (moderate to high)
void Player::setFuelConsumed(int newRate)
{
    if(newRate<0)
    {
        printf("Error: fuelConsumed cannot be less than zero. \n");
    }else
    {
        fuelConsumed=newRate;
    }
}

int Player::getFuel()
{
    return fuel;
}

int Player::getShield()
{
    return shield;
}

int Player::getEnergy()
{
    return energy;
}

Player::~Player()
{
    //destructor
}
