#include <iostream>
#include "font.h"
#include "logger.h"

using namespace std;

Font::Font(const char* path, int size): size_(size)
{
	if((font = TTF_OpenFont(path, size)) == NULL){
		logger->error("Font::Font(): No se pudo cargar la fuente");
		exit(1);
	}
}

Font::~Font()
{
	TTF_CloseFont(font);
}

void Font::draw(SDL_Surface* screen, const std::string& text, SDL_Color color, int x, int y)
{
	SDL_Surface* tmp;

	if((tmp = TTF_RenderUTF8_Solid(font, text.c_str(), color)) == NULL){
		logger->error("Font::draw(): No se pudo dibujar el texto");
		exit(1);
	}

	if((surface = SDL_DisplayFormat(tmp)) == NULL){
		logger->error("Font::draw(): No se pudo adaptar el renderizado al formato de la pantalla");
		exit(1);
	}
	
	SDL_FreeSurface(tmp);

	SDL_Rect destiny = {x, y, surface->w, surface->h};

	SDL_BlitSurface(surface, NULL, screen, &destiny);
	
	SDL_FreeSurface(surface);
}

void Font::draw(SDL_Surface* screen, const std::string& text, SDL_Color color, int y, Alignment alignment)
{
	int x;
	
	switch(alignment){
		case LEFT:
			x = 5;
			break;
		case RIGHT:
			x = screen->w - text_width(text) - 5;
			break;
		case CENTER:
			x = (screen->w - text_width(text)) / 2;
			break;
	}
	
	draw(screen, text, color, x, y);
}

int Font::text_width(const std::string& text) const
{
	int h, w;
	
	if(TTF_SizeUTF8(font, text.c_str(), &w, &h) == -1){
		logger->error("Font::text_width(): No se pudo determinar el ancho del texto");
		exit(1);	
	}
	
	return w;
}

int Font::text_height(const std::string& text) const
{
	int h, w;
	
	if(TTF_SizeUTF8(font, text.c_str(), &w, &h) == -1){
		logger->error("Font::text_width(): No se pudo determinar el ancho del texto");
		exit(1);	
	}
	
	return h;
}


