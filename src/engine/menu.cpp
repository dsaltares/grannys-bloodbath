#include <iostream>
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "resourcemngr.h"
#include "menu.h"
#include "scenemngr.h"
#include "font.h"
#include "image.h"
#include "music.h"
#include "option.h"
#include "parser.h"
#include "keyboard.h"

using namespace std;

Menu::Menu( SceneMngr* sm , const char* path ):Scene(sm)
{
	Parser parser(path);
	std::string texto, z;
	SDL_Color aux, aux2;
	int x=0,y=0, r, g, b, r1, g1, b1;
	selected = 0;
	
	
	background_code = parser.get_attribute("background", parser.root());
	cursor_code = parser.get_attribute("cursor", parser.root());
	music_code = parser.get_attribute("music", parser.root());
	font_code = parser.get_attribute("font", parser.root());
	move_code = parser.get_attribute("move", parser.root());
	select_code = parser.get_attribute("select", parser.root());	

	vector<ticpp::Element *> option;
	vector<ticpp::Element *>::iterator i;
	
	parser.find("option",option,parser.find("options"));
	font = resource->font(font_code);
	for(i = option.begin(); i != option.end(); ++i){
		parser.get_attribute("r", *i, &r);
		parser.get_attribute("g", *i, &g);
		parser.get_attribute("b", *i, &b);
		parser.get_attribute("r2", *i, &r1);
		parser.get_attribute("g2", *i, &g1);
		parser.get_attribute("b2", *i, &b1);
		parser.get_attribute("x", *i, &x);
		parser.get_attribute("y", *i, &y); 
		texto = parser.get_attribute("text",*i);
		
		aux.r=r;
		aux.g=g;
		aux.b=b;
		aux2.r=r1;
		aux2.g=g1;
		aux2.b=b1;
		
		options.push_back(new Option(texto, font, x, y, aux, aux2));
	}
	
	background = resource->image(background_code);
	move_sound = resource->sound(move_code);
	select_sound = resource->sound(select_code);
	music = resource->music(music_code);	
	cursor = resource->image(cursor_code);
	
	x_ = options[selected]->get_x() - cursor->width() - 100;
	y_ = options[selected]->get_y() + 10;
	
	music->fadein(1000);
}

Menu::~Menu()
{
	resource->free_image(background_code);
	resource->free_font(font_code);	
	resource->free_music(music_code);
	resource->free_image(cursor_code);
	resource->free_sound(select_code);
	resource->free_sound(move_code);	
	
	for(std::vector<Option*>::iterator i = options.begin(); i != options.end(); ++i)
		delete (*i);
			
	background = NULL;
	font = NULL;
	music = NULL;
	cursor = NULL;
	move_sound = NULL;
	select_sound = NULL;
}

void Menu::update()
{	

	if(keyboard->newpressed(Keyboard::KEY_DOWN)){
		move_sound->play();
		selected++;
		if(options.size() <= selected)
			selected = 0;
	}
	
	if(keyboard->newpressed(Keyboard::KEY_UP)){	
		move_sound->play();
		selected = (selected == 0)? options.size() - 1 : selected - 1;
	}
	
	if(keyboard->newpressed(Keyboard::KEY_ACCEPT)){
		
		select_sound->play();
		
		if(options[selected]->get_text() == "Jugar")
			scene_mngr->end_scene(SceneMngr::BACK_TO_SCENE);
		else if(options[selected]->get_text() == "Creditos")
			scene_mngr->end_scene(SceneMngr::TO_CREDITS);
		else if(options[selected]->get_text() == "Salir")
			scene_mngr->end_scene(SceneMngr::EXIT_GAME);
	}
	
	y_ = options[selected]->get_y() + 10;
}

void Menu::reset()
{
	music->stop();
	music->fadein(1000);
	selected = 0;
}

void Menu::resume()
{
	music->stop();
	music->fadein(1000);
}

void Menu::draw(SDL_Surface* screen)
{
	background->draw(screen, 0, 0, 0);
	cursor->draw(screen, 0, x_, y_);	

	for(std::size_t i = 0; i < options.size(); ++i){
		if(selected == i)		
			options[i]->draw(screen, true);
		else
			options[i]->draw(screen, false);
	}
}
	







