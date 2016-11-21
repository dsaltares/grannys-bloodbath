#include <algorithm>
#include "collisionmngr.h"

using namespace std;

bool CollisionMngr::actor_collision(Actor& a1, Actor& a2) const
{
	Actor::Collision_Rects col_a1 = a1.get_rects();
	Actor::Collision_Rects col_a2 = a2.get_rects();
	
	// Comparamos cada caja de colisión del actor 1 con cada caja de colisión del actor 2
	for(Actor::Collision_Rects::const_iterator i = col_a1.begin(); i != col_a1.end(); ++i)
		for(Actor::Collision_Rects::const_iterator j = col_a2.begin(); j != col_a2.end(); ++j)
			if(collision(a1.get_x() + i->x, a1.get_y() + i->y, i->w, i->h, a2.get_x() + j->x,  a2.get_y() + j->y, j->w, j->h))
				return true;
	
	return false;
}

bool CollisionMngr::level_collision(Actor& actor, Level& level)
{
	int tile_pos;
	int old_y = actor.get_old_y();
	Actor::Collision_Rects collision_rects = actor.get_rects();
	bool x_collision = false;

	// Para cada caja de colision
	for(vector<SDL_Rect>::iterator i = collision_rects.begin(); i != collision_rects.end(); ++i){
	
		// Comprobamos el eje X
		// Vamos hacia la izquierda
		if(actor.get_direction() && collision_ver(actor.get_x() + i->x, old_y + i->y - 1, i->w, i->h, tile_pos, level, false)){
			actor.move(tile_pos + level.get_tile_width() - actor.get_real_dimensions().x, actor.get_y());
			x_collision = true;
		}
		// Vamos hacia la derecha
		else if(collision_ver(actor.get_x() + i->x + i->w, old_y + i->y - 1, i->w, i->h, tile_pos, level, true)){
			actor.move(tile_pos - actor.get_real_dimensions().w - actor.get_real_dimensions().x - 1, actor.get_y());
			x_collision = true;
		}
		
		int actor_x = actor.get_x() + i->x;
		
		if(actor.get_direction())
			actor_x += 10;
		else
			actor_x -= 10;
		
		
		// Comprobamos el eje Y
		// Si vamos hacia arriba
		if(actor.get_vy() < 0){
			if(collision_hor(actor_x, actor.get_y() + i->y, i->w, i->h, tile_pos, level, true)){
				actor.move(actor.get_x(), tile_pos + level.get_tile_height() - actor.get_real_dimensions().y);
				actor.set_vy(0);
			}
		}
		// Si pisamos el suelo y estábamos saltando
		else if(actor.get_state() == Actor::JUMP && collision_hor(actor.get_x() + i->x, actor.get_y() + i->y + i->h, i->w, i->h, tile_pos, level, false)){
			actor.set_state(Actor::NORMAL);
			actor.set_vy(0);
			actor.move(actor.get_x(), tile_pos - actor.get_real_dimensions().h - actor.get_real_dimensions().y);
		}
		// Si no pisamos el suelo y no estábamos saltando
		else if(actor.get_state() != Actor::JUMP && !collision_hor(actor.get_x() + i->x, actor.get_y() + i->y + i->h + 3, i->w, i->h, tile_pos, level, false)){
				actor.set_state(Actor::JUMP);
		}
	}
	
	return x_collision;		 
}

bool CollisionMngr::on_ground(const Actor& actor, const Level& level, int x, int y) const
{
	Actor::Collision_Rects collision_rects = actor.get_rects();
	int tile_pos;
	
	// Para cada caja de colision
	for(vector<SDL_Rect>::iterator i = collision_rects.begin(); i != collision_rects.end(); ++i)
		if(collision_hor(x + i->x, y + i->y + i->h + 3, i->w, i->h, tile_pos, level, false))
			return true;
	
	return false;
}

bool CollisionMngr::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const
{
	return (((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1));
}

bool CollisionMngr::collision_hor(int x, int y, Uint16 w, Uint16 h, int& tilecoordy, const Level& level, bool up) const
{
	int tiles_x0 = x / level.get_tile_width();
	int tiles_x1 = (x + w) / level.get_tile_width();
	tilecoordy = y / level.get_tile_height();
	
	for(int i = tiles_x0; i <= tiles_x1; ++i){
		if(level.get_tile(i, tilecoordy, 1).type == NONPASSABLE || level.get_tile(i, tilecoordy, 0).type == NONPASSABLE){
			tilecoordy *= level.get_tile_height();
			return true;
		}
		
		if(!up && (level.get_tile(i, tilecoordy, 1).type == PLATFORM || level.get_tile(i, tilecoordy, 0).type == PLATFORM)){
			tilecoordy *= level.get_tile_height();
			return true;
		}
	}
	
	return false;
}

bool CollisionMngr::collision_ver(int x, int y, Uint16 w, Uint16 h, int& tilecoordx, const Level& level, bool right) const
{
	int tiles_y0 = y / level.get_tile_height();
	int tiles_y1 = (y + h) / level.get_tile_height();
	tilecoordx = x / level.get_tile_width();
	
	for(int i = tiles_y0; i <= tiles_y1; ++i){
		if(level.get_tile(tilecoordx, i, 1).type == NONPASSABLE || level.get_tile(tilecoordx, i, 0).type == NONPASSABLE){
			tilecoordx *= level.get_tile_width();
			return true;
		}
	}
	
	return false;
}

bool CollisionMngr::bullet_collision(const Actor& bullet, Level& level) const{
	
	int tile_pos;
	int old_y = bullet.get_old_y();
	Actor::Collision_Rects collision_rects = bullet.get_rects();
	//bool x_collision = false;
	
	// Para cada caja de colision
	for(vector<SDL_Rect>::iterator i = collision_rects.begin(); i != collision_rects.end(); ++i){
		
		if(collision_ver(bullet.get_x() + i->x, old_y + i->y -1, i->w, i->h, tile_pos, level, false))
			return true;

	}
	
	return false;
}
