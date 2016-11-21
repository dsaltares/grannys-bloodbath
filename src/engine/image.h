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

#ifndef _IMAGE_
#define _IMAGE_

#include <string>
#include <SDL/SDL.h>

//!Carga y muestra imagenes

/**
	@author David Saltares Márquez y José Jesús Marente Florín
	@version 1.0

	Esta clase se encarga de cargar imagenes en memoria y mostrar un frame determinado de ellas.
	Los frames se enumeran de la siguiente forma:
			-Por ejemplo en la fila 1, columna 1, estara el frame 1, en la fila 1 columna 2, el frame 2, y asi sucesivamente.

	Ejemplo:
	\code
		//Inicializa SDL...

		Image abuela("granny.png",8,12);
		//mostramos el frame 5 de la imagen de la abuela
		abuela.draw(screen,5,100,100);
	\endcode
*/

class Image{
	public:
		/**
			Constructor
		
			Carga en memoria la imagen

			@param path ruta donde se encuentra la imagen
			@param rows numero de filas de la imagen por defecto 1
			@param columns numero de columnas de la imagen por defecto 1
		*/
		Image(const char *path, int rows = 1, int columns = 1);
		/**
			Destructor
		
			Libera de la memoria la imagen cargada
		*/
		~Image();
		/**
			Muestra la imagen sobre una superficie dada
	
			@param screen superficie de destino donde queremos mostrar la imagen
			@param f el frame de la imagen que queremos mostrar
			@param x eje x de la superficie de destino donde se mostrara la imagen
			@param y eje y de la superficie de destino donde se mostrara la imagen
			@param flip determina si queremos mostrar la imagen reflejada o no, por defecto no(false)
		*/
		void draw(SDL_Surface *screen, int f, int x, int y, bool flip = false);
		/**
			Metodo consultor

			@return ancho de un frame de la imagen
		*/
		int width() const;
		/**
			Metodo consultor

			@return alto de un frame de la imagen
		*/
		int height() const;
		/**
			Metodo consultor

			@return número de frames que tiene la imagen
		*/
		int frames() const;
		/**
			Metodo consultor

			@return número de filas de la imagen
		*/
		int rows() const;
		/**
			Metodo consultor

			@return número de columnas de la imagen
		*/
		int columns() const;
		
		/**
			Método consultor
			
			@param Coordenada en el eje x
			@param Coordenada en el eje y
			@return Color del píxel indicado	
		*/
		Uint32 get_pixel(int x, int y) const;
	private:
		enum colors {R, G, B};
		
		SDL_Surface * reverse_image(SDL_Surface *image);
		SDL_Surface *normal_image;
		SDL_Surface *inverted_image;
		int columns_, rows_, height_, width_;
};

inline int Image::width() const {return width_;}
inline int Image::height() const {return height_;}
inline int Image::rows() const {return rows_;}
inline int Image::columns() const {return columns_;}
inline int Image::frames() const {return rows_* columns_;}

#endif
