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

#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_

#include <string>
#include <vector>
#include <utility>
#include <SDL/SDL.h>
#include "scene.h"
#include "application.h"

class Menu;
class Game;
class Story;
class SpecialScene;

//! Maneja las escenas y el cambio entre ellas

/**
	@author David Saltares Márquez
	@version 1.0
	
	La clase se encarga de gestionar todas las escenas y el cambio de una a otra. La clase Application simplemente pide que SceneMngr se actualice y ésta actualiza la escena concreta que estime oportuno.
	
	Carga un fichero XML con el guión del juego que enumera la secuencia de escenas de historia y niveles juagables. Un ejemplo de este fichero sería:
	
	\code
		<plot>
			<scene type = "story" path = "introduction.xml" />
			<scene type = "level" path = "level1.tmx" />
			<scene type = "story" path = "argument.xml" />
			<scene type = "level" path = "level2.tmx" />
			<scene type = "story" path = "ending.xml" />
		</plot>
	\endcode
	
	Cuando el jugador selecciona Jugar se comienza por el primer elemento del guión, cuando finaliza uno con éxito pasamos al siguiente. Si en algún momento nos eliminan volvemos al menú y comenzaríamos el guión de nuevo. Si terminamos todos los elementos con éxito también volvemos al menú.
	
	Ejemplo:
	\code
		void Application::update(){
			scene_mngr->update();
		}
		
		void Application::draw(){
			scene_mngr->update(screen);
		}
		
		...
		
		void Game::update(){
			...
			
			// Hemos llegado al final del nivel
			scene_mngr->end_scene(SceneMngr::SCENE_COMPLETED);
			
			...
			
			// Eliminan a nuestro personaje y no tenemos más vidas
			scene_mngr->end_scene(SceneMngr::GAME_OVER);
		}
	\endcode
*/
class SceneMngr{
	public:
		
		//! Señales que le podemos enviar al SceneMngr para que el decida qué cambios de escena hacer
		enum Signal{GAME_OVER, DEATH, END_AND_GO_TO_MENU, SCENE_COMPLETED, PAUSE_TO_MENU, BACK_TO_SCENE, EXIT_GAME, TO_CREDITS};
	
		/**
			Constructor
			
			@param plot ruta al fichero XML con el guión del juego
			
			Crea el Manejador de escenas y comienza en el menú principal	
		*/
		SceneMngr(Application* app, const std::string& plot);
		
		/**
			Destructor
			
			Libera la memoria ocupada por las escenas cargadas actualmente
		*/
		~SceneMngr();
		
		/**
			Actualiza de manera lógica la escena actual
		*/
		void update();
		
		/**
			@param screen superficie en la que se dibuja la escena
			
			Dibuja la escena actual en la superficie dada
		*/
		void draw(SDL_Surface* screen);
		
		/**
			@param signal Señal para decirle al SceneMngr lo ocurrido
			
			La escena concluye e informa a SceneMngr que debe pasar a otra escena.
			En función de la señal, SceneMngr decide qué hacer.
		*/
		void end_scene(Signal signal);
		
		/**
		 *	    @return ancho en píxeles de la pantalla
		 */
		int get_screen_width() const;
		
		/**
		 *	    @return alto en píxeles de la pantalla
		 */
		int get_screen_height() const;
	private:
		
		Application* application;
		Scene* actual_scene;
		Scene* old_scene;
		Menu* menu;
		Game* game;
		SpecialScene* credits;
		SpecialScene* gameover;
		Story* story;
		
		std::vector<std::pair<Scene::Scenes, std::string> > scenes;
		std::vector<std::pair<Scene::Scenes, std::string> >::iterator it;
		
		// Métodos para manejar las transiciones entre escenas
		void game_over();
		void death();
		void end_to_menu();
		void scene_completed();
		void pause_menu();
		void back_to_scene();
		void exit_game();
		void to_credits();
};

inline int SceneMngr::get_screen_width() const {return application->get_screen_width();}
inline int SceneMngr::get_screen_height() const {return application->get_screen_height();}
	
#endif
