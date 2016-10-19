#include "Enemy.h"
#include "Player.h"
#include <cmath>
Enemy::Enemy(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, int id, EnemyInfo info):
Entity(level, mediaPath, position, rotation, id), Damageable(info.health, info.damage), aggroRange(info.aggroRange), state(info.defaultState)
{
	player = level->getPlayer();
}

void Enemy::setPlayer(Player* play)
{
	player = play;
}

void Enemy::update(float delta)
{
	//entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	updateStates();
	rot = entityNode->getRotation();
	pos = entityNode->getPosition();
	entityNode->updateAbsolutePosition();
}


void Enemy::updateAggroState(const irr::core::vector3df playerPos)
{
	if(!isPlayerNearby(aggroRange)) {
		state = STATIONARY;
	} else {
		rotateTowardsPosition(playerPos);
		entityNode->setRotation(rot);
		rotateTowardsPosition(playerPos);
		irr::core::vector3df direction = (playerPos - pos).normalize();
		entityNode->setPosition(entityNode->getPosition() + direction * speed);
	}
}

void Enemy::updateStationaryState() {
	if(isPlayerNearby(aggroRange))
		state = AGGRO;
}

bool Enemy::isPlayerNearby(float range)
{
	return player->getCamera()->getPosition().getDistanceFrom(entityNode->getPosition()) <= range;
}

bool Enemy::onClick(bool MouseEvent)
{
	return true;
}


void Enemy::updateStates() {
	switch(state) {
	case AGGRO:
		updateAggroState(player->getCamera()->getPosition());
		break;
	case STATIONARY:
		updateStationaryState();
		break;
	default:
		break;
	}
}


