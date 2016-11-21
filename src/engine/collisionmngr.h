#ifndef _COLLISIONMNGR_
#define _COLLISIONMNGR_

#include <vector>
#include "actor.h"
#include "level.h"

//! Clase para gestionar colisiones entre actores y con el escenario

/**
	@author David Saltares Márquez
	@version 1.0
	
	Esta clase se utiliza para detectar y gestionar colisiones tanto actor-actor como actor-nivel.
	
	CollisionMngr se encarga de corregir propiedades de los actores relacionadas con el movimiento (posición, velocidad...) para que dejen de colisionar.
	La entidad que llame a los métodos de CollisionMngr es la responsable de cambiar otras propiedades como items, vida o eliminar a alguno de los que colisionan.
	
	Ejemplo de uso:
	\code
	void Game::update()
	{
		abuela->update();
		update_enemies();
		update_items();
		
		...
		
		// Colisiones escenario-abuela
		collision_mngr.level_collision(*abuela, *level);
		
		// Colisiones abuela-enemigo
		// para cada enemigo:
		for(list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i){
			if(collision_mngr.actor_collision(*abuela, *level)){
				if(abuela->state == Actor::HIT)
					(*i)->collides(*abuela);
				else
					abuela->collides(*(*i));
			}
		}
		
		...
	}
	\endcode
*/
class CollisionMngr{
	public:
		/**
			Detecta colisiones entre actores
			
			@param a1 Actor del que se quieren conocer sus colisiones
			@param actor2 Actor con el que se quieren consultar las colisiones
			
			@return true si el actor 1 colisiona con el actor 2, false en caso contrario
		*/
		bool actor_collision(Actor& a1, Actor& a2) const;
		
		/**
			Detecta colisiones actor-nivel y corrige la posición y estado del actor
			
			@param actor Actor del que se quieren conocer sus colisiones
			@param level Nivel con el que se quiere saber la colisión
		*/
		bool level_collision(Actor& actor, Level& level);
		
		/**
		 * 	Detecta si un actor esta tocando el suelo
		 * 
		 * 	@param actor del que se quiere saber si toca el suelo
		 * 	@param level escenario que se quiere consultar
		 * 	@param x coordenada en el eje x en la que se quiere comprobar la colisión
		 * 	@param y coordenada en el eje y en la que se quiere comprobar la colisión
		 * 	@return true si al actor toca el suelo, false en caso contrario
		 */
		bool on_ground(const Actor& actor, const Level& level, int x, int y) const;
		
		/**
			Detecta colisiones bala-nivel
			
			@param actor Bala del que se quieren conocer sus colisiones
			@param level Nivel con el que se quiere saber la colisión
		*/
		bool bullet_collision(const Actor& bullet, Level& level) const;
	private:
		bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const;
		bool collision_hor(int x, int y, Uint16 w, Uint16 h, int& tilecoordy, const Level& level, bool up) const;
		bool collision_ver(int x, int y, Uint16 w, Uint16 h, int& tilecoordx, const Level& level, bool right) const;
};

#endif
