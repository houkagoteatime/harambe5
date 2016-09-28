#include "Enemy.h"
#include "Player.h"
#include <cmath>
Enemy::Enemy(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id): 
Entity(level, mediaPath, position, rotation, map, id)
{
	initialize();
}

void Enemy::setPlayer(Player* play)
{
  player = play;
}

void Enemy::takeDamage(float dmg)
{
  health -= dmg;
}

void Enemy::initialize()
{
  state = STATIONARY;
  health = 200;
  damage = 10;
}

void Enemy::update(float delta)
{
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  rotateTowardsPosition(playerPos);
  entityNode->setRotation(rot);
  if(isPlayerNearby(100)) {
    state = AGGRO;
  }
  switch(state) {
    case AGGRO:
      updateAggroState(playerPos);
      break;
    default:
      break;
  }
  rot = entityNode->getRotation();
  pos = entityNode->getPosition();
}


void Enemy::updateAggroState(const irr::core::vector3df playerPos)
{
  rotateTowardsPosition(playerPos);
  irr::core::vector3df direction = (playerPos - pos).normalize();
  entityNode->setPosition(entityNode->getPosition() + direction * speed);
}

bool Enemy::isPlayerNearby(float range)
{
  return player->getCamera()->getPosition().getDistanceFrom(entityNode->getPosition()) < range;
}

bool Enemy::onClick(bool MouseEvent)
{
  //health -= player->getDamage();
  return false;
}

