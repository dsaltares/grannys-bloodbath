#include "item.h"
#include "game.h"
#include "parser.h"
#include "resourcemngr.h"

using namespace std;

Item::Item(Game *g):Actor(g){}

Item::Item(Game* game, const char* path, int x, int y): Actor(game)
{
	Parser parser(path);
	
	// Obtenemos el sprite
	image_code = parser.get_attribute("code", parser.find("item"));
	image = resource->image(image_code);
	
	// Obtenemos el tipo de item
	type = TEETH;
	string item_type = parser.get_attribute("type", parser.find("item"));
	if(item_type == "teeth")
		type = TEETH;
	else if(item_type == "pills")
		type = PILLS;
	else if(item_type == "ammo")
		type = AMMO;
	
	parse_basic_info(parser);
	
	this->x = x;
	this->y = y;
}

Item::~Item() {}

void Item::update(void)
{
	animations[state]->update();
}

void Item::collides(Actor& a)
{
	state = ERASE;
}

Item* Item::clone(int x1, int y1)
{
	Item *z = new Item(g);
	
	z->image_code = image_code;
	z->image = resource->image(image_code);
	z->type = type;
	
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

Item::ItemType Item::get_type() const
{
	return type;
}
