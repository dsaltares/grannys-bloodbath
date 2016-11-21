#include <iostream>
#include <string>
#include "sound.h"

#include "logger.h"

using namespace std;

Sound::Sound(const char* path){
        if((sound = Mix_LoadWAV(path)) == NULL) {
		logger->error(string("Sound::Sound(): No se ha podido cargar el sonido ") + string(path));
		exit(1);
        }
}

Sound::~Sound(){
	Mix_FreeChunk(sound);
}

void Sound::play(){
	Mix_PlayChannel(-1, sound, 0);	
}
