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

#ifndef _ACTOR_
#define _ACTOR_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "image.h"
#include "animation.h"

class Game;
class Parser;

//! Clase virtual pura que abstrae las características básicas de los actores (abuela, enemigos, ítems etc)

/**
 	@author David Saltares Márquez
	@version 1.0
	
	Es una clase que abstrae lo básico del comportamiento y las características de los personajes (posición, estado, velocidad, animaciones, cajas de colisión...).
	No adjunto código de ejemplo ya que la clase es virtual pura.
*/
	
class Actor{
	public:	
		
		//! Tipos de actores
		enum Type{GRANNY, ENEMY, ITEM};
		
		
		//! Posibles estados en los que puede encontrarse el actor
		enum State{NORMAL, MOVE, ATTACK, JUMP, DAMAGED, KNEEL, DIE, ERASE, RISE, NORMALDOWN};
		
		//! Cada animación se asocia a un estado del personaje
		typedef std::map<State, Animation* > Animations;
		
		//! Conjunto de cajas de colisión, se asociará con un único estado del personaje
		typedef std::vector<SDL_Rect > Collision_Rects;
		
		//! Cajas de colisión asociadas a un estado del personaje
		typedef std::map<State, Collision_Rects > Collision_Map;

		/**
			Constructor
			
			@param game Puntero a Game con el que se asocia el actor
		*/
		Actor(Game* game);
		
		/**
		 *	Destructor
		 * 
		 * 	Libera la memoria ocupada por Actor
		 */
		virtual ~Actor();
		
		/**
			@return Posición en el eje x del actor
		*/
		int get_x() const;
		
		/**
			@return Posición en el eje y del actor
		*/
		int get_y() const;
		
		/**
			@return Posición en el eje x del actor en el frame anterior
		*/
		int get_old_x() const;
		
		/**
			@return Posición en el eje y del actor en el frame anterior
		*/
		int get_old_y() const;
		
		/**
			@return Velocidad en el eje x del actor
		*/
		int get_vx() const;
		
		/**
			@return Velocidad en el eje y del actor
		*/
		int get_vy() const;
		
		/**
			@return Estado actual del actor
		*/
		State get_state() const;
		
		/**
			@return Cajas de colisión del actor según su estado actual
		*/
		const Collision_Rects& get_rects() const;
		
		/**
			@return true el actor mira a la izquierda, false en caso contrario
		*/
		bool get_direction() const;
		
		/**
		 * 	@return Ancho de un frame del sprite en píxeles
		 */
		bool get_image_width() const;
		
		/**
		 * 	@return Alto de un frame del sprite en píxeles
		 */
		bool get_image_height() const;
		
		/**
			@return recuadro con las dimensiones reales de la abuela dentro de la rejilla
		*/
		SDL_Rect get_real_dimensions() const;
		
		/**
			@param x Nueva posición en el eje x
			@param y Nueva posición en el eje y
		*/
		void move(int x, int y);
		
		/**
			@param vx Nueva velocidad en el eje x
		*/
		void set_vx(int vx);
		
		/**
			@param vy Nueva velocidad en el eje y
		*/
		void set_vy(int vy);
		
		/**
			@param state Nuevo estado del actor
		*/
		void set_state(State state);
		
		/**
			@param direction Nueva dirección del actor (true -> izquierda, false -> derecha)
		*/
		void set_direction(bool direction);
		
		/**
			@param Superficie donde se dibujará el actor
			
			Dibuja el actor en la superficie dada según su posición y animación actuales
		*/
		void draw(SDL_Surface* screen);
		
		/**
			Virtual pura
			
			Actualiza lógicamente al personaje
		*/
		virtual void update() = 0;
		
		/**
			Virtual pura
			
			@param a Actor con el que colisiona
			
			Hace que el actor reaccione a la colisión (restar vida, añadir objeto...)
		*/
		virtual void collides(Actor& a) = 0;		
	protected:
		Game* g;
		int x, y, vx, vy, vx0, vy0, old_x, old_y;
		bool direction;
		Image* image;
		std::string image_code;
		std::map<State, SDL_Rect> real_dimensions;
		std::map<State, SDL_Rect> real_dimensions_inverted;
		Collision_Map collision_map;
		Collision_Map collision_map_inverted;
		Animations animations;
		State state, previous_state;
		Type type;
		
		void parse_basic_info(Parser& parser);
};

inline int Actor::get_x() const {return x;}
inline int Actor::get_y() const {return y;}
inline int Actor::get_old_x() const {return old_x;}
inline int Actor::get_old_y() const {return old_y;}
inline int Actor::get_vx() const {return vx;}
inline int Actor::get_vy() const {return vy;}
inline Actor::State Actor::get_state() const {return state;}
inline bool Actor::get_direction() const {return direction;}
inline bool Actor::get_image_width() const {return image->width();}
inline bool Actor::get_image_height() const {return image->height();}

#endif
