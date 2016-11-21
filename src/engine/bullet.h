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

#ifndef _BULLET_
#define _BULLET_

#include <string>
#include "game.h"
#include "image.h"
#include "actor.h"

//! Clase encarga del comportamiento de la bala

/**
 	@author José Jesús Marente Florín
 	@version 1.0
 	
 	Bullet hereda de la clase virtual pura Actor.
	
	
*/
class Bullet: public Actor{
	public:
	
		//! Señales para indicar quien es el actor que dispara
		enum Owner{GRANNY, FAT, BOSS};
		
		/**
			Constructor
			
			@param g Puntero a Game con el que se asocia la bala
		*/
		Bullet(Game *g);

		/**
			Constructor
			
			@param g Puntero a Game con el que se asocia la bala
			@param path ruta del fichero de configuración de la bala
			@param x coordenada del eje x de la bala
			@param y coordenada del eje y de la bala
			@param direction dirección de la bala 
			@param o actor que dispara la bala.
		*/
		Bullet(Game *g, const char* path, int x, int y, bool direction, Owner o);
		
		/**
			Destructor
		*/
		~Bullet();
		
		/**
			Actualiza lógicamente la bala
		*/
		void update();
		
		/**			
			@param x Coordenada en el eje x del nuevo clon
			@param y Coordenada en el eje y del nuevo clon
			
			@return Clon del actor en una posición dada
		*/
		Actor* clone(int x, int y);
		
		/**			
			@param a Actor con el que colisiona
			
			Hace que el bala raccione a la colision
		*/
		void collides(Actor& a);
		
		/**
			@return Fuerza de ataque que tiene el enemigo
		*/
		int get_force() const;
		
		/**
			@param f nuevo valor para la fuerza del ataque del enemigo
		*/
		void set_force(int f);
		
		/**
			@return Actor que a disparado la bala.
		*/
		Owner get_owner()const;
	private:
		int force;
		Owner owner;
};

inline int Bullet::get_force()const{ return force; }
inline void Bullet::set_force(int f){ force = f; }
inline Bullet::Owner Bullet::get_owner()const{ return owner; }

#endif
