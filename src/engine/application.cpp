#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <cstring>
#include "application.h"
#include "scenemngr.h"
#include "keyboard.h"
#include "logger.h"
#include "parser.h"
#include "font.h"
#include "resourcemngr.h"


using namespace std;

Application::Application( const char* path )
{
	Parser parser(path);

	parser.get_attribute("ancho", parser.find("pantalla"), &screen_w);
	parser.get_attribute("alto", parser.find("pantalla"), &screen_h);
	parser.get_attribute("bpp", parser.find("pantalla"), &bpp);
	parser.get_attribute("valor", parser.find("fps"), &fps);

	fps_mngr.set_fps(fps);

	screen = SDL_Setup();
	
	scene_mngr = new SceneMngr(this, "./XML/plot.xml");
}

Application::~Application(){
	delete scene_mngr;
	ResourceMngr::free_instance();
	SDL_Quit();
}

void Application::run(){

	Font* fps = resource->font("hand");
	char buffer[30];
	SDL_Color blanco;
	
	blanco.r = 255;
	blanco.g = 255;
	blanco.b = 255;

	while(!keyboard->quit()){
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		
		keyboard->update();

		scene_mngr->update();		
		scene_mngr->draw(screen);

		sprintf(buffer, "%d fps", fps_mngr.get_fps());
		fps->draw(screen, buffer, blanco, 510, Font::RIGHT);
		
		SDL_Flip(screen);

		fps_mngr.fps_control();
	}
}

SDL_Surface *Application::SDL_Setup(){

	SDL_Surface* screenaux;
	SDL_Surface* icon;


	if(SDL_Init(0) < 0){
		logger->error("En Application::SDL_Setup(): no se puedo iniciar");
		exit(1);
	}

	atexit(SDL_Quit);
		
	screenaux = SDL_SetVideoMode(screen_w, screen_h, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(screenaux == NULL){
		logger->error("En Application::SDL_Setup(): error al establecer modo de video");
		exit(1);
	}
	
	SDL_WM_SetCaption("Granny's BloodBath BETA - v0.1", NULL);
	
	if((icon = SDL_LoadBMP("icon.bmp")) != NULL){
		SDL_WM_SetIcon(icon,NULL);
	}

	SDL_ShowCursor(SDL_DISABLE);

	if(TTF_Init() == -1){
		logger->error("En Application::SDL_Setup(): no se pueod iniciar TTF");
		exit(1);
	}

	atexit(TTF_Quit);
	
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0){
		logger->error("En Application::SDL_Setup(): subsistema de audio");
		exit(1);
	}

	atexit(Mix_CloseAudio);
	
	srand(time(NULL));

	return screenaux;
}
