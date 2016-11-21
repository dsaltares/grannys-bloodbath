#include <SDL/SDL.h>
#include "fpsmngr.h"

FPSMngr::FPSMngr(int maxfps): max_fps(maxfps) 
{
	best_fps = 0;
	worst_fps = 1000000;
	average_fps = 0;
	frame_count = 0;
	fps = 0;
	time0 = 0;
}

void FPSMngr::fps_control()
{
	time = SDL_GetTicks() - time0;
	
	fps = (time == 0)? 1000 : (1000/time);
	
	if(fps > best_fps)
		best_fps = fps;
	if(fps < worst_fps)
		worst_fps = fps;
		
	average_fps += fps;
	++frame_count;
	
	if(time < (1000/max_fps))
	    SDL_Delay((1000 / max_fps) - time);
	
	time0 = SDL_GetTicks();
}

double FPSMngr::get_average() const 
{
	return ((frame_count)? average_fps/frame_count : average_fps);
}

void FPSMngr::set_fps(int maxfps)
{
	max_fps = maxfps;
}

