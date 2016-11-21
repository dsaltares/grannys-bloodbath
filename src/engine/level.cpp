#include <cstdio>
#include <cstdlib>
#include <string>

#include "level.h"
#include "parser.h"
#include "game.h"
#include "logger.h"
#include "granny.h"
#include "item.h"
#include "enemy.h"
#include "zombie.h"
#include "resourcemngr.h"
#include "dog.h"
#include "fat.h"
#include "boss.h"
#include "spider.h"

using namespace std;

Level::Level(Game* game, const char* path): g(game)
{
	Parser parser(path);
	
	actor_factory = new ActorFactory(g);
	
	ticpp::Element* e;
	
	// Información del mapa
	e = parser.find("map");
	parser.get_attribute("width", e, &width);
	parser.get_attribute("height", e, &height);
	parser.get_attribute("tileheight", e, &tile_height);
	parser.get_attribute("tilewidth", e, &tile_width);

	e = parser.find("image");
	string image_path = parser.get_attribute("source", e);
	e = parser.find("properties", parser.find("map"));
	
	// Propiedades del tileset
	int tileset_width = 1, tileset_height = 1;
	string collision_map_path;
	Image* collision_map;
	vector<ticpp::Element*>properties;
	
	parser.find("property", properties, e);
	
	for(vector<ticpp::Element*>::iterator i = properties.begin(); i != properties.end(); i++){
		if(parser.get_attribute("name", *i) == "tileset_ancho")
			parser.get_attribute("value", *i, &tileset_width);
		else if(parser.get_attribute("name", *i) == "tileset_alto")
			parser.get_attribute("value", *i, &tileset_height);
		else if(parser.get_attribute("name", *i) == "collision_map")
			collision_map_path = parser.get_attribute("value", *i);
		else if(parser.get_attribute("name", *i) == "music")
			g->set_music(parser.get_attribute("value", *i));
		else if(parser.get_attribute("name", *i) == "zombie"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "zombie";
		}
		else if(parser.get_attribute("name", *i) == "dog"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "dog";
		}
		else if(parser.get_attribute("name", *i) == "fat"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "fat";
		}
		else if(parser.get_attribute("name", *i) == "spider"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "spider";
		}
		else if(parser.get_attribute("name", *i) == "boss"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "boss";
		}
		else if(parser.get_attribute("name", *i) == "teeth"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "teeth";
		}
		else if(parser.get_attribute("name", *i) == "pills"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "pills";
		}
		else if(parser.get_attribute("name", *i) == "ammo"){
			int frame;
			parser.get_attribute("value", *i, &frame);
			actors_map[frame] = "ammo";
		}
	}
	
	tileset = new Image(image_path.c_str(), tileset_height, tileset_width);
	collision_map = new Image(collision_map_path.c_str(), tileset_height, tileset_width);
	
	// Reservamos memoria para el mapa
	if((level = (Tile***)malloc(4 * sizeof(Tile**))) == NULL){
		logger->error("Level::Level(): Memoria insuficiente para el mapa");
		exit(1);
	}
	
	for(int i = 0; i < 4; i++){		
		if((level[i] = (Tile**)malloc(height * sizeof(Tile*))) == NULL){
			logger->error("Level::Level(): Memoria insuficiente para el mapa");
			exit(1);
		}
		
		for(int j = 0; j < height; j++){
			if((level[i][j] = (Tile*)malloc(width * sizeof(Tile))) == NULL){
				logger->error("Level::Level(): Memoria insuficiente para el mapa");
				exit(1);
			}
		}
	}
	
	x = 0;
	y = 0;
	
	// Parseamos el contenido del mapa
	vector<ticpp::Element*> layers;
	vector<ticpp::Element*> tiles_layer;
	
	parser.find("layer", layers);
	
	int layer = 0;
	int row = 0;
	int column = 0;
	int n = 0;
	int frame;
	
	Image* tile_types = new Image("multimedia/tile_types.png", 1, 3);
	
	// Para cada capa rellenamos la matriz del mapa
	for(vector<ticpp::Element*>::iterator i = layers.begin(); i != layers.end(); i++){
		// Vector con todos los tiles de cada mapa
		parser.find("tile", tiles_layer, *i);
		for(vector<ticpp::Element*>::iterator j = tiles_layer.begin(); j != tiles_layer.end(); j++){
			parser.get_attribute("gid", *j, &frame);
			row = n / width;
			column = (n % width) % width;
			level[layer][row][column].frame = frame;
			
			// Obtenemos el tipo de tile (atravesable, no atravesable o plataforma)
			if(frame == 0)
				level[layer][row][column].type = PASSABLE;
			else{
				int p_x = (((frame - 1) % tileset_width) % tileset_width) * tile_height;
				int p_y = ((frame - 1) / tileset_width) * tile_width;
				Uint32 color = collision_map->get_pixel(p_x, p_y);
			
				if(color == tile_types->get_pixel(0, 0))
					level[layer][row][column].type = PASSABLE;
				else if(color == tile_types->get_pixel(1, 0))
					level[layer][row][column].type = NONPASSABLE;
				else if(color == tile_types->get_pixel(2, 0))
					level[layer][row][column].type = PLATFORM;
				else
					level[layer][row][column].type = PASSABLE;
			}
			
			n++;
		}
		n = 0;
		tiles_layer.clear();
		layer++;
	}
	
	// Liberamos los recursos temporales
	delete collision_map;
	delete tile_types;
	
	// Cargamos a los actores
	load_actors();
}

Level::~Level()
{	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < height; j++){
			free(level[i][j]);
		}
		
		free(level[i]);
	}
	
	free(level);
	
	delete tileset;
	
	delete actor_factory;
}

void Level::draw(SDL_Surface* screen, int layer)
{
	int lx, ly, margin_x, margin_y, num_blocks_x, num_blocks_y;
	int pos_x, pos_y;
	int frame;
	
	if(layer < 0 || layer > 3){
		logger->error("Level::draw(): Capa inválida");
		exit(1);
	}
	
	// Calculamos las posiciones
	lx = x / tile_width;
	ly = y / tile_height;

	// Calculamos número de bloques a dibujar
	num_blocks_x = screen->w / tile_width;
	num_blocks_y = screen->h / tile_height;
	
	// Calculamos si hay píxeles sobrantes
	margin_x = x % tile_width;
	margin_y = y % tile_height;
	
	if(margin_x)
		++num_blocks_x;
	if(margin_y)
		++num_blocks_y;	
	
	// Recorremos la capa y la dibujamos
	for(int row = 0; row < num_blocks_y; ++row){
		for(int column = 0; column < num_blocks_x; ++column){
			frame = level[layer][row + ly][column + lx].frame - 1;
			if(frame > -1){
				pos_x = column * tile_width - margin_x;
				pos_y = row * tile_width - margin_y;
				tileset->draw(screen, frame, pos_x, pos_y);
			}
		}
	}
}

Tile Level::get_tile(int x, int y, int layer) const
{	
	if(x < 0 || x > width || y < 0 || y > height || layer < 0 || layer > 3){
		logger->warning("Level::get_tile(): Coordenadas fuera de rango, tomamos el tile básico");
		Tile tile = {0, PASSABLE};
		return tile;
	}

	return level[layer][y][x];
}

void Level::move(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Level::load_actors()
{
	// Aquí se cargarían los actores
	
	map<int, string>::iterator it;
	int x, y;
	Enemy* enemy;
	Item* item;
	
	// Recorremos la cuarta capa del mapa
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			it = actors_map.find(level[3][i][j].frame);
			// Si estamos en un frame con un actor
			if(it != actors_map.end()){
				
				x = j * tile_height;
				y = i * tile_width;
				
				// Si el frame corresponde a un zombie
				if(it->second == "zombie"){
					enemy = actor_factory->get_zombie(x, y);
					g->add_enemy(enemy);
				}
				// Si el frame corresponde a un gordo
				if(it->second == "fat"){
					enemy = actor_factory->get_fat(x, y);
					g->add_enemy(enemy);
				}
				// Si el frame corresponde a un perro
				if(it->second == "dog"){
					enemy = actor_factory->get_dog(x, y);
					g->add_enemy(enemy);
				}
				// Si el frame corresponde a una araña
				if(it->second == "spider"){
					enemy = actor_factory->get_spider(x, y);
					g->add_enemy(enemy);
				}
				// Si el frame corresponde a un boss
				if(it->second == "boss"){
					enemy = actor_factory->get_boss(x, y);
					g->add_enemy(enemy);
				}
				// Si el frame corresponde a dentadura
				else if(it->second == "teeth"){
					item = actor_factory->get_teeth(x, y);
					g->add_item(item);
				}
				// Si el frame corresponde a pastillas
				else if(it->second == "pills"){
					item = actor_factory->get_pill(x, y);
					g->add_item(item);
				}
				// Si el frame corresponde a munición
				else if(it->second == "ammo"){
					item = actor_factory->get_ammo(x, y);
					g->add_item(item);
				}
			}
		}
	}
}

