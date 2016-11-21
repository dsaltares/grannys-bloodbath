#include "actor.h"
#include "enemy.h"
#include "game.h"
#include "granny.h"
#include "resourcemngr.h"

using namespace std;

Enemy::Enemy(Game *g):Actor(g){
	actual_delay = 10;
	direction  = false;
}

Enemy::~Enemy(){
	resource->free_sound(hurt_code);
}

void Enemy::damaged()
{	
	if(state != DAMAGED && state != DIE && state != ERASE){
		
		if(hurt)
			hurt->play();
		
		--energy;
			
		if(energy > 0)
			state = DAMAGED;
		else
			state = DIE;
	}	
}

void Enemy::change_direction()
{
	SDL_Rect rect = get_real_dimensions();
	
	if(direction){
		direction = false;
		x += (image->width() - rect.x - rect.w);
	}
	else{
		direction = true;
		x -= (image->width() - rect.x - rect.w);
	}
}

bool Enemy::in_view()
{
	const Granny *granny = g->get_granny();
	
	int positionx = abs(granny->get_x() - this->x);
	int positiony = abs(granny->get_y() - this->y);
	
	if(positionx <= 400 && positiony <= 95){
				
		if(granny->get_x() < this->x)
			direction = true;
		else
			direction = false;
			
		return true;
	}
	
	return false;
}
