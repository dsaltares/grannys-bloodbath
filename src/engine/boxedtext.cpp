#include <cstring>
#include "boxedtext.h"
#include "logger.h"

using namespace std;

BoxedText::BoxedText(Font* font, SDL_Color color, SDL_Rect box, const string& text): font_(font), color_(color), rect_(box), text_(text)
{
	changed = true;
	first_time = true;
}

BoxedText::~BoxedText()
{
	
}

void BoxedText::draw(SDL_Surface* screen)
{
	char* tmp;
	char* word;
	int line_width = 0;
	int x = 0, y = 0;
	
	// Si algo ha cambiado del texto tenemos que renderizarlo de nuevo
	if(changed){
		// Copiamos el texto en cadenas temporales, blitearemos palabra a palabra
		tmp = new char[text_.size() + 1];
		strcpy(tmp, text_.c_str());
	
		if(!first_time)
			SDL_FreeSurface(rendered_text);
		else
			first_time = false;
	
		if((rendered_text = SDL_CreateRGBSurface(SDL_HWSURFACE, rect_.w, rect_.h, 32, 0, 0, 0, 0)) == NULL){
			logger->error("BoxedText::draw(): No se pudo reservar memoria para la superficie de renderizado");
			exit(1);
		}
	
		// Extraemos palabra a palabra	
		for(word = strtok(tmp, " \n"); word != NULL; word = strtok(NULL, " \0")){
			// Si cabe la palabra a lo largo y a lo alto la bliteamos
			if(line_width + font_->text_width(word) <= rect_.w)
				line_width += font_->text_width(word) + font_->get_size()/4;
				
			// Si no cabe a lo largo saltamos una línea y bliteamos
			else{
				y += font_->line_skip();
				x = 0;
				line_width = font_->text_width(word) + font_->get_size()/4;
			}
		
			font_->draw(rendered_text, string(word),color_, x, y);
			x += font_->text_width(word) + font_->get_size()/4;
		}
	
		changed = false;
	}

	SDL_Surface* temp;
		
	if((temp = SDL_DisplayFormat(rendered_text)) == NULL){
		logger->error("BoxedText::draw(): No se pudo adaptar el renderizado al formato de la pantalla");
		exit(1);
	}
	
	SDL_SetColorKey ( temp ,  SDL_SRCCOLORKEY , SDL_MapRGB ( temp -> format , 0 , 0 , 0 ));
	
	SDL_Rect destiny = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_BlitSurface(temp, NULL, screen, &destiny);
	SDL_FreeSurface(temp);
}

void BoxedText::set_rect(SDL_Rect rect)
{
	if(rect.h <= 10)
		rect.h = 10;
	if(rect.w <= 10)
		rect.w = 10;
	rect_ = rect;
	changed = true;
}

void BoxedText::set_color(SDL_Color color)
{
	color_ = color;
	changed = true;
}

void BoxedText::set_font(Font* font)
{
	font_ = font;
	changed = true;
}

void BoxedText::set_text(const string& text)
{
	text_ = text;
	changed = true;
}

