#include "actorfactory.h"
#include "zombie.h"
#include "game.h"
#include "actor.h"
#include "dog.h"
#include "fat.h"
#include "item.h"
#include "boss.h"
#include "spider.h"

ActorFactory::ActorFactory(Game *game):g(game){
	
	zombie = new Zombie(g,"XML/zombie.xml",0,0);
	fat = new Fat(g,"XML/fat.xml",0,0);
	dog = new Dog(g,"XML/dog.xml",0,0);
	spider = new Spider(g, "XML/spider.xml", 0, 0);
	boss = new Boss(g,"XML/boss.xml",0,0);
		
	pill = new Item(g,"XML/pills.xml",0,0);
	teeth = new Item(g,"XML/teeth.xml",0,0);
	ammo = new Item(g,"XML/ammo.xml",0,0);
	
}

ActorFactory::~ActorFactory(){
	
	delete zombie;
	delete fat;
	delete dog;
	delete pill;
	delete teeth;
	delete ammo;
}

Zombie* ActorFactory::get_zombie(int x, int y){
	
	Zombie *z = static_cast<Zombie *>(zombie->clone(x, y));
	//return zombie->clone(x, y);
	return z;
	
}

Fat* ActorFactory::get_fat(int x, int y){
	
	Fat *f = static_cast<Fat *>(fat->clone(x, y));

	return f;
}

Dog* ActorFactory::get_dog(int x, int y){
	
	Dog *d = static_cast<Dog *>(dog->clone(x, y));

	return d;
}

Spider* ActorFactory::get_spider(int x, int y){
 
	Spider *s = static_cast<Spider *>(spider->clone(x, y));

	return s;
}
		

Boss* ActorFactory::get_boss(int x, int y){
	Boss *b = static_cast<Boss *>(boss->clone(x, y));
	return b;
}

Item* ActorFactory::get_pill(int x, int y){
	
	Item *i = static_cast<Item *>(pill->clone(x, y));

	return i;	
}

Item* ActorFactory::get_teeth(int x, int y){
	
	Item *i = static_cast<Item *>(teeth->clone(x, y));

	return i;	
}

Item* ActorFactory::get_ammo(int x, int y){
	
	Item *i = static_cast<Item *>(ammo->clone(x, y));

	return i;	
}







