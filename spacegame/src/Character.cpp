/**
 * @authors: Zach DeCook, Jon Hutchens
 *
 *
 */

#include "Character.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Character::Character(SDL_Renderer &renderer,SDL_Texture &texture,int x,int y)
{
    //constructor
    this->renderer=&renderer;
    this->texture=&texture;
    this->x=x;
    this->y=y;
	px=x;
	py=y;
    this->rect.x=this->x;
    this->rect.y=this->y;
    this->rect.w=30;
    this->rect.h=40;
    isAlive=true;
    health=10;
	omega=0;


    //center.x=5;
    //center.y=10;

    direction=0;
    speed[0]=0;
    speed[1]=0;

}

void Character::kill()
{
    this->setHealth(0);
}

void Character::damage()
{
    this->setHealth(this->health-1);
}

void Character::setHealth(int newHealth)
{
    if(newHealth<0)
    {
        printf("Error: Health cannot be less than zero.\n");
    }else if(newHealth==0)
    {
        this->health=newHealth;
        this->isAlive=false;
        this->destroy();
    }else
    {
        this->health=newHealth;
    }
}

void Character::increaseSpeed()
{
    //modify the speed vector
    this->speed[0]+=.25*sin(this->direction *(3.14/180));
    this->speed[1]-=.25*cos(this->direction *(3.14/180));
}

void Character::steerLeft()
{
    this->omega= -3;
}

void Character::steerRight()
{
    this->omega=  3;
}

void Character::process()
{
    //process actions & other items
    this->updatePosition();
}

void Character::updatePosition()
{
    this->friction();
    px+=this->speed[0];
    py+=this->speed[1];
	rect.x = px;
	rect.y = py;

	direction+= omega;
}

void Character::render()
{
	//printf("To renderer %d, we send texture %d\n",renderer,texture);
    //printf("Rendering...umm, %d, %d [%d,%d] %f degrees\n",rect.x,rect.y,rect.w,rect.h,direction);
//<<<<<<< zach CONFLICT
	//clip.y = frame * clip.h;
	//SDL_RenderCopyEx(renderer, texture, &clip, &rect, direction, NULL, SDL_FLIP_NONE);
//======= CONFLICT 
    SDL_RenderCopyEx(this->renderer,this->texture,NULL,&(this->rect),this->direction,NULL,SDL_FLIP_NONE);
//>>>>>>> master CONFLICT
}

void Character::friction()
{
    //slow down
//<<<<<<< zach CONFLICT
	//Instead of treating friction as if it were run every frame,
	//some code will do some friction based on how far you are moving.
	//The friction is the force caused by every square inch of 'space'
	//that you move through.
//double magnitude = sqrt(speed[0]*speed[0] + speed[1]*speed[1]);//take the magnitude
	//and decrease each by its portion of that.
	//speed[0]-=magnitude/speed[1];
	//speed[1]-=magnitude/speed[0];
//if(frame>0)frame--;
//======= CONFLICT
//>>>>>>> master CONFLICT
	if(speed[0]>=.0125){
		speed[0]-= .0125;//*SDL_abs(sped[0]/sumsped);
	}
	else if(speed[0]<= -.0125){
		speed[0]+=.0125;//*SDL_abs(sped[0]/sumsped);
	}
	else speed[0]=0;

	if(speed[1]>= .0125){
		speed[1]-= .0125;//*SDL_abs(sped[1]/sumsped);
	}
	else if(speed[1]<= -.0125){
		speed[1]+=.0125;//*SDL_abs(sped[1]/sumsped);
	}
	else speed[1]=0;

	if(omega>.125)omega-=.125;
	else if(omega<-.125)omega+=.125;
	else omega = 0;

}

void Character::destroy()
{
    //destroy character
}

Character::~Character()
{
    //destructor
}
