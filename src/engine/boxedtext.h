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

#ifndef _BOXEDTEXT_
#define _BOXEDTEXT_

#include <string>
#include <SDL/SDL.h>
#include "font.h"

//! Clase que se encarga de renderizar texto en un SDL_Rect de forma que no se salga del mismo

/**
	@author David Saltares Márquez
	@version 1.0
	
	Clase que almacena un texto y se encarga de renderizarlo dentro de unos límites.
	No es necesario introducir saltos de línea ya que la clase se encarga de colocarlos donde sean necesarios.
	Esta clase se utiliza para mostrar el texto con la historia en las escenas tipo Story
*/
class BoxedText{
	public:
		/**
			Constructor
			
			@param font Fuente con la que se renderizará el texto
			@param color Color del texto
			@param box Caja que representa la posición y los límites del texto
			@param text Texto a renderizar
		*/
		BoxedText(Font* font, SDL_Color color, SDL_Rect box, const std::string& text = "");
		
		/**
			Destructor
			
			Libera los recursos ocupados por el objecto BoxedText
		*/
		~BoxedText();
		
		/**
			@param screen Superficie donde se renderizará el texto
			
			Renderiza el texto en la superficie dada con sus propiedades (texto, color, caja y fuente)
		*/
		void draw(SDL_Surface* screen);
		
		/**
			Consultor
			
			@return Caja que limita al texto
		*/
		SDL_Rect get_rect() const;
		
		/**
			Consultor
			
			@return Color del texto
		*/
		SDL_Color get_color() const;
		
		/**
			Consultor
			
			@return Texto almacenado
		*/
		const std::string& get_text() const;
		
		/**
			 @param rect Nuevo rectángulo que limitará al texto
		*/
		void set_rect(SDL_Rect rect);
		
		/**
			@param color Nuevo color del texto
		*/
		void set_color(SDL_Color color);
		
		/**
			@param font Nueva Fuente que usará el texto
		*/
		void set_font(Font* font);
		
		/**
			@param text Nuevo texto a dibujar
		*/
		void set_text(const std::string& text);
	
	private:
		bool changed;
		bool first_time;
		Font* font_;
		SDL_Color color_;
		SDL_Rect rect_;
		std::string text_;
		SDL_Surface* rendered_text;
};

inline SDL_Rect BoxedText::get_rect() const {return rect_;}
inline SDL_Color BoxedText::get_color() const {return color_;}
inline const std::string& BoxedText::get_text() const {return text_;}


#endif
