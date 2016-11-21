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

#ifndef _GAMEGRANNY_
#define _GAMEGRANNY_

#include <list>
#include <string>
#include "story.h"
#include "collisionmngr.h"
#include "level.h"

class SceneMngr;
class Granny;
class Enemy;
class Item;
class Bullet;
class Music;

//! Clase que lleva el control de una escena de juego

/**
 * 	@author David Saltares Márquez
 * 	@version 1.0
 * 	
 * 	Clase que crea un nivel de juego y controla a todos los actores que intervienen en él. Es la clase principal para el juego.
 * 	SceneMngr es el encargado (leyendo el guión del juego) de lanzar una escena tipo Game con un nivel determinado.
 * 	Simplemente llamando a sus métodos update y draw se va actualizando.
 * 	Cuando se llega al final del nivel, se produce la muerte del personaje o algún evento similar Game avisa a su SceneMngr para que actúe en consecuencia.
 */

class Game: public Scene{
	public:
		/**
		 * 	Constructor
		 * 	@param sm SceneMngr que controla a la escena Game
		 * 	@param path Ruta del fichero XML con el nivel a cargar
		 * 	@param boos_fight true si estamos en una pelea con un jefe final, false si es un nivel normal.
		 * 	Esto afecta a la manera de terminar el nivel:
		 * 	- Escena normal: llegar al final del nivel.
		 * 	- Boss Fight: eliminar a todos los enemigos.
		 */
		Game(SceneMngr* sm, const char* path, bool boss_fight = false);
		
		/**
		 * 	Destructor
		 * 	
		 * 	Libera todos los recursos ocupados por la escena de juego
		 */
		~Game();
		
		/**
		 *	Actualiza lógicamente la escena de juego (mueve actores, hace scrolling, detecta y responde a las colisiones...)
		 */
		void update();
		
		/**
		 *	Resetea la escena de juego
		 */
		void reset();
		
		/**
		 *	Vuelve a la escena de juego (activa la bso)
		 */
		void resume();
		
		/**
		 * 	Dibuja en pantalla un frame de la escena
		 * 
		 * 	@param screen Superficie donde se bliteará la escena
		 */
		void draw(SDL_Surface* screen);
		
		/**
		 *	Añade un Item a la escena de juego.
		 * 	Esta función la utilizará el constructor de Level para establecer los actores iniciales bajo el control de Game
		 * 	
		 * 	@param item Item a añadir (se añadirá el item en su posición)
		 */
		void add_item(Item* item);
		
		/**
		 * 	Añade un Enemy a la escena de juego.
		 * 	Esta función la utilizará el constructor de Level para establecer los actores iniciales bajo el control de Game
		 * 	
		 * 	@param enemy Enemy a añadir (se añadirá el item en su posición) 	
		 */
		void add_enemy(Enemy* enemy);
		
		/**
		 * 	Añade la abuelita bajo el control del juego
		 * 
		 * 	@param abuelita que se añade (debe estar creada y sólo añadirse una vez cada vez que se crea Game)
		 */
		void add_granny(Granny* granny);
		
		/**
		 * 	Añade una bala a la escena del juego
		 * 
		 * 	@param bala que se añade
		 */
		void add_bullet(Bullet* bullet);
		
		/**
		 * 	Establece la música que debe sonar durante el juego
		 * 
		 * 	@param music Música a reproducir
		 * 
		 * 	Esta función debería llamarla Level en su constructor
		 */
		void set_music(const std::string& music_code);
		
		/**
		 * 	Detecta si un actor esta tocando el suelo
		 * 
		 * 	@param actor actor del que se quiere saber si toca el suelo
		 * 	@param level escenario que se quiere consultar
		 * 	@param x coordenada en el eje x en la que se quiere comprobar la colisión
		 * 	@param y coordenada en el eje y en la que se quiere comprobar la colisión
		 * 	@return true si al actor toca el suelo, false en caso contrario
		 */
		bool on_ground(const Actor& actor, int x, int y) const;
		
		/**
		 * 	Detecta si un actor está en pantalla
		 * 
		 * 	@param actor actor del que se quiere saber si está en pantalla
		 * 	@return true si el actor está en pantalla, false en caso contrario
		 */
		bool on_screen(const Actor& actor) const;
		
		/**
		 * 	@return Scroll en el eje x del nivel
		 */
		int level_x() const;
		
		/**
		 * 	@return Scroll en el eje y del nivel
		 */
		int level_y() const;
		
		const Granny* get_granny();
	private:
		Level* level;
		Music* music;
		std::string music_code;
		std::string level_path;
		CollisionMngr collision_mngr;
		Granny* granny;
		std::list<Enemy*> enemy_list;
		std::list<Item*> item_list;
		std::list<Bullet*> bullet_list;
		bool boss_fight;
		
		void check_collisions();
		void delete_actors();			
		void check_end();
}; 

inline int Game::level_x() const {return (level)? level->get_x() : 0;}
inline int Game::level_y() const {return (level)? level->get_y() : 0;}
inline const Granny* Game::get_granny(){ return granny; }
#endif
