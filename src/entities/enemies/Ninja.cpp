#include "Ninja.h"
#include <iostream>

const EnemyInfo Ninja::ninjaInfo = {600, 20, 300, STATIONARY};

const std::string Ninja::MEDIA_PATH = "media/ninja.b3d";

Ninja::Ninja(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id) :
Enemy(level, MEDIA_PATH, position, rotation, id, ninjaInfo)
{
	initialize();
}

void Ninja::initialize() {
	offset = 180;
	entityNode->setMaterialTexture(0, driver->getTexture("media/nskinrd.jpg"));
	entityNode->setScale(irr::core::vector3df(10.f,10.f,10.f));
	entityNode->setFrameLoop(0, 13);
	entityNode->setAnimationSpeed(5);
	entityNode->setLoopMode(true);
}

void Ninja::update(float delta) {
	Enemy::update(delta);
	entityNode->setLoopMode(true);
}

void Ninja::updateAggroState(const irr::core::vector3df playerPos) {
	Enemy::updateAggroState(playerPos);
	if(isPlayerNearby(200)) {
		attack();
		player->takeDamage(damage);
	} else {
		//entityNode->setFrameLoop(0, 13);
	}
}

void Ninja::attack() {
	entityNode->setFrameLoop(60, 70);
}
