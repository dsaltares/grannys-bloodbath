#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "music.h"
#include "logger.h"

using namespace std;

Music::Music(const char *path){

	music_=Mix_LoadMUS(path);

	if(music_==NULL){
		logger->error("Music::Music(): Error al cargar la música");
		exit(1);
	}

}

Music::~Music(){
	Mix_FreeMusic(music_);
}

void Music::play(int loop){

	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else{
		if(Mix_PlayMusic(music_, loop) == -1){
			logger->error("Error en Music::play()");
			exit(1);
		}
	}
}

void Music::fadein(int ms, int loop){
	if(Mix_FadeInMusic(music_, loop, ms) == -1){
		logger->error("Error en Music::fadein()");
		exit(1);
	}
}

void Music::fadeout(int ms){
	if(Mix_FadeOutMusic(ms)==-1){
		logger->error("Error en Music::fadeout()");
		exit(1);
	}
}
