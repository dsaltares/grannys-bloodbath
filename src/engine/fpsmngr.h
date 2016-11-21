/*
    This file is part of Granny's Bloodbath.

    Granny's Bloodbath is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Granny's Bloodbath is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Granny's Bloodbath.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _FPSMANAGER_
#define _FPSMANAGER_

//! Controla el framerrate de la aplicación

/**
	@author David Saltares Márquez
	@version 1.0
	
	Se encarga de llevar el control del framerrate deseado.
	Al final de cada frame se invoca la función que controla el framerrate.
	Si el PC donde se ejecuta la aplicación es más potente de lo debido se espera para ajustarse a la velocidad deseada.
	
	Ejemplo:
	\code
		FPSMngr fpsmngr(30);
	
		while(!keyboard->quit()){
			keyboard->update();
		
			cout << "FPS: " << fpsmngr.get_fps() << endl;
			cout << "Max FPS: " << fpsmngr.get_max() << endl;
			cout << "Best FPS: " << fpsmngr.get_best() << endl;
			cout << "Worst FPS: " << fpsmngr.get_worst() << endl;
			cout << "Average FPS: " << fpsmngr.get_average() << endl;
		
			fpsmngr.fps_control();
		}	
	\endcode
*/ 
class FPSMngr{
	public:
		/**
			Constructor
			
			@param maxfps Establece el framerrate deseado
		*/
		FPSMngr(int maxfps = 30);
		
		/**
			Método a llamar al final de cada iteración del game loop
			Si el PC ha ejecutado el game loop demasiado rápido espera para ajustarse a la velocidad deseada
			Si no, no espera
		*/
		void fps_control();
		
		/**
			Consultor
			
			@return FPS conseguidos en el último frame
		*/
		int get_fps() const;
		
		/**
			Consultor
			
			@return Mejor FPS desde que se activó el control de FPS
		*/
		int get_best() const;
		
		/**
			Consultor
			
			@return Peor FPS desde que se activó el control de FPS
		*/
		int get_worst() const;
		
		/**
			Consultor
			
			@return FPS medio desde que se activó el control de FPS
		*/
		double get_average() const;
		
		/**
			Consultor
			
			@return FPS máximos (el máximo establecido)
		*/
		int get_max() const;
		
		/**
			@param maxfps Nuevo máximo framerrate
			
			Establece un nuevo framerrate máximo
		*/
		void set_fps(int maxfps);
	private:
		int fps, max_fps, frame_count, best_fps, worst_fps;
		double average_fps;
		int time0, time;
};

inline int FPSMngr::get_fps() const {return fps;}
inline int FPSMngr::get_best() const {return best_fps;}
inline int FPSMngr::get_worst() const {return worst_fps;}
inline int FPSMngr::get_max() const {return max_fps;}

#endif
