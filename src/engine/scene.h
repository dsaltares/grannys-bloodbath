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

#ifndef _SCENE_
#define _SCENE_

#include "SDL/SDL.h"

class SceneMngr;

//! Clase virtual pura para tratar todos los tipos de escenas de la misma manera

/**
	@author José Jesús Marente Florín
	@version 1.0

	Esta clase se utiliza para tratar en la clase que controla todas las escenas(SceneMngr) de manera uniforme
*/

class Scene{
	public:
		/**
			Controles de los distintos tipos de escenas que trataremos en el juego
		*/
		enum Scenes{MENU, GAME, STORY, CREDITS, BOSS};

		/**
			Constructor
			
			@param sm puntero al SceneMngr que pertence
		*/
		Scene( SceneMngr* sm );
		/**
			Destructor
		*/
		virtual ~Scene() {}
		/**
			Metodo virtual puro

			Mirar función correspondiente en la clase de una escena concreta para mas información
		*/
		virtual void update() = 0;
		/**
			Metodo virtual puro

			Mirar función correspondiente en la clase de una escena concreta para mas información
		*/
		virtual void reset() = 0;
		
		/**
		 *	Método virtual puro
		 * 
		 * 	Función a llamar cuando se vuelve a activar una escena (reproducción de músicas etc)
		 */
		virtual void resume() = 0;
		/**
			Metodo virtual puro

			Mirar función correspondiente en la clase de una escena concreta para mas información
		*/
		virtual void draw(SDL_Surface* screen) = 0;
	protected:
		SceneMngr* scene_mngr;
};



#endif
