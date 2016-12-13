#include "Ninja.h"
#include <iostream>

const EnemyInfo Ninja::ninjaInfo = {600, 20, 300, STATIONARY};

const std::string Ninja::MEDIA_PATH = "media/ninja.b3d";

/** Cooldown for attack in ms. */
const float Ninja::COOLDOWN = 3000;

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
    time = 0;
}

void Ninja::update(float delta) {
	Enemy::update(delta);
	entityNode->setLoopMode(true);
    time += delta;
}

void Ninja::updateAggroState(const irr::core::vector3df playerPos) {
	Enemy::updateAggroState(playerPos);
	if(isPlayerNearby(200) && time >= COOLDOWN) {
		attack();
        time = 0;
	} else {
		//entityNode->setFrameLoop(0, 13);
	}
}

void Ninja::attack() {
	entityNode->setFrameLoop(60, 70);
    player->takeDamage(30);
}
