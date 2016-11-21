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

#ifndef _FONT_
#define _FONT_

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//! Clase para cargar y dibujar fuentes ttf personalizadas

/**
	@author David Saltares Márquez
	@version 1.0

	Permite cargar de disco fuentes ttf a un tamaño determinado y dibujar cadenas de texto en un color dado.
	Es posible establecer el alineamiento horizontal con respecto a la superficie sobre la que se dibuja.
	
	Ejemplo:
	\code
		Font matter("matteroffact.ttf", 60);
		Font hand("handsean.ttf", 30);
	
		matter.draw(pantalla, "Granny's Bloodbath", rojo, 40, Font::CENTER);
		hand.draw(pantalla, "El plataformas de acción de la abuela y los zombies", blanco, 110, Font::CENTER);
	
		cout << "Ancho de Granny's Bloodbath: " << matter.text_width("Granny's Bloodbath") << endl;
		cout << "Alto de Granny's Bloodbath: " << matter.text_height("Granny's Bloodbath") << endl;
		cout << "Salto de línea de matteroffact: " << matter.line_skip() << endl; 
	
		SDL_Flip(pantalla);
	\endcode
*/
class Font{
	public:
		
		/**
			Sirve para determinar el alineamiento horizontal deseado a la hora de dibujar
		*/
		enum Alignment{LEFT, RIGHT, CENTER};
		
		/**
			Constructor
			
			Carga de disco una fuente ttf a un tamaño determinado
			
			@param path ruta de la fuente a cargar
			@size tamaño en puntos de la fuente
		*/
		Font(const char* path, int size = 20);
		
		/**
			Destructor
			
			Libera la memoria ocupada por la fuente
		*/
		~Font();
		
		/**
			Dibuja la cadena de texto en el color dado en la superficie indicada
			
			@param screen superficie sobre la que se dibujará la cadena
			@param text texto a dibujar
			@param color color del texto
			@param x coordenadas en el eje x donde se dibujará (en píxeles)
			@param y coordenadas en el eje y donde se dibujará (en píxeles)
		*/
		void draw(SDL_Surface* screen, const std::string& text, SDL_Color color, int x, int y);
		
		/**
			Dibuja la cadena de texto en el color dado en la superficie indicada con alineamiento
			
			@param screen superficie sobre la que se dibujará la cadena
			@param text texto a dibujar
			@param color color del texto
			@param y coordenadas en el eje y donde se dibujará (en píxeles)
			@param alignment alineamiento de la cadena a dibujar
		*/
		void draw(SDL_Surface* screen, const std::string& text, SDL_Color color, int y, Alignment alignment);
		
		/**
			Consultor
			
			@return tamaño de la fuente en puntos
		*/
		int get_size() const;
		
		/**
			Consultor
			
			@param texto del que se quiere conocer su ancho
			@return ancho que ocuparía el texto al ser dibujado (en píxeles)
		*/
		int text_width(const std::string& text) const;
		
		/**
			Consultor
			
			@param texto del que se quiere conocer su alto
			@return alto que ocuparía el texto al ser dibujado (en píxeles)
		*/
		int text_height(const std::string& text) const;
		
		/**
			Consultor
			
			@return salto de línea recomendado
		*/
		int line_skip() const;
	private:
		TTF_Font* font;
		int size_;
		SDL_Surface* surface;
};

inline int Font::get_size() const {return size_;}
inline int Font::line_skip() const {return TTF_FontLineSkip(font);}

#endif
