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

#ifndef _STORY_
#define _STORY_

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include "scenemngr.h"
#include "scene.h"

class Image;
class Music;
class Font;
class BoxedText;

//! Clase virtual pura para tratar todos los tipos de escenas de la misma manera

/**
	@author José Jesús Marente Florín
	@version 1.0

	Esta clase se utiliza para tratar en la clase que controla todas las escenas(SceneMngr) de manera uniforme

*/

class Story: public Scene{
	public:
		/**
			Constructor
			
			@param sm puntero al SceneMngr que pertence
		*/
		Story( SceneMngr* sm , const char* path );
		/**
			Destructor
		*/
		~Story();
		/**
			Metodo

			Comprueba el estado de la escena
		*/
		void update();
		/**
			Metodo
 
			Detiene Musica/Narrador, y hace que comiencen de nuevo
		*/
		void reset();
		/**
		 *	Función a llamar cuando se vuelve a activar una escena story (vuelve a comenzar el narrador)
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
		std::string FontCode;
		Image *image;
		Music *narrator;
		Font *font;
		BoxedText* boxedtext;
		SDL_Color ColorText;
		SDL_Rect PositionText;
		std::string text;
};

#endif
