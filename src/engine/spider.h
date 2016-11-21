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

#ifndef _SPIDER_
#define _SPIDER_

#include "enemy.h"

//! Clase encargada de controlar el comportamiento de la araña

/**	
	@author José Jesús Marente Florín
	@version 1.0
	
*/

class Game;
class Bullet;
class Sound;

class Spider:public Enemy{
	public:
		/**
		Constructor 
		
		@param g Puntero a Game con el que se asocia con la araña
		*/
		Spider(Game *g);
		
		/**
			Constructor
			
			@param g Puntero a Game con el que se asocia la araña
			@param path ruta del fichero que contiene las distintas caracteristicas del personaje
			@param x coordenada x del personaje
			@param y coordenada y del personaje
		*/
		Spider(Game *g, const char *path, int x, int y);
		
		/**
			Destructor
			
			Liberamos recursos usados por el personaje.			
		*/
		~Spider();
		
		/**
			Actualiza lógicamente al personaje
		*/
		void update();
		
		/**			
			@param x Coordenada en el eje x del nuevo clon
			@param y Coordenada en el eje y del nuevo clon
			
			@return Clon del zombie gordo en una posición dada
		*/
		Actor *clone(int x, int y);
		
		/**			
			@param a Actor con el que colisiona
			
			Hace que el zombie reaccione a la colisión (restar vida, añadir objeto...)
		*/
		void collides(Actor &a);
	private:
		Bullet *bullet;
		int vx2, actual_vx;
		
		Sound* attack;
		std::string attack_code;
		
		int shoot_delay, actual_shoot_delay;
		
		void shoot_spiderweb();
		
		bool within_range();
		
		void normal_state();
		void jumping_state();
		void moving_state();
		void attack_state();
		void attackTOnormal_state();
		void damaged_state();
		void death_state();
	
};

#endif
