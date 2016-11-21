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

#ifndef _MUSIC_
#define _MUSIC_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

//!Carga y reproduce musica

/**
	@author José Jesús Marente Florín
	@version 1.0;

	Esta clase se encarga de cargar musica/canciones y reproducirlos

	Ejemplo:
	\code
		Music musica("prueba.ogg");

		while(!keyboard->quit()){
			keyboard->update();
			if(keyboard->newpressed(Keyboard::KEY_UP))
				musica.play();	
			else if(keyboard->newpressed(Keyboard::KEY_DOWN))
				musica.pause();
	\endcode
*/
class Music{
	public:
		/**
			Constructor
			
			Carga en memoria la canción
			
			@param path ruta de la cancion
		*/
		Music(const char *path);
		/**
			Destructor

			Libera la memoria ocupada por la cancion		
		*/
		~Music();
		/**
			Reproduce la canción		
			
			@param loop número de bucles (-1 para bucle infinito)
		*/
		void play(int loop = -1);
		/**
			Pausa la canción		
		*/
		void pause();
		/**
			Detiene la canción		
		*/
		void stop();
		/**
			Reproduce la canción con un fadein de unos milisegundos dados
		
			@param ms milisegundo de la duracion del fadein	
			@param loop número de bucles (-1 para bucle infinito)
		*/
		void fadein(int ms, int loop = -1);
		/**
			Detiene la canción con un fadeout de unos milisegundos dados
		
			@param ms milisegundo de la duracion del fadeout	
		*/
		void fadeout(int ms);
		
		/**
			@return true si hay música sonando, false en caso contrario
		*/
		bool playing() const;
	private:
		Mix_Music *music_;
};

inline void Music::pause(){
	Mix_PauseMusic();
}

inline void Music::stop(){
	Mix_HaltMusic();
}

inline bool Music::playing() const {return (Mix_PlayingMusic())? true : false;}

#endif
