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

#ifndef _RESOURCEMNGR_
#define _RESOURCEMNGR_

#include <map>
#include <string>

#include "image.h"
#include "font.h"
#include "music.h"
#include "sound.h"

//! Carga y cachea todos los recursos multimedia

/**
	@author David Saltares Márquez
	@version 1.0
	
	Clase que sigue el patrón de diseño Singleton (una sóla instancia accesible desde todo el sistema).
	Se utiliza para cargar los recursos multimedia y minimizar el consumo de memoria y el número de accesos a disco.
	Cuando queremos recursos de algún tipo simplente accedemos mediante su clave.
	ResourceMngr guarda el número de referencias que existen de un recurso en el sistema. Cuando dejemos de usar un recurso debemos de avisarle de que no lo usaremos más. Este manejador se encarga de liberarlo definivamente si era la última referencia al recurso.
	Si queremos volver a cargar el recurso liberado quizás haya que volver a hacer un acceso a disco.
	
	Carga un fichero XML llamado "./multimedia/resources.xml" con el siguiente formato
	\code
		<resources>
			<images>
				<image code="granny" path="./multimedia/granny.png" rows="8" columns="12"/>
			</images>
			<fonts>
				<font code="matter" path="./multimedia/matteroffact.ttf" size="50"/>
				<font code="hand" path="./multimedia/handsean.ttf" size="20"/>
			</fonts>
			<musics>
				<music code="nivel" path="./multimedia/prueba.ogg"/>
			</musics>
			<sounds>
				<sound code="vomito" path="./multimedia/vomito.wav"/>
			</sounds>
		</resources>
	\endcode
	
	Ejemplo de uso:
	\code
		Music* music = resource->music("nivel"); // Equivalente a ResourceMngr::get_instance()->music("nivel");
		Sound* sound = resource->sound("vomito");
		Font* font1  = resource->font("matter");
		Font* font2 = resource->font("hand");
		Image* image = resource->image("granny");
		
		...
		
		// Cuando no los usemos más
		resource->free_image("granny");
		resource->free_music("nivel");
		resource->free_sound("vomito");
		resource->free_font("matter");
		resource->free_font("hand");
	\endcode
*/
class ResourceMngr{
	public:
		
		
		/**
			@return Si es la primera vez que se utiliza ResourceMngr se crea la única instancia que habrá de la clase en el sistema. En caso contrario simplemente la devuelve
		*/
		static ResourceMngr* get_instance(){
			if(_instance == 0)
				_instance = new ResourceMngr;
			return _instance;
		}
		
		static void free_instance();
		
		/**
			@param code Clave de la imagen a encontrar
			@return puntero a Image con la imagen deseada
		*/
		Image* image(const std::string& code);
		
		/**
			@param code Clave de la fuente a encontrar
			@return puntero a Font con la fuente deseada
		*/
		Font* font(const std::string& code);
		
		/**
			@param code Clave del efecto de sonido a encontrar
			@return puntero a Sound con el sonido deseado
		*/
		Sound* sound(const std::string& code);
		
		/**
			@param code Clave de la música a encontrar
			@return puntero a Music con la música deseada
		*/
		Music* music(const std::string& code);
		
		/**
			@param code Clave de la imagen a liberar
			
			Avisa a ResourceMngr del cese del uso de ese recurso. Si no existen más referencias a ese recurso, se libera definitivamente. La próxima vez que se le pida ResourceMngr tendrá que hacer un acceso a disco.
		*/
		void free_image(const std::string& code);
		
		/**
			@param code Clave de la fuente a liberar
			
			Avisa a ResourceMngr del cese del uso de ese recurso. Si no existen más referencias a ese recurso, se libera definitivamente. La próxima vez que se le pida ResourceMngr tendrá que hacer un acceso a disco.
		*/
		void free_font(const std::string& code);
		
		/**
			@param code Clave de la música a liberar
			
			Avisa a ResourceMngr del cese del uso de ese recurso. Si no existen más referencias a ese recurso, se libera definitivamente. La próxima vez que se le pida ResourceMngr tendrá que hacer un acceso a disco.
		*/
		void free_music(const std::string& code);
		
		/**
			@param code Clave del efecto de sonido a liberar
			
			Avisa a ResourceMngr del cese del uso de ese recurso. Si no existen más referencias a ese recurso, se libera definitivamente. La próxima vez que se le pida ResourceMngr tendrá que hacer un acceso a disco.
		*/
		void free_sound(const std::string& code);
		
	protected:
		ResourceMngr();
		ResourceMngr(const ResourceMngr& m);
		~ResourceMngr();
		ResourceMngr& operator = (const ResourceMngr& m);
		
	private:
		
		//! Maneja un recurso de imagen
		struct ImageMngr{
			std::string path;
			int rows, columns;
			Image* image;
			int counter;
		};
		
		//! Maneja un recurso de fuente
		struct FontMngr{
			std::string path;
			int size;
			Font* font;
			int counter;
		};
		
		//! Maneja un recurso de sonido
		struct SoundMngr{
			std::string path;
			Sound* sound;
			int counter;
		};
		
		//! Maneja un recurso de música
		struct MusicMngr{
			std::string path;
			Music* music;
			int counter;
		};
		
		typedef std::map<std::string, ImageMngr> Images;
		typedef std::map<std::string, FontMngr> Fonts;
		typedef std::map<std::string, SoundMngr> Sounds;
		typedef std::map<std::string, MusicMngr> Musics;
		 
		static ResourceMngr* _instance;
		
		Images images;
		Fonts fonts;
		Sounds sounds;
		Musics musics;
};

#define resource ResourceMngr::get_instance()

#endif
