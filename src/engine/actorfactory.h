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

#ifndef _ACTORFACTORY_
#define _ACTORFACTORY_

#include "actor.h"

class Zombie;
class Dog;
class Fat;
class Spider;
class Boss;
class Bullet;
class Item;
class Game;

//! Carga y cachea todos los actores

/**
	@author José Jesús Marente Florín
	@version 1.0
	
	Se utiliza para cargar los actores y minimizar el consumo de memoria y el número de accesos a disco.
	Cuando queremos algun actor de un tipo lo obtenemos mendiate su metodo determinado.
*/
class ActorFactory{
	public:
		/*
			Constructor
			
			@param game Puntero a Game con el que se asocia el actor
		*/
		ActorFactory(Game *game);
		
		/*
			Destructor
			
			Libera recursos
		*/
		~ActorFactory();
		
		/*
			@param x posicion x en la que se cargara el zombie
			@param y posicion y en la que se cargara el zombie
			@return Puntero a zombie
		*/
		Zombie* get_zombie(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el fat
			@param y posicion y en la que se cargara el fat
			@return Puntero a fat
		*/
		Fat* get_fat(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el dog
			@param y posicion y en la que se cargara el dog
			@return Puntero a dog
		*/
		Dog* get_dog(int x, int y);
		
		/*
			@param x posicion x en la que se cargara spider
			@param y posicion y en la que se cargara spider
			@return Puntero a spider
		*/
		Spider* get_spider(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el boss
			@param y posicion y en la que se cargara el boss
			@return Puntero a boss
		*/
		Boss* get_boss(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el pill
			@param y posicion y en la que se cargara el pill
			@return Puntero a pill
		*/
		Item* get_pill(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el teeth
			@param y posicion y en la que se cargara el teeth
			@return Puntero a teeth
		*/
		Item* get_teeth(int x, int y);
		
		/*
			@param x posicion x en la que se cargara el ammo
			@param y posicion y en la que se cargara el ammo
			@return Puntero a ammo
		*/
		Item* get_ammo(int x, int y);
	private:
		ActorFactory(const ActorFactory &a);
		ActorFactory& operator = (const ActorFactory& m);
		
		Zombie *zombie;
		Fat* fat;
		Dog* dog;
		Spider* spider;
		Boss* boss;
		Item* pill;
		Item* teeth;
		Item* ammo;
		
		Game* g;
};

#endif
