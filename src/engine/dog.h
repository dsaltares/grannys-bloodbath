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

#ifndef _DOG_
#define _DOG_

#include "game.h"
#include "enemy.h"

//! Clase encargada de controlar el comportamiento del perro

/**	
	@author José Jesús Marente Florín
	@version 1.0
	
*/

class Dog: public Enemy{
	public:
		/**
		Constructor 
		
		@param g Puntero a Game con el que se asocia el perro
		*/
		Dog(Game *g);
		/**
			Constructor
			
			@param g Puntero a Game con el que se asocia el perro
			@param path ruta del fichero que contiene las distintas caracteristicas del personaje
			@param x coordenada x del personaje
			@param y coordenada y del personaje
		*/
		Dog(Game *g, const char *p, int x, int y);
		/**
			Destructor
			
			Liberamos recursos usados por el perro.			
		*/
		virtual ~Dog();
		/**
			Actualiza lógicamente al perro
		*/
		void update();
		
		/**			
			@param x Coordenada en el eje x del nuevo clon
			@param y Coordenada en el eje y del nuevo clon
			
			@return Clon del perro en una posición dada
		*/
		Actor* clone(int x1, int y1);
		
		/**			
			@param a Actor con el que colisiona
			
			Hace que el perro reaccione a la colisión (restar vida, añadir objeto...)
		*/
		void collides(Actor& a);
	private:
		void normal_state();
		void moving_state();
		void damaged_state();
		void death_state();	
		void jumping_state();
	
};

#endif
