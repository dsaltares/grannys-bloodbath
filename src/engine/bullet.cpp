#include <vector>
#include <string>
#include <SDL/SDL.h>
#include "parser.h"
#include "bullet.h"
#include "resourcemngr.h"

using namespace std;

Bullet::Bullet(Game *g):Actor(g){
	
		owner = GRANNY;
		force = 0;
}

Bullet::Bullet(Game *g, const char* path, int x, int y, bool direction, Bullet::Owner o):Actor(g), owner(o){
	
	this->x = x;
	this->y = y;
	this->old_x = x;
	this->old_y = y;
	this->direction = direction;
	
	Parser parser(path);
	
	image_code = parser.get_attribute("imagecode", parser.find("bullet"));
	parser.get_attribute("vx", parser.find("bullet"), &vx);
	parser.get_attribute("vy", parser.find("bullet"), &vy);
	parser.get_attribute("force", parser.find("bullet"), &force);
	
	image = resource->image(image_code);
	
	parse_basic_info(parser);
}

Bullet::~Bullet(){
}


void Bullet::update(){
	
	if(state != ERASE){
		
		if(direction)
			move(x-vx,y);
		else
			move(x+vx,y);

		
		if(!(g->on_screen(*this)))
			state = ERASE;
	}

}

Actor* Bullet::clone(int x1, int y1){
	
	Bullet *z = new Bullet(g);
	
	z->image_code = image_code;
	z->image = resource->image(image_code);
	
	z->vx = vx;
	z->vy = vy;
	z->x = x1;
	z->y = y1;
	z->old_x = x1;
	z->old_y = y1;
	z->vx0 = vx0;
	z->vy0 = vy0;
	z->force = force;
	z->owner = owner;
	z->collision_map = collision_map;
	z->collision_map_inverted = collision_map_inverted;
	z->real_dimensions = real_dimensions;
	z->real_dimensions_inverted = real_dimensions_inverted;

	//Asignamos animaciones.
	for(Animations::iterator i = animations.begin(); i != animations.end(); ++i)	
		z->animations[i->first] = new Animation(*(i->second));

	return z;	
}

void Bullet::collides(Actor& a){
	
	state = ERASE;
	
}
