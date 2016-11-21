// Listado: Imagen.cpp
//
// Implementación de la clase imagen

#include <iostream>
#include <SDL/SDL_image.h>

#include "image.h"
#include "logger.h"

using namespace std;

Image::Image(const char *path, int rows, int columns): columns_(columns), rows_(rows)
{
	if((normal_image = IMG_Load(path) ) == NULL) {
		logger->error(string("Image()::Image(): No se pudo cargar la imagen: ") + string(path));
		exit(1);
	}
	
	SDL_Surface *tmp = normal_image;
	
	if((normal_image = SDL_DisplayFormatAlpha(tmp)) == NULL) {
		logger->error("Image()::Image(): No se pudo adaptar la imagen al formato de la pantalla");
		exit(1);
	}
	
	SDL_FreeSurface(tmp);
	
	if((inverted_image = reverse_image(normal_image)) == NULL) {
		logger->error("Image()::Image(): No se pudo invertir la imagen");
		exit(1);
	}
	
	width_ = normal_image->w / columns_;
	height_ = normal_image->h / rows_;
}



void Image::draw(SDL_Surface *screen, int f, int x, int y, bool flip)
{
	SDL_Rect destiny, origin;
	    
	destiny.x = x;
	destiny.y = y;
	destiny.h = 0;
	destiny.w = 0;
	
	origin.w = width_;
	origin.h = height_;
	
	if(f < 0 || f > (rows_ * columns_))	{
		logger->error("Image::draw() = No existe el cuadro");
		return;
	}
	
	if(flip) {
		origin.x = ((columns_-1) - (f % columns_)) * width_;
		origin.y = (f / columns_) * height_;
		SDL_BlitSurface(inverted_image, &origin, screen, &destiny);
	}
	else{
		origin.x = ((f % columns_) * width_);
		origin.y = ((f / columns_) * height_);
		SDL_BlitSurface(normal_image, &origin, screen, &destiny);	
	}
}


Image::~Image()
{
	SDL_FreeSurface(normal_image);
	SDL_FreeSurface(inverted_image);
}

Uint32 Image::get_pixel(int x, int y) const
{
	if(!normal_image) {
		logger->error("Image::get_pixel(): Superficie inválida");
		exit(1);
	}
	if(x < 0 || x > normal_image->w || y < 0 || y > normal_image->h) {
		logger->error("Image::get_pixel(): Posición inválida");
		exit(1);
	}
	if(SDL_LockSurface(normal_image) < 0){
		logger->error("Image::get_pixel(): No se puede bloquear la superficie");
		exit(1);
	}
	int bpp = normal_image->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)normal_image->pixels + y * normal_image->pitch + x * bpp;

	Uint32 ret = 0;

	switch(bpp) {
		case 1:
			ret = *p;
			break;
		case 2:
			ret = *(Uint16 *)p;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				ret = (p[0] << 16 | p[1] << 8 | p[2]);
			else
				ret = (p[0] | p[1] << 8 | p[2] << 16);
			break;
		case 4:
			ret = *(Uint32 *)p;
			break;
		default:
			ret = 0;
			break;
	}

	SDL_UnlockSurface(normal_image);
	return ret;
}


SDL_Surface * Image::reverse_image(SDL_Surface *image)
{
	SDL_Rect origin;
	SDL_Rect destiny;
	
	origin.x = 0;
	origin.y = 0;
	origin.w = 1;
	origin.h = image->h;
	
	destiny.x = image->w;
	destiny.y = 0;
	destiny.w = 1;
	destiny.h = image->h;
	
	SDL_Surface *inverted;

	if((inverted = SDL_DisplayFormatAlpha(image)) == NULL) {
		logger->error("Image()::reverse_image(): No se pudo adaptar la imagen al formato de la pantalla");
		return NULL;
	}
	
	SDL_FillRect(inverted, NULL, SDL_MapRGBA(inverted->format, 0, 0, 0, 0));
	
	for(int i = 0; i < image->w; i++) {
		SDL_BlitSurface(image, &origin, inverted, &destiny);
		origin.x = origin.x + 1;
		destiny.x = destiny.x - 1;
	}
	
	return inverted;
}


