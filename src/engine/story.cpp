#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include "story.h"
#include "scenemngr.h"
#include "resourcemngr.h"
#include "image.h"
#include "music.h"
#include "boxedtext.h"
#include "parser.h"
#include "keyboard.h"

using namespace std;

Story::Story( SceneMngr* sm , const char* path ):Scene(sm)
{
	Parser parser(path);
	
	int r,g,b;

	ImageCode = parser.get_attribute("code", parser.find("image"));
	MusicCode = parser.get_attribute("code", parser.find("music"));
	FontCode = parser.get_attribute("code", parser.find("text"));
	parser.get_attribute("r", parser.find("text"), &r);
	parser.get_attribute("g", parser.find("text"), &g);
	parser.get_attribute("b", parser.find("text"), &b);
	parser.get_attribute("x", parser.find("text"), &PositionText.x);
	parser.get_attribute("y", parser.find("text"), &PositionText.y);
	parser.get_attribute("w", parser.find("text"), &PositionText.w);
	parser.get_attribute("h", parser.find("text"), &PositionText.h);
	text = parser.get_content(parser.find("text"));
	
	ColorText.r = r;
	ColorText.g = g;
	ColorText.b = b;
	
	image = resource->image(ImageCode);
	narrator = resource->music(MusicCode);
	font = resource->font(FontCode);
	
	boxedtext = new BoxedText(font, ColorText, PositionText, text);
	
	narrator->fadein(1000, 1);
}

Story::~Story()
{
	delete boxedtext;
	resource->free_image(ImageCode);
	resource->free_music(MusicCode);
	resource->free_font(FontCode);
	image=NULL;
	narrator=NULL;
	font=NULL;
	boxedtext=NULL;
}

void Story::update()
{	
	if(keyboard->newpressed(Keyboard::KEY_EXIT) || !narrator->playing())
		scene_mngr->end_scene(SceneMngr::SCENE_COMPLETED);
}

void Story::reset()
{
	narrator->stop();
	narrator->fadein(1000, 1);
}

void Story::resume()
{
		narrator->stop();
		narrator->fadein(1000, 1);
}

void Story::draw(SDL_Surface* screen)
{
	image->draw(screen, 0, 0, 0);
	boxedtext->draw(screen);
}


