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

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include <pspkernel.h>
#include <pspctrl.h>
#include <valarray>
#include <map>

//! Gestiona el teclado, consultamos teclas pulsadas

/**
	@author David Saltares Marquez
	@version 1.0
	
	Clase que sigue el patron de diseno Singleton (una sola instancia accesible
	desde todo el sistema).
	Lleva el control de que teclas estan pulsadas en un momento determinado,
	cuales se sueltan y cuales se vuelven a presionar.
	
	Ejemplo de uso
	
	\code
		// Game loop
		while(!quit){
			keyboard->update() // Equivalente a Keyboard::get_instance()->update();
			
			if(keyboard->pressed(Keyboard::KEY_UP)) // Si pulsamos arriba
				...
			if(keyboard->released(Keyboard::KEY_HIT)) // Si dejamos de pulsar golpear
				...
			if(keyboard->newpressed(Keyboard::KEY_SHOOT)) // Si antes soltamos y
								      // ahora pulsamos disparar
		}
	\endcode
*/
class Keyboard{
	public:
		
		/**
			Controles del teclado utilizados en el juego
		*/
		enum keys{
			KEY_UP,
			KEY_DOWN,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_SHOOT,
			KEY_HIT,
			KEY_KNEEL,
			KEY_EXIT,
			KEY_ENTER
		};
		
		/**
			@return Si es la primera vez que se usa Keyboard crea su instancia y
			la devuelve. Sino simplemente la devuelve.
		*/
		static Keyboard* get_instance(){
			/* Si es la primera vez que necesitamos Keyboard, lo creamos */
			if(_instance == 0)
				_instance = new Keyboard;
			return _instance;
		}
		
		/**
			Actualiza el estado del teclado. Debe llamarse una vez al comienzo
			del game loop.
		*/
		void update();
		
		/**
			@param key Tecla a consultar
			
			@return true si la tecla esta pulsada, false en caso contrario.
		*/
		bool pressed(keys key);
		
		/**
			@param key Tecla a consultar
			
			@return true si la tecla estaba antes pulsada en la ultima actualizacion
			y ahora no lo esta, false en caso contrario.
		*/
		bool released(keys key);
		
		/**
			@param key Tecla a consultar
			
			@return true si la tecla no estaba pulsada en la ultima actualizacion y
			ahora lo esta, false en caso contrario.
		*/
		bool newpressed(keys key);
		
		/**
			@return true si se ha producido algun evento de salida, false en caso
			contrario
		*/
		bool quit();

		void set_quit() {_quit = true;}
		
	protected:
		Keyboard();
		~Keyboard();
		Keyboard(const Keyboard& k);
		Keyboard& operator = (const Keyboard& k);
	private:
		static Keyboard* _instance;
		std::valarray<bool> actual_keyboard;
		std::valarray<bool> old_keyboard;
		bool _quit;
		std::map<keys, PspCtrlButtons> configured_keys;
		SceCtrlData buttonInput;
		int n_keys;
};

#define keyboard Keyboard::get_instance()

#endif
