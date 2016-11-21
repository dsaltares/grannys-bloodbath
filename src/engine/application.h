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

#ifndef _APPLICATION_
#define _APPLICATION_

#include <SDL/SDL.h>
#include "fpsmngr.h"

class SceneMngr;

//!Clase encargada de iniciar y cerrar SDL. Tiene el bucle principal

/**
	@author José Jesús Marente Florín
	@version 1.0

	Se encarga de inicializar la SDL, cerrarla e ir cargando cada escena. Tambien contiene el bucle principal del juego

	Ejemplo:
	\code
		#include "application.h"
		
		int main(){
			Application app("Configuracion.xml");
			app.run();
			return 0;
		}
	\endcode
*/
class Application{
	public:	
		/**
			Constructor

			@param path ruta del fichero que contiene la configuración
		*/
		Application( const char* path );
		
		/**
			Destructor

			Cierra SDL y libera recursos usados.
		*/
		~Application();
		
		/**
			Encargado de actualizar el juego.
		*/
		void run();
		
		/**
		 *	    @return ancho en píxeles de la pantalla
		 */
		int get_screen_width() const;
		
		/**
		 *	    @return alto en píxeles de la pantalla
		 */
		int get_screen_height() const;
	private:
		SDL_Surface* screen;
		int screen_w,screen_h,bpp,fps;
		FPSMngr fps_mngr;
		SceneMngr* scene_mngr;
		SDL_Surface* SDL_Setup();
};


inline int Application::get_screen_width() const {return screen_w;}
inline int Application::get_screen_height() const {return screen_h;}

/**
	@mainpage Granny's Bloodbath
	
	
	
	<strong><center><h2>David Saltares Márquez</h2></center>
	<center><h2>Jose Marente Florín</h2></center>
	<center><h2>Manuel de la Calle Brihuega</h2></center>
	<center><h3>Web del proyecto: http://granysbloodbath.wordpress.com</h3></center></strong>
	
	<center><img src=grannysbloodbath.png/></center>
	
	<h3>Introducción</h3>
	
	Granny's Bloodbath es un plataformas de acción en 2D de avance lateral. Está programado en C++ usando las librerías SDL y ticpp.
	
	<h3>Descarga y compilación</h3>
	
	Para descargar el código fuente de Granny's Bloodbath hay que entrar en una terminal y ejecutar:
	
	svn checkout https://forja.rediris.es/svn/grannysbloodbath
	
	(Es necesario tener Subversion instalado)
	
	Para poder compilar Granny's Bloodbath se debe tener instalados los siguientes paquetes:
	
	\li libsdl1.2-dev
	\li libsdl-image1.2-dev
	\li libsdl-ttf1.2-dev
	\li libsdl-mixer1.2-dev
	
	Posteriormente habrá que entrar en el directorio /grannysbloodbath/trunk/src y hacer make
*/

#endif
