#include <iostream>
#include <algorithm>
#include "keyboard.h"

using namespace std;

Keyboard* Keyboard::_instance = 0;

Keyboard::Keyboard()
{
	/* Configuración predeterminada */
	configured_keys[KEY_UP] = SDLK_UP;
	configured_keys[KEY_DOWN] = SDLK_DOWN;
	configured_keys[KEY_LEFT] = SDLK_LEFT;
	configured_keys[KEY_RIGHT] = SDLK_RIGHT;
	configured_keys[KEY_HIT] = SDLK_a;
	configured_keys[KEY_SHOOT] = SDLK_s;
	configured_keys[KEY_EXIT] = SDLK_ESCAPE;
	configured_keys[KEY_ACCEPT] = SDLK_SPACE;
	
	/* Inicializamos el estado del teclado */
	n_keys = configured_keys.size();
	actual_keyboard.resize(n_keys);
	old_keyboard.resize(n_keys);
	
	for(int i = 0; i < n_keys; ++i){
		actual_keyboard[false];
		old_keyboard[false];
	}
	
	_quit = false;
}

Keyboard::~Keyboard()
{
}

		
void Keyboard::update()
{
	static SDL_Event event;
	
	/* Ahora el teclado nuevo es el viejo */
	old_keyboard = actual_keyboard;
	
	/* Sacamos los eventos de la cola y mapeamos el estado del teclado actual */
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			_quit = true;
		else if(event.type == SDL_KEYDOWN){
			for(map<keys, SDLKey>::iterator i = configured_keys.begin(); i != configured_keys.end(); ++i){
				if(event.key.keysym.sym == i->second){
					actual_keyboard[i->first] = true;
				}
			}
		}
		else if(event.type == SDL_KEYUP){
			for(map<keys, SDLKey>::iterator i = configured_keys.begin(); i != configured_keys.end(); ++i){
				if(event.key.keysym.sym == i->second){
					actual_keyboard[i->first] = false;
				}
			}
		}
	}
}
		
bool Keyboard::pressed(keys key)
{
	/* Devolvemos si la tecla indicada está pulsada */
	return actual_keyboard[key];
}
				
bool Keyboard::released(keys key)
{
	/* Comprobamos si la tecla indicada no está pulsada y antes sí */
	return (!actual_keyboard[key] && old_keyboard[key]);
}
		
bool Keyboard::newpressed(keys key)
{
	/* Comprobamos si la tecla indicada está pulsada y antes no */
	return (actual_keyboard[key] && !old_keyboard[key]);
}

bool Keyboard::quit()
{
	return _quit;
}
		
void Keyboard::set_quit()
{
	_quit = true;
}
