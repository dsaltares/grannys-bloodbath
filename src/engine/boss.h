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

#ifndef _BOSS_
#define _BOSS_

#include "enemy.h"

//! Clase encargada de controlar el comportamiento del Boss

/**	
	@author David Saltares Márquez
	@version 1.0
	
*/

class Game;
class Bullet;
class Sound;

class Boss:public Enemy{
	public:
		/**
			Constructor 
			
			@param g Puntero a Game con el que se asocia con el Boss
		*/
		Boss(Game *g);
		
		/**
			Constructor
			
			@param g Puntero a Game con el que se asocia el Boss
			@param path ruta del fichero que contiene las distintas caracteristicas del personaje
			@param x coordenada x del personaje
			@param y coordenada y del personaje
		*/
		Boss(Game *g, const char *path, int x, int y);
		
		/**
			Destructor
			
			Liberamos recursos usados por el personaje.			
		*/
		~Boss();
		
		/**
			Actualiza lógicamente al personaje
		*/
		void update();
		
		/**			
			@param x Coordenada en el eje x del nuevo clon
			@param y Coordenada en el eje y del nuevo clon
			
			@return Clon del Boss en una posición dada
		*/
		Actor *clone(int x, int y);
		
		/**			
			@param a Actor con el que colisiona
			
			Hace que el Boss reaccione a la colisión (restar vida, añadir objeto...)
		*/
		void collides(Actor &a);
	private:
		Bullet *bullet;
		
		Sound* attack;
		std::string attack_code;
		
		int shoot_delay, actual_shoot_delay;
		
		void spit();
		
		bool within_range(int x, int y);
		
		void normal_state();
		void jumping_state();
		void moving_state();
		void attack_state();
		void spit_state();
		void spit_to_normal_state();
		void damaged_state();
		void death_state();
};

#endif
