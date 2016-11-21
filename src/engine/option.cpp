#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include "font.h"
#include "option.h"

using namespace std;


void Option::draw(SDL_Surface* screen, bool selected)
{
	if(selected)
		font_->draw(screen, text_, selected_col, x_, y_);
	else
		font_->draw(screen, text_, nselected_col, x_, y_);
}
