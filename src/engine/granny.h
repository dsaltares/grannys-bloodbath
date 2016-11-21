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

#ifndef _GRANNY_
#define _GRANNY_

#include <iostream>
#include <string>
#include <vector>
#include "actor.h"
#include "hud.h"

class Game;
class Sound;
class Bullet;
class Item;

//! Clase que modela el comportamiento y las características de la abuelita protagonista

/**
	@author José Jesús Marente Florín
	@version 1.0
	
	Granny hereda de la clase virtual pura Actor y define los métodos update entre otros para darle comportamiento a la abuela
	Su uso es muy sencillo:
	
	\code
		// Game loop
		while(!exit){
			...
			
			granny->update(); // Actualizamos lógicamente a la abuela
			
			...
			
			granny->draw(screen); // Dibumamos a la abuela en pantalla
			
			...
			
			granny->set_state(Actor::NORMAL); // Si lo deseamos podemos cambiar su estado
		}
	\endcode
*/
	
class Granny: public Actor{
	public:
		/**
			Constructor
			
			@param game Puntero a Game con el que se asocia el actor
			@param path ruta del fichero que contiene las distintas caracteristicas del personaje
			@param x coordenada x del personaje
			@param y coordenada y del personaje
		*/
		Granny(Game *g, const char *path, int x, int y);
		/**
			Destructor
			
			Liberamos recursos usados por el personaje.			
		*/
		~Granny();
		/**
			Actualiza lógicamente al personaje
		*/
		void update();
		
		/**
		 *	Resetea a la abuela (State = NORMAL vida al máximo)
		 */
		void reset();
		
		/**			
			@param a Actor con el que colisiona
			
			Hace que el actor reaccione a la colisión (restar vida, añadir objeto...)
		*/
		void collides(Actor& a);
		
		/**
		 *	@param i Daño inflingido a la abuela
		 * 
		 * 	Le resta vida a la abuela
		 */
		void damaged(int i);
		
		/**
		 *	@param i Item que recoge la abuela
		 * 
		 * 	Según el ítem reacciona la abuela
		 */
		void get_item(const Item& i);
		
		/**			
			@return devuelve el numero de vidas actual
		*/
		int get_lives() const;
		/**			
			@param nuevo numero de vidas
			
			Establece un nuevo numero de vidas
		*/		
		void add_lives(int l);
		/**			
			@return numero de puntos actuales.
		*/		
		int get_points() const;
		/**			
			@param numero de puntos actuales.
			
			Establece un nuevo numero de puntos
		*/		
		void add_points(int p);
		/**			
			@return municion restante que tiene el personaje.
		*/		
		int get_munition() const;
		/**			
			@param m numero para incrementar la municion..
		*/
		void add_munition(int m);
		/**			
			@return energia restante del personaje.
		*/		
		int get_energy() const;
		/**			
			@param e valor para incrementar la energua.
		*/
		void add_energy(int e);
		/**
			@param Superficie donde se dibujará el actor
			
			Dibuja al personaje en la superficie dada según su posición y animación actuales
		*/
		void draw(SDL_Surface* screen);
		
		/**
			Reproduce el sonido de victoria de la abuela
		*/
		void epic_win();
	private:
		HUD *hud_;
		int lifes, points, munition, energy, max_energy;
		int y0;
		
		Sound* attack;
		Sound* shoot;
		Sound* win;
		Sound* jump;
		std::string attack_code, shoot_code, win_code, jump_code;
		std::vector<std::pair<Sound*, std::string> > hurt_sounds;
		
		void Normal_State();
		void NormalDown_State();
		void Moving_State();
		void Jumping_State();
		void Kneeled_State();
		void Rising_State();
		void Attaking_State();
		void Damaged_State();
		void Dead_State();
		
		void shoot_gun();
		
		Bullet* bullet;

};

inline int Granny::get_lives() const { return lifes; }	
inline void Granny::add_lives(int l) { lifes+=l; }

inline int Granny::get_points() const { return points; }
inline void Granny::add_points(int p) { points+=p; }
		
inline int Granny::get_munition() const { return munition; }
inline void Granny::add_munition(int m) { munition+=m; }
		
inline int Granny::get_energy() const { return energy; }
inline void Granny::add_energy(int e) { (energy + e >= max_energy)? energy = max_energy : energy += e; }

#endif
