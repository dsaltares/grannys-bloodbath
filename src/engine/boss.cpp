#include <iostream>
#include <vector>
#include <string>
#include "actor.h"
#include "granny.h"
#include "sound.h"
#include "game.h"
#include "parser.h"
#include "resourcemngr.h"
#include "keyboard.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

using namespace std;


Boss::Boss(Game *g): Enemy(g)
{
	energy = 0;
	force = 0;
}

Boss::Boss(Game *g, const char *path, int x, int y): Enemy(g)
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
	
	bullet = new Bullet(g, "XML/spit.xml", 0, 0, direction, Bullet::BOSS);
}
		
Boss::~Boss()
{
	delete bullet;
	resource->free_sound(attack_code);	
}
		
void Boss::update()
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
		case KNEEL:
			spit_state();
			break;
		case RISE:
			spit_to_normal_state();
			break;
		default:
			break;
	}	
}
		
Actor * Boss::clone(int x, int y)
{
	Boss *z = new Boss(g);
	
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
	z->x = x;
	z->y = y;
	z->old_x = old_x;
	z->old_y = old_y;
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
		
void Boss::collides(Actor &a) {}

void Boss::spit()
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
		
bool Boss::within_range(int x, int y)
{
	const Granny *granny = g->get_granny();
	
	int positionx = abs(granny->get_x() - this->x);
	int positiony = abs(granny->get_y() - this->y);
	
	return (positionx <= x && positiony <= y);
}
		
void Boss::normal_state()
{
	state = MOVE;
}

void Boss::jumping_state()
{
	move(x,y+vy);
	vy+=2;
	if(vy >= vy0)
		vy = vy0;	
}

void Boss::moving_state()
{
	animations[MOVE]->update();
	
	// Nos movemos
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
		
	if(direction)
		move(x-vx, y);
	
	else
		move(x+vx, y);
	
	// Si podemos atacar directo
	if(within_range(50, 50) && in_view()){
		if(actual_delay >= attack_delay){		
			state = ATTACK;
			actual_delay = 0;
		}
		else
			actual_delay++;
	}
	
	// Si podemos atacar a distancia
	else if(within_range(200, 50) && in_view()){
		if(actual_shoot_delay >= shoot_delay){
			actual_shoot_delay = 0;
			state = KNEEL;
		}
		else
			actual_shoot_delay++;
	}
	
	vx = vx0;
}

void Boss::attack_state()
{
	if(animations[ATTACK]->update())
		state = NORMAL;
}

void Boss::damaged_state()
{
	if(animations[DAMAGED]->update())
		state = NORMAL;	
}

void Boss::death_state()
{
	if(animations[DIE]->update())
		state = ERASE;
}

void Boss::spit_state()
{
	if(animations[ATTACK]->update()){
		spit();
		state = RISE;
	}
}

void Boss::spit_to_normal_state()
{
	if(animations[RISE]->update())
		state = NORMAL;
}
