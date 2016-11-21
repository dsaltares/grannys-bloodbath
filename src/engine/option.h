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

#ifndef _OPTION_
#define _OPTION_

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include "font.h"

//! Opción de la escena Menu

/**
	@author Manuel Jesús de la Calle Brihuega
	@version 1.0
	
	Se utiliza para crear una opción del menú del juego, y posteriormente poder pintarla y gestionarla.
	En el menú cargaremos varias opciones, por lo que esta clase nos abstraerá bastante el trabajo.
	
*/

class Option{

	public:
		Option(const std::string& text, Font* font, int x, int y, SDL_Color sel, SDL_Color nosel): text_(text), font_(font), x_(x), y_(y), selected_col(sel), nselected_col(nosel){};
		void draw(SDL_Surface* screen, bool selected = false);
		int get_x() const;
		int get_y() const;		
		const std::string& get_text() const;
	
	private:
		std::string text_;
		Font* font_;
		int x_, y_;
		SDL_Color selected_col, nselected_col;
};

inline int Option::get_x() const {return x_;}
inline int Option::get_y() const {return y_;}
inline const std::string& Option::get_text() const {return text_;}



#endif
