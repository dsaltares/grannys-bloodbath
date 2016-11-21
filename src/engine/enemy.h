/*
    This file is part of Granny's Bloodbath.

    Granny's Bloodbath is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Granny's Bloodbath is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Granny's Bloodbath.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _ENEMY_
#define _ENEMY_

#include "actor.h"
#include "game.h"

//! Clase virtual pura que abstrae las características básicas de los enemigos (zombie, dog, fat)

/**	
	@author José Jesús Marente Florín
	@version 1.0
	
	Es una clase que abstrae lo básico del comportamiento y las características de los enemigos.
*/

class Sound;

class Enemy: public Actor{
	public:
		/**
			Constructor
			@param g Puntero a la clase Game con la que se aosica el enemigo.
		 */
		Enemy(Game *g);
		
		~Enemy();
		
		/**
			@return Fuerza de ataque que tiene el enemigo
		*/
		int get_force()const;
		
		/**
			@param f nuevo valor para la fuerza del ataque del enemigo
		*/
		void set_force(int f);
		
		/**
			@return Energía actual del enemigo
		*/
		int get_energy()const;
		
		/**
			@param Nuevo valor para la energia del enemigo
		*/
		void set_energy(int e);
		
		/**
			Cambia la dirección del enemigo
		*/
		void change_direction();
		
		/**
			@return retraso entre ataque y ataque
		*/
		int get_attackdelay()const;
		
		/**
			@param e nuevo valor para el retraro entre ataque y ataque
		*/
		void set_attackdelay(int e);
		
		/**
			@return retraso actual entre ataque y ataque
		*/
		int get_actualdelay()const;
		
		/**
			@param e nuevo valor para el retraso actual entre ataque y ataque
		*/
		void set_actualdelay(int e);
		
		/**
		 *	Función para dañar al enemigo 
		 */
		void damaged();
	protected:
		bool in_view();
		Sound* hurt;
		std::string hurt_code;
		int energy, force, attack_delay, actual_delay;
};

inline int Enemy::get_force()const{ return force; }
inline void Enemy::set_force(int f){ force = f; }
inline int Enemy::get_energy()const{ return energy; }
inline void Enemy::set_energy(int e){ energy = e; }
inline int Enemy::get_attackdelay()const{ return attack_delay; }
inline void Enemy::set_attackdelay(int e){ attack_delay = e; }
inline int Enemy::get_actualdelay()const { return actual_delay; }
inline void Enemy::set_actualdelay(int e){ actual_delay = e; }

#endif
