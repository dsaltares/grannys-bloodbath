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

#ifndef _SPECIALSCENE_
#define _SPECIALSCENE_

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include "scenemngr.h"
#include "scene.h"

//!Clase para manejar escenas especiales (Game Over, Créditos)

/**
	@author Manuel Jesús de la Calle Brihuega y David Saltares Márquez
	@version 1.0

	Esta clase se utiliza para crear las escenas de game over y de créditos del juego.

*/

class Image;
class Music;

class SpecialScene: public Scene{
	public:
		/**
			Constructor
			
			@param sm puntero al SceneMngr que pertence
			@param path ruta al fichero xml con la configuración de la escena
		*/
		SpecialScene(SceneMngr* sm, const char* path);
		
		/**
			Destructor
		*/
		~SpecialScene();
	
		/**
			Actualiza de manera lógica la escena
		*/
		void update();
		
		/**
			Detiene Musica, y hace que comience de nuevo
		*/
		void reset();
		
		/**
		 *	Vuelve a la escena tras una pausa
		 */
		void resume();
		
		/**
			Metodo

			Se encarga de pintar sobre la superficie dada, todo los componentes de la escena
		*/    
		void draw(SDL_Surface* screen);
	private:
		std::string ImageCode;
		std::string MusicCode;
		Image *image;
		Music *music;
};

#endif
