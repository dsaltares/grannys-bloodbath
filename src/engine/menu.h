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

#ifndef _MENU_
#define _MENU_

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <vector>
#include "font.h"
#include "music.h"
#include "sound.h"
#include "scene.h"
#include "image.h"
#include "option.h"

//! Gestiona y carga el menu, con sus distintas opciones

/**
	@author Manuel Jesús de la Calle Brihuega
	@version 1.0
	
	Se utiliza para cargar las distintas opciones del Menú del juego, así como de pintarlo con todo su multimedia. Las opciones y el multimedia podemos modificarlo a nuestro gusto en el XML.
	
*/

class Menu: public Scene{

	public:

		Menu( SceneMngr* sm , const char* path );
		~Menu();
		void update();
		void reset();
		void resume();
		void draw(SDL_Surface* screen);
	private:
		unsigned int selected;
		std::vector <Option *> options;
		Font* font;
		int x_, y_;
		Font *aux;
		Music* music;
		Sound* select_sound;
		Sound* move_sound;
		Image* background;
		Image* cursor;
		std::string background_code, cursor_code, font_code, music_code, select_code, move_code;
};

#endif
