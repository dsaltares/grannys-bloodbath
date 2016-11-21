#include <iostream>
#include <algorithm>
#include "keyboard.h"

using namespace std;

Keyboard* Keyboard::_instance = 0;

Keyboard::Keyboard()
{
	/* Configuracion predeterminada */
	configured_keys[KEY_UP] = PSP_CTRL_UP;
	configured_keys[KEY_DOWN] = PSP_CTRL_DOWN;
	configured_keys[KEY_LEFT] = PSP_CTRL_LEFT;
	configured_keys[KEY_RIGHT] = PSP_CTRL_RIGHT;
	configured_keys[KEY_HIT] = PSP_CTRL_CROSS;
	configured_keys[KEY_SHOOT] = PSP_CTRL_CIRCLE;
	configured_keys[KEY_EXIT] = PSP_CTRL_SELECT;
	configured_keys[KEY_ENTER] = PSP_CTRL_START;
	
	/* Inicializamos el estado del teclado */
	n_keys = configured_keys.size();
	actual_keyboard.resize(n_keys);
	old_keyboard.resize(n_keys);
	
	for(int i = 0; i < n_keys; ++i){
		actual_keyboard[false];
		old_keyboard[false];
	}
	
	_quit = false;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

Keyboard::~Keyboard()
{
}

		
void Keyboard::update()
{	
	/* Ahora el teclado nuevo es el viejo */
	old_keyboard = actual_keyboard;

	/* Actualizamos el estado de la entrada PSP */
	sceCtrlPeekBufferPositive(&buttonInput, 1); 
	
	/* Actualizamos el estado del teclado */
	for(map<keys, PspCtrlButtons>::iterator i = configured_keys.begin();
		i != configured_keys.end(); ++i)
			actual_keyboard[i->first] = (buttonInput.Buttons & i->second)?
							actual_keyboard[i->first] = true :
								actual_keyboard[i->first] = false;
}
		
bool Keyboard::pressed(keys key)
{
	/* Devolvemos si la tecla indicada esta pulsada */
	return actual_keyboard[key];
}
				
bool Keyboard::released(keys key)
{
	/* Comprobamos si la tecla indicada no esta pulsada y antes si */
	return (!actual_keyboard[key] && old_keyboard[key]);
}
		
bool Keyboard::newpressed(keys key)
{
	/* Comprobamos si la tecla indicada esta pulsada y antes no */
	return (actual_keyboard[key] && !old_keyboard[key]);
}

bool Keyboard::quit()
{
	return _quit;
}
		

