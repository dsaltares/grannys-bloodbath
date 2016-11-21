#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include "specialscene.h"
#include "scenemngr.h"
#include "resourcemngr.h"
#include "image.h"
#include "music.h"
#include "parser.h"
#include "keyboard.h"

using namespace std;

SpecialScene::SpecialScene(SceneMngr* sm, const char* path): Scene(sm)
{
	Parser parser(path);
	
	ImageCode = parser.get_attribute("image", parser.find("specialscene"));
	MusicCode = parser.get_attribute("music", parser.find("specialscene"));
	
	image = resource->image(ImageCode);
	music = resource->music(MusicCode);
	
	music->fadein(1000);
}

SpecialScene::~SpecialScene()
{
	resource->free_image(ImageCode);
	resource->free_music(MusicCode);
	
	image = NULL;
	music = NULL;
}

void SpecialScene::update()
{	
	//Si se ha pulsado la tecla para pasar la escena
	if(keyboard->newpressed(Keyboard::KEY_EXIT)){
		music->stop();
		scene_mngr->end_scene(SceneMngr::END_AND_GO_TO_MENU);
	}
}

void SpecialScene::reset()
{
	music->stop();
	music->fadein(1000);
}

void SpecialScene::resume()
{
	reset();
}

void SpecialScene::draw(SDL_Surface* screen)
{
	image->draw(screen, 0, 0, 0);
}


