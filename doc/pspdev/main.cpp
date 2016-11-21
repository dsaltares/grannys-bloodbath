#include <pspkernel.h>
#include "engine/application.h"
#include "engine/keyboard.h"

int exit_callback(int arg1, int arg2, void *common) {
	/* Codigo para cerrar correctamente nuestro sistema */
	keyboard->set_quit();
	return 0;
}

int CallbackThread(SceSize args, void *argp) {
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int SetupCallbacks(void) {
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 
		0x11, 0xFA0, 0, 0);
	if(thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}

/* Necesario para no tener problemas con C++ */
extern "C" int SDL_main (int argc, char* args[]); 

int main(int argc, char *argv[])
{
	/* Preparamos los callbacks */
	SetupCallbacks();
	
	/* Lanzamos nuestro sistema */
	Application app("XML/configuration.xml");

	app.run();
	
	/* Volvemos al sistema operativo */
	sceKernelExitGame();
	
	return 0;	
}

