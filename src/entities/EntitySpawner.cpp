#include "EntitySpawner.h"

int EntitySpawner::entityCount = -1;
EntitySpawner* EntitySpawner::instance = 0;

EntitySpawner* EntitySpawner::getInstance() {
	if(!instance)
		instance = new EntitySpawner;
	return instance;
}


void EntitySpawner::init(Level* level) {
	this->level = level;
}
