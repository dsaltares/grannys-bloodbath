#include <iostream>
#include <vector>
#include <string>
#include "fat.h"
#include "actor.h"
#include "granny.h"
#include "sound.h"
#include "game.h"
#include "parser.h"
#include "resourcemngr.h"
#include "keyboard.h"
#include "hud.h"
#include "enemy.h"
#include "bullet.h"

using namespace std;

Fat::Fat(Game *g):Enemy(g)
{
	energy = 0;
	force = 0;
}

Fat::Fat(Game *g, const char *path, int x, int y):Enemy(g)
{
	this->x = x;
	this->y = y;
	old_x = x;
	old_y = y;
	
	Parser parser(path);
	
	parser.get_attribute("code", parser.find("fat"), &image_code);
	parser.get_attribute("vx", parser.find("fat"), &vx);
	parser.get_attribute("vx", parser.find("fat"), &vx0);
	parser.get_attribute("vy", parser.find("fat"), &vy0);
	parser.get_attribute("attackdelay", parser.find("fat"), &attack_delay);
	parser.get_attribute("shootdelay", parser.find("fat"), &shoot_delay);
	parser.get_attribute("force", parser.find("fat"), &force);
	parser.get_attribute("energy", parser.find("fat"), &energy);
		
	image = resource->image(image_code);
	
	actual_shoot_delay = shoot_delay;
	
	parse_basic_info(parser);
	
	vector<ticpp::Element*> sounds;
	string code, situation;
	
	parser.find("sound", sounds, parser.find("sounds"));
	
	for(vector<ticpp::Element*>::iterator i = sounds.begin(); i != sounds.end(); ++i){
		situation = parser.get_attribute("situation", *i);
		code = parser.get_attribute("code", *i);
	
		if(situation == "attack"){
			attack = resource->sound(code);
			attack_code = code;
		}
		else if(situation == "hurt"){
			hurt = resource->sound(code);
			hurt_code = code;
		}
	}
	
	bullet = new Bullet(g, "XML/vomit.xml", 0, 0, direction, Bullet::FAT);
}

Fat::~Fat()
{
	delete bullet;
	resource->free_sound(attack_code);
}

void Fat::update()
{

	if(state!=previous_state && state != ERASE){
		previous_state = state;
		animations[state]->restart();
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
		case ATTACK:
			attack_state();
			break;
		case DAMAGED:
			hurt->play();
			damaged_state();
			break;
		case DIE:
			death_state();
			break;
		case RISE:
			attackTOnormal_state();
			break;
		default:
			break;
	}
}

void Fat::collides(Actor &a){}

Actor *Fat::clone(int x1, int y1)
{
	
	Fat *z = new Fat(g);
	
	z->bullet = static_cast<Bullet*>(bullet->clone(0,0));
	
	z->image_code = image_code;
	z->image = resource->image(image_code);
	
	z->attack_code = attack_code;
	z->attack = resource->sound(attack_code);
	z->hurt_code = hurt_code;
	z->hurt = resource->sound(hurt_code);
	
	z->attack_delay = attack_delay;
	z->actual_delay = actual_delay;
	z->shoot_delay = shoot_delay;
	z->actual_shoot_delay = actual_shoot_delay;
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

void Fat::normal_state()
{
	state = MOVE;
}

void Fat::moving_state(){
	
	animations[MOVE]->update();
	
	if(!within_range() && !in_view())
	{
		if(direction){
			if(!g->on_ground(*this, x-vx-40, y)){
				change_direction();
			}	
		}
		else{
			if(!g->on_ground(*this, x+vx+40, y)){
				change_direction();
			}
		}
	}
	
	if(direction)
		move(x-vx, y);
		
	else
		move(x+vx, y);
	
	vx = vx0;
}

void Fat::jumping_state(){
	
	move(x,y+vy);
	vy+=2;
	if(vy >= vy0)
		vy = vy0;
}


void Fat::attack_state()
{
	if(animations[ATTACK]->update()){
		shoot_vomit();
		state = RISE;
	}
}

void Fat::attackTOnormal_state()
{
	if(animations[RISE]->update())
		state = NORMAL;
}


void Fat::damaged_state()
{
	if(animations[DAMAGED]->update())
		state = NORMAL;
}

void Fat::death_state()
{
	if(animations[DIE]->update())
		state = ERASE;
}

void Fat::shoot_vomit()
{
	Bullet *b;
	attack->play();
	if(direction){
		b = static_cast<Bullet*>(bullet->clone(x + 20, y + 40));
		b->set_direction(direction);
		g->add_bullet(b);
	}
	else{
		b = static_cast<Bullet*>(bullet->clone(x + 100, y + 40));
		b->set_direction(direction);
		g->add_bullet(b);
	}	
}

bool Fat::within_range()
{
	const Granny *granny = g->get_granny();
	
	int positionx = abs(granny->get_x() - this->x);
	int positiony = abs(granny->get_y() - this->y);
	
	/*std::cout << "Estado disparar" << std::endl; 
	std::cout << "Actual shoot delay: " <<  actual_shoot_delay << std::endl; 
	std::cout << "Shoot delay: " <<  shoot_delay << std::endl; */
	if(positionx <= 200 && positiony <= 50){
		
		if(actual_shoot_delay >= shoot_delay){	
			
			if(granny->get_x() < this->x)
				direction = true;
			else
				direction = false;
				
			actual_shoot_delay = 0;
			state = ATTACK;
		}
		else
			actual_shoot_delay += 1;
			
		return true;
	}
	
	return false;
}





