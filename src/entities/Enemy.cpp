#include "Enemy.h"
#include <cmath>
Enemy::Enemy(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id): 
Entity(dev, mediaPath, position, rotation, map, id)
{
	initialize();
}

void Enemy::setPlayer(Player* play)
{
  player = play;
}

void Enemy::initialize()
{
  entityNode->setPosition(pos);
  entityNode->setRotation(rot);
  entityNode->setMD2Animation(irr::scene::EMAT_ATTACK);
  entityNode->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
  entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  entityNode->setName("Sydney");
  entityNode->setTriangleSelector(manager->createTriangleSelector(entityNode));
  state = STATIONARY;
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
  if(range<=0) {
    return false;
  }
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  float distance = std::sqrt((std::pow<float>( (playerPos.X - pos.X), 2) - std::pow<float>((playerPos.Y - pos.Y), 2)));
  return std::abs(distance) <= range;
}


