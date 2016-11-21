#include <iostream>
#include "resourcemngr.h"
#include "parser.h"
#include "logger.h"

using namespace std;

ResourceMngr* ResourceMngr::_instance = 0;

ResourceMngr::ResourceMngr()
{
	// Abrimos el XML con la lista de recursos a cachear
	Parser parser("./XML/resources.xml");
	
	vector<ticpp::Element*> resources;
	vector<ticpp::Element*>::iterator i;
	string code, path;
	int rows, columns, size;
	
	// Creamos las imágenes
	parser.find("image", resources, parser.find("images"));
	for(i = resources.begin(); i != resources.end(); ++i){
		code = parser.get_attribute("code", *i);
		path = parser.get_attribute("path", *i);
		parser.get_attribute("rows", *i, &rows);
		parser.get_attribute("columns", *i, &columns);
		
		ImageMngr imgmngr = {path, rows, columns, NULL, 0};
		images[code] = imgmngr;
	}
	
	resources.clear();
	
	// Creamos las fuentes
	parser.find("font", resources, parser.find("fonts"));
	for(i = resources.begin(); i != resources.end(); ++i){
		code = parser.get_attribute("code", *i);
		path = parser.get_attribute("path", *i);
		parser.get_attribute("size", *i, &size);
		
		FontMngr fontmngr = {path, size, NULL, 0};
		fonts[code] = fontmngr;
	}
	
	resources.clear();
	
	// Creamos los efectos de sonido
	parser.find("sound", resources, parser.find("sounds"));
	for(i = resources.begin(); i != resources.end(); ++i){
		code = parser.get_attribute("code", *i);
		path = parser.get_attribute("path", *i);
		
		SoundMngr soundmngr = {path, NULL, 0};
		sounds[code] = soundmngr;
	}
	
	resources.clear();
	
	// Creamos las músicas
	parser.find("music", resources, parser.find("musics"));
	for(i = resources.begin(); i != resources.end(); ++i){
		code = parser.get_attribute("code", *i);
		path = parser.get_attribute("path", *i);
		
		MusicMngr musicmngr = {path, NULL, 0};
		musics[code] = musicmngr;
	}
	
	resources.clear();
}

void ResourceMngr::free_instance() {
	delete _instance;
}

ResourceMngr::~ResourceMngr()
{
	// Destruimos las imágenes
	for(Images::iterator i = images.begin(); i != images.end(); ++i)
		if(i->second.image != NULL)
			delete i->second.image;
	
	// Destruimos las fuentes
	for(Fonts::iterator i = fonts.begin(); i != fonts.end(); ++i)
		if(i->second.font != NULL)
			delete i->second.font;
		
	// Destruimos los efectos de sonido
	for(Sounds::iterator i = sounds.begin(); i != sounds.end(); ++i)
		if(i->second.sound != NULL)
			delete i->second.sound;
		
	// Destruimos las músicas
	for(Musics::iterator i = musics.begin(); i != musics.end(); ++i)
		if(i->second.music != NULL)
			delete i->second.music;
}


Image* ResourceMngr::image(const std::string& code)
{
	Images::iterator i = images.find(code);
	
	if(i == images.end()){
		logger->warning("ResourceMngr::image(): Código no encontrado");
		return NULL;
	}
	
	if(i->second.counter == 0)
		i->second.image = new Image(i->second.path.c_str(), i->second.rows, i->second.columns);
	
	i->second.counter++;

	return i->second.image;
}

Font* ResourceMngr::font(const std::string& code) 
{
	Fonts::iterator i = fonts.find(code);
	
	if(i == fonts.end()){
		logger->warning("ResourceMngr::font(): Código no encontrado");
		return NULL;
	}
	
	if(i->second.counter == 0)
		i->second.font = new Font(i->second.path.c_str(), i->second.size);
	
	i->second.counter++;
	
	return i->second.font;
}

Sound* ResourceMngr::sound(const std::string& code) 
{
	Sounds::iterator i = sounds.find(code);
	
	if(i == sounds.end()){
		logger->warning("ResourceMngr::sound(): Código no encontrado");
		return NULL;
	}
	
	if(i->second.counter == 0)
		i->second.sound = new Sound(i->second.path.c_str());
	
	i->second.counter++;
	
	return i->second.sound;
}

Music* ResourceMngr::music(const std::string& code) 
{
	Musics::iterator i = musics.find(code);
	
	if(i == musics.end()){
		logger->warning("ResourceMngr::music(): Código no encontrado");
		return NULL;
	}
	
	if(i->second.counter == 0)
		i->second.music = new Music(i->second.path.c_str());
	
	i->second.counter++;
	
	return i->second.music;
}

void ResourceMngr::free_image(const std::string& code)
{
	Images::iterator i = images.find(code);
	
	if(i != images.end()){
		
		if(i->second.counter > 0)
			(i->second.counter)--;
		
		if((i->second.counter) == 0 && i->second.image != NULL){
			delete i->second.image;
			i->second.image = NULL;
		}
	}
}

void ResourceMngr::free_font(const std::string& code)
{
	Fonts::iterator i = fonts.find(code);
	
	if(i != fonts.end()){
		
		if(i->second.counter > 0)
			(i->second.counter)--;
		
		if((i->second.counter) == 0 && i->second.font != NULL){
			delete i->second.font;
			i->second.font = NULL;
		}
	}
}

void ResourceMngr::free_music(const std::string& code) // That doesnt mean music at no cost
{
	Musics::iterator i = musics.find(code);
	
	if(i != musics.end()){
		
		if(i->second.counter > 0)
			(i->second.counter)--;
		
		if((i->second.counter) == 0 && i->second.music != NULL){
			delete i->second.music;
			i->second.music = NULL;
		}
	}
}

void ResourceMngr::free_sound(const std::string& code)
{
	Sounds::iterator i = sounds.find(code);
	
	if(i != sounds.end()){
		
		if(i->second.counter > 0)
			(i->second.counter)--;
		
		if((i->second.counter) == 0 && i->second.sound != NULL){
			delete i->second.sound;
			i->second.sound = NULL;
		}
	}
}


