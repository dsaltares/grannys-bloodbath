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

#ifndef _SOUND_
#define _SOUND_

#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

//! Carga y reproduce efectos de sonido

/**
	@author Manuel de la Calle Brihuega
	@version 1.0
	
	Esta clase se encarga de cargar en memoria efectos de sonido y reproducirlos.
	
	Ejemplo:
	\code
		Sound sonido("vomito.wav");
	
		cout << "Pulsa UP para reproducir" << endl;
	
		while(!keyboard->quit()){
			keyboard->update();
			if(keyboard->newpressed(Keyboard::KEY_UP))
				sonido.play();	
		}
	\endcode
*/
class Sound{
	public:
		/**
			Constructor
			
			Carga en memoria el efecto de sonido
			
			@param path ruta del efecto de sonido
		*/
		Sound(const char* path);
		
		/**
			Destructor
			
			Libera la memoria ocupada por el efecto
		*/
		~Sound();
		
		/**
			Reproduce el efecto de sonido una vez
		*/
		void play();
	private:
		Mix_Chunk *sound;

};


#endif
