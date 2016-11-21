#include <SDL/SDL.h>
#include <vector>
#include <map>
#include "actor.h"
#include "game.h"
#include "animation.h"
#include "resourcemngr.h"
#include "parser.h"

using namespace std;

Actor::Actor(Game* game): g(game)
{
	x = y = vx = vy = vx0 = vy0 = old_x = old_y = 0;
	direction=false;
	previous_state = state = NORMAL;
}

Actor::~Actor()
{
	resource->free_image(image_code);
	image=NULL;
	
	for(Animations::iterator i = animations.begin(); i != animations.end(); ++i)
		delete i->second;
		
	animations.clear();
}

const Actor::Collision_Rects& Actor::get_rects() const
{
	Actor::Collision_Map::const_iterator i;
	
	if(direction){
		i = collision_map_inverted.find(state);
		
		if(i == collision_map_inverted.end())
			return collision_map_inverted.find(NORMAL)->second;
		else
			return i->second;
	}
	else{
		i = collision_map.find(state);
		
		if(i == collision_map.end())
			return collision_map.find(NORMAL)->second;
		else
			return i->second;	
	}
}

SDL_Rect Actor::get_real_dimensions() const
{
	map<State, SDL_Rect>::const_iterator i;
	
	if(direction){
		i = real_dimensions_inverted.find(state);
		
		if(i == real_dimensions_inverted.end())
			return real_dimensions_inverted.find(NORMAL)->second;
		else
			return i->second;
	}
	else{
		i = real_dimensions.find(state);
		
		if(i == real_dimensions.end())
			return real_dimensions.find(NORMAL)->second;
		else
			return i->second;	
	}
}

void Actor::move(int x, int y)
{
	old_x = this->x;
	old_y = this->y;
	this->x = x;
	this->y = y;
}

void Actor::set_vx(int vx)
{
	this->vx = vx;
}

void Actor::set_vy(int vy)
{
	this->vy = vy;
}

void Actor::set_state(State state)
{
	this->state = state;	
}

void Actor::set_direction(bool direction)
{
	this->direction = direction;
}

void Actor::draw(SDL_Surface* screen)
{
	Animations::const_iterator i = animations.find(state);
	
	Animation* a=animations[NORMAL];
	
	if(i == animations.end())
		image->draw(screen, a->get_frame(), x - g->level_x(), y - g->level_y(), direction);
	else
		image->draw(screen, i->second->get_frame(), x - g->level_x(), y - g->level_y(), direction);
}

void Actor::parse_basic_info(Parser& parser)
{
	std::vector<ticpp::Element *> animation;
	std::vector<ticpp::Element *>::iterator i;
	std::string name, secuency;
	int delay;
	
	parser.find("animation", animation, parser.find("animations") );
	
	for(i = animation.begin(); i != animation.end(); ++i){
		
			name = parser.get_attribute("name", *i);
			secuency = parser.get_attribute("frames", *i);
			parser.get_attribute("delay",*i,&delay);
			
		if(name=="normal")
			animations[NORMAL]=new Animation(secuency.c_str(),delay);
		if(name=="normaldown")
			animations[NORMALDOWN]=new Animation(secuency.c_str(),delay);
		if(name=="move")
			animations[MOVE]=new Animation(secuency.c_str(),delay);
		if(name=="jump")
			animations[JUMP]=new Animation(secuency.c_str(),delay);
		if(name=="attack")
			animations[ATTACK]=new Animation(secuency.c_str(),delay);
		if(name=="damage")
			animations[DAMAGED]=new Animation(secuency.c_str(),delay);
		if(name=="kneel")
			animations[KNEEL]=new Animation(secuency.c_str(),delay);
		if(name=="rise")
			animations[RISE]=new Animation(secuency.c_str(),delay);
		if(name=="die")
			animations[DIE]=new Animation(secuency.c_str(),delay);
				
	}
	
	std::vector<ticpp::Element *> collision;
	SDL_Rect box, inverted_box;
	
	parser.find("collision",collision,parser.find("collisions"));
	
	for(i = collision.begin(); i != collision.end(); ++i){
		
		name = parser.get_attribute("state", *i);
		parser.get_attribute("x", *i, &(box.x));
		parser.get_attribute("y", *i, &(box.y));
		parser.get_attribute("w", *i, &(box.w));
		parser.get_attribute("h", *i, &(box.h));
		
		inverted_box.x = image->width() - box.x - box.w;
		inverted_box.y = box.y;
		inverted_box.w = box.w;
		inverted_box.h = box.h;
		
				if(name == "normal"){
			collision_map[NORMAL].push_back(box);
			collision_map_inverted[NORMAL].push_back(inverted_box);
		}
		else if(name == "normaldown"){
			collision_map[NORMALDOWN].push_back(box);
			collision_map_inverted[NORMALDOWN].push_back(inverted_box);
		}
		else if(name == "move"){
			collision_map[MOVE].push_back(box);
			collision_map_inverted[MOVE].push_back(inverted_box);
		}
		else if(name == "jump"){
			collision_map[JUMP].push_back(box);
			collision_map_inverted[JUMP].push_back(inverted_box);
		}
		else if(name == "attack"){
			collision_map[ATTACK].push_back(box);
			collision_map_inverted[ATTACK].push_back(inverted_box);
		}
		else if(name == "damage"){
			collision_map[DAMAGED].push_back(box);
			collision_map_inverted[DAMAGED].push_back(inverted_box);
		}
		else if(name == "kneel"){
			collision_map[KNEEL].push_back(box);
			collision_map_inverted[KNEEL].push_back(inverted_box);
		}
		else if(name == "rise"){
			collision_map[RISE].push_back(box);
			collision_map_inverted[RISE].push_back(inverted_box);
		}
		else if(name == "die"){
			collision_map[DIE].push_back(box);	
			collision_map_inverted[DIE].push_back(inverted_box);
		}
		
	}

	std::vector<ticpp::Element*> dimensions;
	SDL_Rect box_dimensions;
	SDL_Rect inverted_box_dimensions;
	
	parser.find("dimension", dimensions, parser.find("dimensions"));
	for(i = dimensions.begin(); i != dimensions.end(); ++i){
		
		name = parser.get_attribute("state", *i);
		parser.get_attribute("x", *i, &(box_dimensions.x));
		parser.get_attribute("y", *i, &(box_dimensions.y));
		parser.get_attribute("w", *i, &(box_dimensions.w));
		parser.get_attribute("h", *i, &(box_dimensions.h));

		inverted_box_dimensions.x = image->width() - box_dimensions.x - box_dimensions.w;
		inverted_box_dimensions.y = box_dimensions.y;
		inverted_box_dimensions.w = box_dimensions.w;
		inverted_box_dimensions.h = box_dimensions.h;
		
		if(name == "normal"){
			real_dimensions[NORMAL] = box_dimensions;
			real_dimensions_inverted[NORMAL] = inverted_box_dimensions;
		}
		else if(name == "normaldown"){
			real_dimensions[NORMALDOWN] =  box_dimensions;
			real_dimensions_inverted[NORMALDOWN] = inverted_box_dimensions;
		}
		else if(name == "move"){
			real_dimensions[MOVE] =  box_dimensions;
			real_dimensions_inverted[MOVE] = inverted_box_dimensions;
		}
		else if(name == "jump"){
			real_dimensions[JUMP] =  box_dimensions;
			real_dimensions_inverted[JUMP] = inverted_box_dimensions;
		}
		else if(name == "attack"){
			real_dimensions[ATTACK] =  box_dimensions;
			real_dimensions_inverted[ATTACK] = inverted_box_dimensions;
		}
		else if(name == "damage"){
			real_dimensions[DAMAGED] =  box_dimensions;
			real_dimensions_inverted[DAMAGED] = inverted_box_dimensions;
		}
		else if(name == "kneel"){
			real_dimensions[KNEEL] = box_dimensions;
			real_dimensions_inverted[KNEEL] = inverted_box_dimensions;
		}
		else if(name == "rise"){
			real_dimensions[RISE] = box_dimensions;
			real_dimensions_inverted[RISE] = inverted_box_dimensions;
		}
		else if(name == "die"){
			real_dimensions[DIE] =  box_dimensions;
			real_dimensions_inverted[DIE] = inverted_box_dimensions;
		}
		
	}
}
