#include <iostream>
#include <vector>
#include "parser.h"
#include "logger.h"
#include "menu.h"
#include "keyboard.h"
#include "specialscene.h"
#include "game.h"
#include "story.h"

using namespace std;

SceneMngr::SceneMngr(Application* app, const std::string& plot): application(app)
{
	// Cargamos el guión del juego
	Parser parser(plot);
	string type, path;
	
	vector<ticpp::Element*> plot_scenes;
	parser.find("scene", plot_scenes);
	
	for(vector<ticpp::Element*>::iterator i = plot_scenes.begin(); i != plot_scenes.end(); ++i){
		type = parser.get_attribute("type", *i);
		path = parser.get_attribute("path", *i);
		
		
		if(type == "story")
			scenes.push_back(make_pair(Scene::STORY, path));
		else if(type == "level")
			scenes.push_back(make_pair(Scene::GAME, path));
		else if(type == "boss")
			scenes.push_back(make_pair(Scene::BOSS, path));
	}
	
	// Ponemos el iterador al comienzo del guión
	it = scenes.begin();
	
	// Preparamos el menú principal
	menu = new Menu(this, "./XML/menu.xml");
	actual_scene = menu;
	
	game = 0;
	story = 0;
	old_scene = 0;
	credits = 0;
	gameover = 0;
}

SceneMngr::~SceneMngr()
{
	if(menu){
		delete menu;
		menu = 0;
	}
	
	if(game){
		delete game;
		game = 0;
	}
	
	if(story){
		delete story;
		story = 0;
	}
}

void SceneMngr::update()
{
	actual_scene->update();
}

void SceneMngr::draw(SDL_Surface* screen)
{
		actual_scene->draw(screen);
}

void SceneMngr::end_scene(Signal signal)
{
	// Según la señal llevamos a cabo una acción
	switch(signal){
		case GAME_OVER:
			game_over();
			break;
		case DEATH:
			death();
			break;
		case END_AND_GO_TO_MENU:
			end_to_menu();
			break;
		case SCENE_COMPLETED:
			scene_completed();
			break;
		case PAUSE_TO_MENU:
			pause_menu();
			break;
		case BACK_TO_SCENE:
			back_to_scene();
			break;
		case EXIT_GAME:
			exit_game();
			break;
		case TO_CREDITS:
			to_credits();
			break;
		default:
			break;
	}
}

void SceneMngr::game_over()
{
	// Volvemos al principio
	it = scenes.begin();
	
	if(game){
		delete game;
		game = 0;
	}
	
	if(story){
		delete story;
		story = 0;
	}
	
	gameover = new SpecialScene(this, "XML/gameover.xml");
	actual_scene = gameover;
}

void SceneMngr::death()
{
	// Reseteamos el nivel
	game->reset();
}

void SceneMngr::end_to_menu()
{
	// Eliminamos la escena actual y volvemos al menu
	
	if(actual_scene){
		delete actual_scene;
		actual_scene = 0;
	}
	
	if(!menu){
		menu = new Menu(this, "menu.xml");
	}
	
	menu->resume();
	actual_scene = menu;
}	

void SceneMngr::scene_completed()
{
	// Borramos la escena
	if(actual_scene){
		delete actual_scene;
		actual_scene = 0;
	}
	
	switch(it->first){
		case Scene::GAME:
		case Scene::BOSS:
			game = 0;
			break;
		case Scene::STORY:
			story = 0;
			break;
		default:
			break;
	}
	
	// Avanzamos el iterador del guión
	++it;
	
	// Si hemos terminado el guión empezamos y volvemos al menú
	if(it == scenes.end()){
		it = scenes.begin();
		actual_scene = menu;
		menu->resume();
	}
	else{	
		// Cargamos la siguiente escena
		switch(it->first){
			case Scene::GAME:
				game = new Game(this, it->second.c_str());
				actual_scene = game;
				break;
			case Scene::BOSS:
				game = new Game(this, it->second.c_str(), true);
				actual_scene = game;
				break;
			case Scene::STORY:
				story = new Story(this, it->second.c_str());
				actual_scene = story;
				break;
			default:
				break;
		}
	}
}

void SceneMngr::pause_menu()
{
	// Guardamos la escena actual y volvemos al menu
		
	old_scene = actual_scene;
	
	if(!menu){
		menu = new Menu(this, "menu.xml");
	}
	
	actual_scene = menu;
	menu->resume();
}

void SceneMngr::back_to_scene()
{
	// Si la escena anterior no estaba cargada
	if(!old_scene){
		if(it != scenes.end()){
			switch(it->first){
				case Scene::GAME:
					game = new Game(this, it->second.c_str());
					actual_scene = game;
					break;
				case Scene::BOSS:
					game = new Game(this, it->second.c_str(), true);
					actual_scene = game;
					break;
				case Scene::STORY:
					story = new Story(this, it->second.c_str());
					actual_scene = story;
					break;
				default:
					break;
			}
		}
	}
	// Si estaba cargada la cargamos	
	else{
		actual_scene = old_scene;
		actual_scene->resume();
	}
}

void SceneMngr::exit_game()
{
	keyboard->set_quit();
}

void SceneMngr::to_credits()
{
	credits = new SpecialScene(this, "XML/creditos.xml");	
	actual_scene = credits;
}

