#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include "zombie.h"
#include "parser.h"
#include "resourcemngr.h"
#include "granny.h"
#include "animation.h"

using namespace std;

Zombie::Zombie(Game *g):Enemy(g)
{	
		energy = 0;
		force = 0;
}

Zombie::Zombie(Game *g, const char *path, int x, int y):Enemy(g)
{
	this->x = x;
	this->y = y;
	old_x = x;
	old_y = y;
	
	Parser parser(path);
	
	parser.get_attribute("code", parser.find("zombie"), &image_code);
	parser.get_attribute("vx", parser.find("zombie"), &vx);
	parser.get_attribute("vx", parser.find("zombie"), &vx0);
	parser.get_attribute("vy", parser.find("zombie"), &vy0);
	parser.get_attribute("energy", parser.find("zombie"), &energy);
	parser.get_attribute("force", parser.find("zombie"), &force);
	parser.get_attribute("attackdelay", parser.find("zombie"), &attack_delay);
	
	image = resource->image(image_code);
	
	parse_basic_info(parser);
	
	vector<ticpp::Element*> sounds;
	string code, situation;
	
	parser.find("sound", sounds, parser.find("sounds"));
	
	for(vector<ticpp::Element*>::iterator i = sounds.begin(); i != sounds.end(); ++i){
		situation = parser.get_attribute("situation", *i);
		code = parser.get_attribute("code", *i);

		if(situation == "hurt"){
			hurt = resource->sound(code);
			hurt_code = code;
		}
	}
	
	// Primero mira a la izquierda
	direction = true;
}

Zombie::~Zombie(){}

Actor* Zombie::clone(int x1, int y1)
{
	
	Zombie *z = new Zombie(g);
	
	z->image_code = image_code;
	z->image = resource->image(image_code);
	z->hurt_code = hurt_code;
	z->hurt = resource->sound(hurt_code);
	
	z->attack_delay = attack_delay;
	z->actual_delay = actual_delay;
	z->energy = energy;
	z->force = force;
	
	z->vx = vx;
	z->vy = vy;
	z->x = x1;
	z->y = y1;
	z->old_x = x1;
	z->old_y = y1;
	z->vx0 = vx0;
	z->vy0 = vy0;
	
	z->collision_map = collision_map;
	z->collision_map_inverted = collision_map_inverted;
	z->real_dimensions = real_dimensions;
	z->real_dimensions_inverted = real_dimensions_inverted;

	//Asignamos animaciones.
	for(Animations::iterator i = animations.begin(); i != animations.end(); ++i)	
		z->animations[i->first] = new Animation(*(i->second));

	return z;
}
		
void Zombie::collides(Actor& a){}

void Zombie::update()
{
	if(state != previous_state && state != ERASE){
		previous_state = state;
		animations[state]->restart();
		vy = 0;
	}

	switch(state){
	
		case NORMAL:
			normal_state();
			break;
		case JUMP:
			jumping_state();
			break;
		case MOVE:
			moving_state();
			break;
		case DAMAGED:
			damaged_state();
			break;
		case DIE:
			death_state();
			break;
		default:
			break;
	}

}

void Zombie::normal_state()
{
	
		state = MOVE;
}

void Zombie::moving_state()
{
	
	animations[MOVE]->update();
	
	/*if(!g->on_ground(*this,x+(vx*10),y)){
		
		if(direction)
			direction = false;
		else
			direction = true;
		vx = image->width()/2;
	}*/
	
	if(direction){
		if(!g->on_ground(*this, x-vx-20, y)){
			change_direction();
		}	
	}
	else{
		if(!g->on_ground(*this, x+vx+20, y)){
			change_direction();
		}
	}
	
	/*if(!g->on_ground(*this, x+vx, y))
		direction = !direction;*/
		
	if(direction)
		move(x-vx, y);
		
	else
		move(x+vx, y);
	
	vx = vx0;

}
void Zombie::damaged_state()
{
	
	if(animations[DAMAGED]->update())
		state = NORMAL;
}
void Zombie::death_state()
{
	
	if(animations[DIE]->update())
		state = ERASE;
}

void Zombie::jumping_state()
{
	
	move(x,y+vy);
	vy+=2;
	if(vy >= vy0)
		vy = vy0;
}

