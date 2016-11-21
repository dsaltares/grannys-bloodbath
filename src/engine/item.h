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

#ifndef _ITEM_
#define _ITEM_

#include "actor.h"

class Game;

//! Clase que modela los objetos recolectables del juego

/**
 *	@author David Saltares Márquez
 * 	@version 1.0
 * 
 * 	Agrupa a los objetos que se pueden recoger en el juego. Contiene sus tipos y proporciona una forma de tratarlos de manera común.
 */

class Item: public Actor{
	public:
		/**
		 *	Distintos tipos de Item
		 */
		enum ItemType{TEETH, PILLS, AMMO};
		
		/**
			Constructor 
		
			@param g Puntero a Game con el que se asocia el actor
		*/
		Item(Game *g);
		
		/**
		 *	Constructor
		 * 
		 * 	@param game puntero al objeto que controla el juego
		 * 	@param path ruta con la información del item en XML
		 * 	@param x coordenada inicial en el eje x del item
		 * 	@param y coordenada inicial en el eje y del item
		 */
		Item(Game* game, const char* path, int x, int y);
		
		/**
		 * 	Destructor
		 * 
		 * 	Libera la memoria ocupada por el ítem
		 */
		~Item();
		
		/**
		 * 	Actualiza lógicamente el ítem
		 */
		void update(void);
		
		/**
		 *	Función a llamar cuando Granny colisiona con el ítem.
		 * 	Marca a Ítem para ser borrado.
		 * 
		 * 	@param a Actor con el que colisiona
		 */
		void collides(Actor& a);
		
		/**
		 * 	@param x Coordenada en el eje x del nuevo item
		 * 	@param y Coordenada en el eje y del nuevo item
		 * 
		 * 	@return Crea un nuevo item copia del primero (salvo por la posición) y devuelve un puntero
		 */
		Item* clone(int x, int y);
		
		ItemType get_type() const;
	private:
		ItemType type;
};

#endif
