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

#ifndef _ANIMATIONH_
#define _ANIMATIONH_

#include <iostream>
#include<vector>
//! Gestiona las animaciones de ina imagen

/**
	@author José Jesús Marente Florín
	@version 1.0;

	Clase sirve para gestionar las distintas animaciones que puede recoger un mismo sprite

	Ejemplo:
	\code
		Image abuelita("abuela.png");
		Animation AbuelitaAndar(1,31,1);
		Animation AbuelaAgachar("90,91,92,93,94,95,96,95,94,93,92,91,90",1);
		SDL_Event evento;
		for(;;){
			while(SDL_PollEvent(&evento)){
				if(evento.type==SDL_QUIT)
				return 0;
				else if(evento.type==SDL_KEYDOWN){
					if(evento.key.keysym.sym==SDLK_ESCAPE)
						return 0;
					if(evento.key.keysym.sym==SDLK_a){
						cout<<"Abuela en ejecucion. Espere..."<<endl;
						PintarAnimacion(abuela,AbuelaAndar);
						cout<<"Abuela termino su ejecucion. Pulse otra tecla..."<<endl;
					}
					if(evento.key.keysym.sym==SDLK_d){
						cout<<"Abuela agachandose. Espere..."<<endl;
						PintarAnimacion(abuela,AbuelaAgachar);
						cout<<"Abuela derecha. Pulse otra tecla..."<<endl;
					}
			}
		}
	}
	\endcode
*/

class Animation{
	public:
		/**
			Constructor

			Recibe la secuencia de la animacion junto con su retardo
			@param frms secuencia con el formato "a1,a2,...an"
			@param delay retardo para pasar de un frame a otro
		*/
		Animation(const char* frms, int delay);
		/**
			Constructor

			Recibe la secuencia de la animacion junto con su retardo
			@param begin frame/cuadro de inicio
			@param end frame/cuadro de fin 
			Si usamos 1 como begin y 4 como end es equivalente a usar el constructor anterior de la siguente forma Animation("1,2,3,4",...)
			@param delay retardo para pasar de un frame a otro
		*/
		Animation(int begin, int end, int delay);
		/**
			Reinicia la animacion
		*/
		void restart();
		/**
			Incrementa en 1 el contador que controla el retardo, si es igual pasa al siguiente cuadro
			Si termina y se continua vuelve a empezar
			@return Verdadero si se termina la animación, falso si no es así
		*/
		bool update();
		/**
			Establece el retardo
				
			@param newdelay valor que pasa a ser el nuevo retardo
		*/
		void set_delay(int newdelay);
		/**
			Metodo consultor
		
			@return valor que tiene el retardo actual
		*/
		int get_delay()const;
		/**
			Metodo consultor
		
			@return numeros de cuadros que posee la animación
		*/
		int get_frames()const;
		/**
			Metodo consultor
		
			@return cuadro actual en el que se encuentra la animación
		*/
		int get_frame()const;
	private:
		std::vector<int> frames;
		int delay,ActualFrame,CounterDelay,NumberFrames;
};

inline void Animation::restart(){ActualFrame=0;CounterDelay=0;}

inline void Animation::set_delay(int newdelay){delay=newdelay;}
inline int Animation::get_delay()const{return delay;}
inline int Animation::get_frames()const{return NumberFrames;}
inline int Animation::get_frame()const{return frames[ActualFrame];}

#endif
