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

#ifndef _HUD_
#define _HUD_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"
#include "font.h"

//!Actualiza y muestra el estado de la abuela

/**
	@author José Jesús Marente Florín
	@version 1.0

	Esta clase se encarga de actualizar el estado actual de la abuela y mostralo por pantalla.

	Ejemplo:
	\code

		void Granny::update(){
			...
			...
			hud.update(lifes,points,munition,energy);
		}

		void Granny::draw(SDL_Surface *Screen){
			...
			...
			hud.draw(screen);
		}

	\endcode
*/

class HUD{
	public:
		/**
				Constructor

				Carga e inicializa los distinos recursos necesarios

				@param path Ruta del archivo donde se encuentra la configuración deseada.
				@param e energía máxima que podra tener la abuela.
		*/
		HUD(const char *path, int e);
		
		/**
			Destructor

			Libera los distintos recursos cargados.
		*/
		~HUD();
		
		/**
			Se encarga de actualizar el estado actual de la abuela
			
			@param l vidas actuales de la abuela
			@param p puntos actuales de la abuela
			@param m munición actual de la abuela
			@param e energía actual de la abuela.
		*/
		void update(int l, int p, int m, int e);
		
		/**
			Método encargado de dibujar el hud sobre la imagen dada

			@param screen superficie destino del hud.
		*/
		void draw(SDL_Surface* screen);
	private:
		SDL_Surface *bar;
		Image *hud;
		Font *font;
		std::string points, lifes, munition, image_code, font_code;
		SDL_Rect hud_destiny, bar_destiny;//, munition_destiny, lifes_destiny, points_destiny;
		SDL_Color color;
		int max_energy, energy, lifesx, lifesy, munitionx, munitiony, pointsx, pointsy;
};

#endif
