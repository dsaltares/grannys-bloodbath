#include "game.h"
#include "scenemngr.h"
#include "granny.h"
#include "enemy.h"
#include "collisionmngr.h"
#include "level.h"
#include "keyboard.h"
#include "item.h"
#include "bullet.h"
#include "logger.h"
#include "music.h"
#include "resourcemngr.h"

using namespace std;


Game::Game(SceneMngr* sm, const char* path, bool boss_fight): Scene(sm), level_path(path)
{
	granny = new Granny(this, "XML/granny.xml", 30, 200);
	music = 0;
	level = new Level(this, path);
	if(music)
		music->fadein(1000);
	this->boss_fight = boss_fight;
}
			
Game::~Game()
{
	// Eliminamos a la abuela
	delete granny;
	
	// Eliminamos el nivel
	delete level;
	
	// Eliminamos todos los enemigos
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i)
		delete (*i);
		
	enemy_list.clear();
	
	// Eliminamos todos los items
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end(); ++i)
		delete (*i);
		
	item_list.clear();
		
	// Eliminamos todas las balas
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i)
		delete (*i);
		
	bullet_list.clear();
	
	resource->free_music(music_code);
}

void Game::reset()
{
	// Eliminamos el nivel
	delete level;
	
	// Eliminamos todos los enemigos
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i)
		delete (*i);
	
	enemy_list.clear();
	
	// Eliminamos todos los items
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end(); ++i)
		delete (*i);
	
	item_list.clear();
		
	// Eliminamos todas las balas
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i)
		delete (*i);
		
	bullet_list.clear();
	
	// Cargamos el nivel de nuevo
	level = new Level(this, level_path.c_str());
	
	// Movemos la abuela al comienzo
	granny->move(30, 200);	
	granny->reset();	
}

void Game::resume()
{
	if(music)
		music->fadein(1000);
}

void Game::update()
{	
	// Actualizamos a la abuela
	granny->update();
	
	// Actualizamos a los enemigos que estén en pantalla
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i)
		if(on_screen(*(*i)))
			(*i)->update();
	
	// Actualizamos a los items que estén en pantalla
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end(); ++i)
		if(on_screen(*(*i)))
			(*i)->update();
	
	// Actualizamos las balas
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i)
		(*i)->update();
	
	// Si la abuela se sale por la izquierda la paramos
	if(granny->get_x() < 0)
		granny->move(0, granny->get_y());
	
	// Si la abuela se sale por la derecha hacemos scroll
	else if(granny->get_x() + granny->get_real_dimensions().x + granny->get_real_dimensions().w - level->get_x() + 200 > scene_mngr->get_screen_width())
		level->move(level->get_x() + granny->get_vx(), level->get_y());
		
	// Si la abuela se sale por la izquierda hacemos scroll (pero no si volvemos al principio del nivel)
	else if(granny->get_x() - level->get_x() - 150 < 0){
		int new_level_x = ((level->get_x() - granny->get_vx()) < 0)? 0 : (level->get_x() - granny->get_vx() - 2);
		
		level->move(new_level_x, level->get_y());
	}
	
	// Comprobamos las colisiones
	check_collisions();
	
	// Eliminamos actores sobrantes
	delete_actors();
	
	// Comprobamos si hemos llegado al final de la escena
	check_end();
}

void Game::draw(SDL_Surface* screen)
{	
	// Dibujamos las capas de fondo del nivel
	level->draw(screen, 0);
	level->draw(screen, 1);
	
	// Dibujamos a la abuela
	granny->draw(screen);
	
	// Dibujamos a los enemigos que están en pantalla
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i)
		if(on_screen(*(*i)))
			(*i)->draw(screen);
	
	// Dibujamos a los items que están en pantalla
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end(); ++i)
		if(on_screen(*(*i)))
			(*i)->draw(screen);
	
	// Dibujamos a las balas que están en pantalla
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i)
		if((*i)->get_state() != Actor::ERASE)
			(*i)->draw(screen);
			
	level->draw(screen, 2);
}
		
void Game::add_item(Item* item)
{
	if(item)
		item_list.push_back(item);
}

void Game::add_enemy(Enemy* enemy)
{
	if(enemy)
		enemy_list.push_back(enemy);
}

void Game::add_granny(Granny* granny)
{
	if(granny){
		if(this->granny){
			logger->error("Game::add_granny(): Ya hay una abuela en juego");
			exit(1);
		}
		else
			this->granny = granny;
	}
}

void Game::add_bullet(Bullet* bullet)
{
	if(bullet)
		bullet_list.push_back(bullet);
}

void Game::set_music(const std::string& music_code)
{
	music = resource->music(music_code);
}

bool Game::on_ground(const Actor& actor, int x, int y) const
{
	return collision_mngr.on_ground(actor, *level, x, y);
}

bool Game::on_screen(const Actor& actor) const
{
	int x1, x2, y1, y2, w1, w2, h1, h2;
	SDL_Rect real_dimensions = actor.get_real_dimensions();
	
	x1 = actor.get_x()  + real_dimensions.x;
	y1 = actor.get_y() + real_dimensions.y;
	w1 = real_dimensions.w;
	h1 = real_dimensions.h;
	x2 = level->get_x();
	y2 = level->get_y();
	w2 = scene_mngr->get_screen_width();
	h2 = scene_mngr->get_screen_height();
	
	return (((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1));
}

void Game::check_collisions()
{
	// Colisiones abuela/enemigo
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i){
		if(on_screen(*(*i)) && collision_mngr.actor_collision(*granny, *(*i))){
			if(granny->get_state() == Actor::ATTACK && ((granny->get_direction() && (granny->get_x() > (*i)->get_x())) || (!granny->get_direction() && (granny->get_x() < (*i)->get_x()))))
				(*i)->damaged();
			else{
				//Controlamos que la abuela no pueda atravesar al enemigo
				if(granny->get_direction() && (granny->get_x() > (*i)->get_x()))
					granny->move(granny->get_x() + granny->get_vx(), granny->get_y());
				else if(!granny->get_direction() && (granny->get_x() < (*i)->get_x()))
					granny->move( granny->get_x() - granny->get_vx(), granny->get_y());
					
				(*i)->set_vx(0);
				if( (granny->get_state() != Actor::DAMAGED) && ((*i)->get_state() != Actor::DAMAGED) && ((*i)->get_state() != Actor::DIE) && ((*i)->get_state() != Actor::ERASE) && ((*i)->get_actualdelay() >=(*i)->get_attackdelay()) ){
					granny->damaged((*i)->get_force());
					(*i)->set_actualdelay(0);
				}
				else
					(*i)->set_actualdelay( (*i)->get_actualdelay() + 1 );
			}
		}
	}
	
	// Si al desplazar la abuela no toca el suelo
	
	if(!collision_mngr.on_ground(*granny, *level, granny->get_x(), granny->get_y()))
		granny->set_state(Actor::JUMP);
	
	// Colisiones abuela escenario
	collision_mngr.level_collision(*granny, *level);
		
	// Colisiones enemigos/escenario (¿Son necesarias?)
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i){
		if(on_screen(*(*i))){
			if(collision_mngr.level_collision(**i, *level))
				(*i)->change_direction();
			if((*i)->get_x() < 20){
				(*i)->move(20, (*i)->get_y());
				(*i)->change_direction();
			}
			else if((*i)->get_x() + 400 > level->get_width() * level->get_tile_width()){
				(*i)->move(level->get_width() * level->get_tile_width() - 400, (*i)->get_y());
				(*i)->change_direction();
			}
		}
	}
		
	// Colisiones abuela/items
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end(); ++i){
		if(on_screen(*(*i)) && collision_mngr.actor_collision(*granny, *(*i))){
			(*i)->collides(*granny);
			granny->get_item(*(*i));
		}
	}
	
	//Colisisiones bala/escenario
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i){
		
		if(collision_mngr.bullet_collision(*(*i), *level))
			(*i)->set_state(Actor::ERASE);
		
	}

	// Colisiones bala/enemy abuela/enemy
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end(); ++i){
		if((*i)->get_owner() == Bullet::GRANNY){
			for(list<Enemy*>::iterator j = enemy_list.begin(); j != enemy_list.end(); ++j){
				if((*i)->get_state() != Actor::ERASE && on_screen(*(*j)) && collision_mngr.actor_collision(*(*i), *(*j)) && (*j)->get_state() != Actor::DAMAGED && (*j)->get_state() != Actor::ERASE){
					(*j)->damaged(/*(*i)->get_force()*/);
					(*i)->collides(*(*j));
				}
			}
		}
		
		else{
			if((*i)->get_state() != Actor::ERASE && collision_mngr.actor_collision(*(*i), *granny) && granny->get_state() != Actor::DAMAGED && granny->get_state() != Actor::ERASE){
				granny->damaged((*i)->get_force());
				(*i)->collides(*granny);
			}
		}
	}
}

void Game::delete_actors()
{
	bool stop = false;
	
	// Comprobamos los enemigos
	for(list<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end() && !stop; ++i){
		if((*i)->get_state() == Actor::ERASE){
			delete (*i);
			enemy_list.erase(i);
			stop = true;
		}
	}
			
	stop = false;
	
	// Comprobamos los items
	for(list<Item*>::iterator i = item_list.begin(); i != item_list.end() && !stop; ++i){
		if((*i)->get_state() == Actor::ERASE){
			delete (*i);
			item_list.erase(i);
			stop = true;
		}
	}
	
	stop = false;
	
	// Comprobamos las balas
	for(list<Bullet*>::iterator i = bullet_list.begin(); i != bullet_list.end() && !stop; ++i){
		if((*i)->get_state() == Actor::ERASE){
			delete (*i);
			bullet_list.erase(i);
			stop = true;
		}
	}
}

void Game::check_end()
{
	SceneMngr::Signal signal = SceneMngr::SCENE_COMPLETED;
	bool end_scene = false;
	
	// Si queremos volver al menu
	if(keyboard->newpressed(Keyboard::KEY_EXIT)){
		signal = SceneMngr::PAUSE_TO_MENU;
		end_scene = true;
	}
		
	// Si la abuela ha muerto
	if(granny->get_state() == Actor::ERASE){
		// Si no tiene más vidas
		if(granny->get_lives() == 0){
			signal = SceneMngr::GAME_OVER;
			end_scene = true;
		}
		// Si le quedan más vidas
		else{
			signal = SceneMngr::DEATH;
			end_scene = true;
		}
	}
	
	// Si estamos en una pelea final
	if(boss_fight){
		// Si hemos eliminado a todos los enemigos
		if(enemy_list.size() == 0){
			granny->epic_win();
			SDL_Delay(3000);
			signal = SceneMngr::SCENE_COMPLETED;
			end_scene = true;
		}
		
		// No podemos pasar más allá del final del nivel
		if(granny->get_x() + granny->get_real_dimensions().x + granny->get_real_dimensions().w  + 200>= level->get_width() * level->get_tile_width()){
			granny->move(level->get_width() * level->get_tile_width() - granny->get_real_dimensions().x - granny->get_real_dimensions().w  - 210, granny->get_y());
		}
	}
	else{
		// Si hemos llegado al final del nivel
		if(granny->get_x() + granny->get_real_dimensions().x + granny->get_real_dimensions().w  + 200>= level->get_width() * level->get_tile_width()){
			granny->epic_win();
			SDL_Delay(3000);
			signal = SceneMngr::SCENE_COMPLETED;
			end_scene = true;
		}
	}
	
	if(end_scene)
		scene_mngr->end_scene(signal);
}
