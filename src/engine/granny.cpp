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
#include "hud.h"
#include "enemy.h"
#include "bullet.h"
#include "item.h"

using namespace std;

Granny::Granny(Game *g, const char *path, int x, int y) :Actor(g)
{
	this->x = x;
	this->y = y;
	old_x = x;
	old_y = y;
	
	Parser parser(path);

	parser.get_attribute("code", parser.find("granny"), &image_code);
	parser.get_attribute("vx", parser.find("granny"), &vx);
	parser.get_attribute("vy", parser.find("granny"), &vy0);
	parser.get_attribute("lifes", parser.find("granny"), &lifes);
	parser.get_attribute("points", parser.find("granny"), &points);
	parser.get_attribute("munition", parser.find("granny"), &munition);
	parser.get_attribute("energy", parser.find("granny"), &energy);
	
	max_energy = energy;

	hud_ = new HUD("XML/hud.xml",energy);
	
	image=resource->image(image_code);
	
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
		else if(situation == "shoot"){
			shoot = resource->sound(code);
			shoot_code = code;
		}
		else if(situation == "win"){
			win = resource->sound(code);
			win_code = code;
		}
		else if(situation == "jump"){
			jump = resource->sound(code);
			jump_code = code;
		}
		else if(situation == "hurt")
			hurt_sounds.push_back(make_pair(resource->sound(code), code));
	}

	bullet = new Bullet(g, "XML/bullet.xml", 0, 0, direction, Bullet::GRANNY);
}

Granny::~Granny(){
	delete hud_;
	delete bullet;
	
	resource->free_sound(win_code);
	resource->free_sound(shoot_code);
	resource->free_sound(attack_code);
	resource->free_sound(jump_code);
	
	for(vector<pair<Sound*, string> >::iterator i = hurt_sounds.begin(); i != hurt_sounds.end(); ++i)
		resource->free_sound(i->second);
	
	hurt_sounds.clear();
}

void Granny::update(){

	if(state!=previous_state){
		previous_state = state;
		animations[state]->restart();
	}

	switch(state){
	
		case NORMAL:
			Normal_State();
			break;
		case NORMALDOWN:
			NormalDown_State();
			break;
		case MOVE:
			Moving_State();
			break;
		case JUMP:
			Jumping_State();
			break;
		case ATTACK:
			Attaking_State();
			break;
		case DAMAGED:
			Damaged_State();
			break;
		case KNEEL:
			Kneeled_State();
			break;
		case RISE:
			Rising_State();
			break;
		case DIE:
			Dead_State();
			break;
		default:
			break;
	}

	hud_->update(lifes,points,munition,energy);
}

void Granny::collides(Actor& a){}

void Granny::damaged(int i)
{
	// Reproducimos un sonido de golpe aleatorio
	hurt_sounds[rand() % hurt_sounds.size()].first->play();
	
	energy -= i;

	if(energy > 0)
		state = DAMAGED;		
	else{
		state = DIE;
		energy = 0;
	}
}

void Granny::get_item(const Item& i)
{
	if(i.get_type() == Item::TEETH){
		++points;
		if(points%20 == 0)
			++lifes;
	}
			
	else if(i.get_type() == Item::PILLS){
				
		if(energy<max_energy)
			++energy;
	}
			
	else if(i.get_type() == Item::AMMO)
		++munition;
}

void Granny::Normal_State(){

	if(keyboard->pressed(Keyboard::KEY_LEFT)){
	
		if(!direction){
		
			move(x-image->width()/2, y);
			direction = true;
		}
		
		state = MOVE;
	}
	
	if(keyboard->pressed(Keyboard::KEY_RIGHT)){
	
		if(direction){
			move(x+image->width()/2, y);
			direction=false;	
		}
		
		state = MOVE;
	}
	
	if(keyboard->pressed(Keyboard::KEY_DOWN))
		state = KNEEL;
		
	if(keyboard->pressed(Keyboard::KEY_HIT)){
		state = ATTACK;
		attack->play();
	}
		
	if(keyboard->newpressed(Keyboard::KEY_UP)){
		jump->play();
		state = JUMP;
		vy = -vy0;
	}
	
	if(keyboard->newpressed(Keyboard::KEY_SHOOT)){
		shoot_gun();		
	}
}

void Granny::Moving_State(){

	animations[MOVE]->update();
	
	if(direction)
		move(x-vx, y);
	else
		move(x+vx, y);

	if(keyboard->released(Keyboard::KEY_RIGHT) || keyboard->released(Keyboard::KEY_LEFT))
		state = NORMAL;

	if(direction == true && keyboard->pressed(Keyboard::KEY_RIGHT))
		state = NORMAL;
		
	if(direction == false && keyboard->pressed(Keyboard::KEY_LEFT))
		state = NORMAL;
		
	if(keyboard->pressed(Keyboard::KEY_HIT)){
		state = ATTACK;
		attack->play();
	}
		
	if(keyboard->newpressed(Keyboard::KEY_UP)){
		jump->play();
		state = JUMP;
		vy = -vy0;
	}
	
	if(keyboard->newpressed(Keyboard::KEY_SHOOT))
		shoot_gun();

}

void Granny::Jumping_State()
{			
	if(keyboard->pressed(Keyboard::KEY_RIGHT)){
	
		if(direction){
			move(x+image->width()/2, y);
			direction = false;
		}
		else
			move(x+vx,y);
	}
	
	if(keyboard->pressed(Keyboard::KEY_LEFT)){
	
		if(!direction){
			move(x-image->width()/2, y);
			direction = true;
		}
		
		else
			move(x-vx, y);
	}
	
	if(vy<=0)
		animations[JUMP]->update();
		
		
	move(x, y+vy);
	vy += 2;
	if(vy >= 31)
		vy = 31;
}

void Granny::Kneeled_State()
{

	if(animations[KNEEL]->update())
		state = NORMALDOWN;

	if(keyboard->released(Keyboard::KEY_DOWN))
			state = NORMAL;
		
	if(keyboard->pressed(Keyboard::KEY_LEFT)){
		direction = true;
		state = MOVE;
	}
	
	if(keyboard->pressed(Keyboard::KEY_RIGHT)){
		direction = false;
		state = MOVE;
	}
}

void Granny::NormalDown_State(){

	if(keyboard->released(Keyboard::KEY_DOWN))
			state = RISE;
		
	if(keyboard->pressed(Keyboard::KEY_LEFT)){
	
		if(!direction){
			move(x-image->width()/2, y);			
			direction = true;
		}
		
		state = MOVE;
	}
	
	if(keyboard->pressed(Keyboard::KEY_RIGHT)){
	
		if(direction){
			move(x+image->width()/2, y);			
			direction = false;
		}
		
		state = MOVE;
	}
}

void Granny::Rising_State(){
	if(animations[RISE]->update())
		state = NORMAL;	
}

void Granny::Attaking_State(){

	if(animations[ATTACK]->update())
		state = NORMAL;
}
void Granny::Damaged_State(){

	if(animations[DAMAGED]->update())
		state = NORMAL;
		
	if(keyboard->pressed(Keyboard::KEY_LEFT)){
	
		if(!direction){
		
			move(x-image->width()/2, y);
			direction = true;
		}
		
		state = MOVE;
	}
	
	if(keyboard->pressed(Keyboard::KEY_RIGHT)){
	
		if(direction){
			move(x+image->width()/2, y);
			direction=false;	
		}
		
		state = MOVE;
	}
}

void Granny::Dead_State(){

	if(animations[DIE]->update()){
		--lifes;
		state = ERASE;
	}
}

void Granny::draw(SDL_Surface* screen)
{
	Animations::const_iterator i = animations.find(state);
		
	Animation* a=animations[NORMAL];
	
	if(i == animations.end())
		image->draw(screen, a->get_frame(), x - g->level_x(), y - g->level_y(), direction);
	else
		image->draw(screen, i->second->get_frame(), x - g->level_x(), y - g->level_y(), direction);
		
	hud_->draw(screen);
}

void Granny::reset()
{
	energy = max_energy;
	state = NORMAL;
}

void Granny::epic_win()
{
	win->play();
}

void Granny::shoot_gun(){
			
	if(munition > 0){
		Bullet *b;
		shoot->play();
		--munition;
		if(direction){
			b = static_cast<Bullet*>(bullet->clone(x + 20, y +70));
			b->set_direction(direction);
			g->add_bullet(b);
		}
		else{
			b = static_cast<Bullet*>(bullet->clone(x + 100, y + 70));
			b->set_direction(direction);
			g->add_bullet(b);
		}
	}
			
}
