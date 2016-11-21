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

#ifndef _LEVEL_
#define _LEVEL_

#include <string>
#include <map>
#include "image.h"
#include "actorfactory.h"

class Game;

/**
	Tipos de tiles que puede haber
	<ul>
		<li>PASSABLE: se puede atravesar</li>
		<li>NONPASSABLE: no se puede atravesar</li>
		<li>PLATFORM: se puede atravesar pero nos podemos montar encima</li>
	</ul>
*/
enum TileType{PASSABLE = 0, NONPASSABLE, PLATFORM};

//! Estructura que guarda la información de un tile del escenario

/**
	@author David Saltares Márquez
	@version 1.0
	
	Estructura que guarda el frame (para poder dibujarlo) del tileset que representa ese tile y su tipo (utilizado para las colisiones)
	
*/
struct Tile{
	/**
		frame del tileset que representa
	*/
	int frame;
	
	/**
		tipo de tile
	*/
	TileType type;
};


//! Clase para manejar los escenarios del juego

/**
	@author David Saltares Márquez
	@version 1.0
	
	Clase que nos permite cargar, actualizar y dibujar escenarios creados en formato XML con la herramienta Tiled.
	Al construirse crea el mapa, carga el tileset y coloca a todos los actores en el escenario
	
	Para construir un nivel compatible con Granny's Bloodbath debe usar Tiled siguiendo el manual que se proporciona para ello.
	
	Ejemplo de uso:
	\code
	// Inicialización
	Level level = new Level("level.tmx", screen);
	
	...
	
	// Game loop
	while(!salir){

		...
		
		// Actualizamos lógicamente a los actores
		
		...
		
		// Movemos la cámara del nivel
		
		level.move(x, y);
		
		// Dibujamos las capas del nivel
		level.draw(screen, 0);
		level.draw(screen, 1);
		dibujar_actores();
		level.draw(screen, 2); // Capa que queda por encima
		
		if(level.get_x() >= ...){
			// Hemos llegado al final del nivel
		}
	}
	\endcode
	
*/
class Level{
	public:
		/**
			Constructor
			
			@param game Objeto Game con el que se asocia el nivel
			@param path Ruta donde está la información del nivel
		*/
		Level(Game* game, const char* path);
		
		/**
			Destructor
			
			Libera los recursos ocupados por nivel
		*/
		~Level();
		
		/**
			@param screen Superficie donde se dibujará el nivel
			@param layer Capa del nivel a dibujar
			
			Dibuja la capa indicada en la superficie dada
		*/
		void draw(SDL_Surface* screen, int layer);
		
		/**
			Consultor
			
			@return Coordenada en el eje x del nivel (scroll) En píxeles
		*/
		int get_x() const;
		
		/**
			Consultor
			
			@return Coordenada en el eje y del nivel (scroll) En píxeles
		*/
		int get_y() const;
		
		/**
			@param x Nueva coordenada en el eje x del nivel (scroll) En píxeles
			@param y Nueva coordenada en el eje y del nivel (scroll) En píxeles
		*/
		void move(int x, int y);
		
		/**
			@param x Coordenada en el eje x a consultar En tiles
			@param y Coordenada en el eje y a consultar En tiles
		*/
		Tile get_tile(int x, int y, int layer) const;
		
		/**
			Consultor
			
			@return Ancho del nivel en tiles
		*/
		int get_width() const;
		
		/**
			Consultor
			
			@return Alto del nivel en tiles
		*/
		int get_height() const;
		
		/**
			Consultor
			
			@return Ancho de un tile en píxeles
		*/
		int get_tile_width() const;
		
		/**
			Consultor
			
			@return Alto de un tile en píxeles
		*/
		int get_tile_height() const;	
	private:
		
		void load_actors();
	
		Game* g;
		Tile ***level;
		Image* tileset;
		std::map<int, std::string> actors_map;
		int x, y, width, height, tile_height, tile_width;
		ActorFactory* actor_factory;
};


inline int Level::get_x() const {return x;}
inline int Level::get_y() const {return y;}
inline int Level::get_width() const {return width;}
inline int Level::get_height() const {return height;}
inline int Level::get_tile_width() const {return tile_height;}
inline int Level::get_tile_height() const {return tile_width;}

#endif
