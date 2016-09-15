#include "Enemy.h"
#include <cmath>
Enemy::Enemy(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation): Entity(dev, mediaPath, position, rotation)
{
	initialize();
}

void Enemy::setPlayer(Player* play)
{
  player = play;
}

void Enemy::initialize()
{
  irr::scene::ISceneManager* manager = device->getSceneManager();
  irr::scene::IAnimatedMesh* mesh = manager->getMesh("media/sydney.md2");
  if(mesh) {
    entityNode = manager->addAnimatedMeshSceneNode(mesh);
    if(entityNode) {
    entityNode->setPosition(pos);
    entityNode->setRotation(rot);
    entityNode->setMD2Animation(irr::scene::EMAT_ATTACK);
    }
  }
}

void Enemy::update(float delta)
{
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  rotateTowardsPosition(playerPos);
  entityNode->setRotation(rot);
  rot = entityNode->getRotation();
  pos = entityNode->getPosition();
}
