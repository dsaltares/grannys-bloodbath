#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "hud.h"
#include "resourcemngr.h"
#include "image.h"
#include "parser.h"
#include "logger.h"

using namespace std;

HUD::HUD(const char *path, int me):max_energy(me), energy(me){

	Parser parser(path);

	image_code = parser.get_attribute("code", parser.find("image"));
	parser.get_attribute("x", parser.find("image"), &hud_destiny.x);
	parser.get_attribute("y", parser.find("image"), &hud_destiny.y);
	hud = resource->image(image_code.c_str());

	string path_bar;

	path_bar = parser.get_attribute("path", parser.find("progressbar"));
	parser.get_attribute("x", parser.find("progressbar"), &bar_destiny.x);
	parser.get_attribute("y", parser.find("progressbar"), &bar_destiny.y);
	parser.get_attribute("w", parser.find("progressbar"), &bar_destiny.w);
	parser.get_attribute("h", parser.find("progressbar"), &bar_destiny.h);
	
	bar = IMG_Load(path_bar.c_str());

	int r, g, b;

	font_code = parser.get_attribute("code", parser.find("font"));
	parser.get_attribute("r", parser.find("font"), &r);
	parser.get_attribute("g", parser.find("font"), &g);
	parser.get_attribute("b", parser.find("font"), &b);

	color.r = r;
	color.g = g;
	color.b = b; 
	
	font = resource->font(font_code.c_str());
	
	if(font == NULL)
		cout << "cuidado, fuente nula" << endl;

	parser.get_attribute("lifesx",parser.find("information"),&lifesx);
	parser.get_attribute("lifesy",parser.find("information"),&lifesy);
	parser.get_attribute("pointsx",parser.find("information"),&pointsx);
	parser.get_attribute("pointsy",parser.find("information"),&pointsy);
	parser.get_attribute("munitionx",parser.find("information"),&munitionx);
	parser.get_attribute("munitiony",parser.find("information"),&munitiony);
	
	update(0, 0, 0, 0);
}

HUD::~HUD(){
	resource->free_image(image_code);
	resource->free_font(font_code);

	SDL_FreeSurface(bar);
}


void HUD::update(int l, int p, int m, int e){

	if(e>max_energy)
		energy = max_energy;
	else
		energy = e;
		
	char aux[10];
	
	sprintf(aux, "%d", l);
	lifes = aux;
	
	sprintf(aux, "%d", p);
	points = aux;
	
	sprintf(aux, "%d", m);
	munition = aux;

}

void HUD::draw(SDL_Surface* screen){

	hud->draw(screen, 0, hud_destiny.x, hud_destiny.y);
	
	SDL_Rect origin;
	origin.x = 0;
	origin.y = 0;
	origin.w = (bar->w*energy)/max_energy;
	origin.h = bar->h;
	
	SDL_BlitSurface(bar, &origin, screen, &bar_destiny);

	font->draw(screen, lifes, color, lifesx, lifesy);
	font->draw(screen, points, color, pointsx, pointsy);
	font->draw(screen, munition, color, munitionx, munitiony);

}
