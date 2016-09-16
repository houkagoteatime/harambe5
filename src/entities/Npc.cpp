#include "Npc.h>
#include <cmath>
Npc::Npc(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation): Entity(dev, mediaPath, position, rotation)
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
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::scene::IAnimatedMesh* mesh = manager->getMesh("media/sydney.md2");
  if(mesh) {
    entityNode = manager->addAnimatedMeshSceneNode(mesh);
    if(entityNode) {
    entityNode->setPosition(pos);
    entityNode->setRotation(rot);
    entityNode->setMD2Animation(irr::scene::EMAT_ATTACK);
    entityNode->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
    entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    entityNode->setName("Sydney");
    entityNode->setTriangleSelector(manager->createTriangleSelector(entityNode));
    }
  }
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
 
  rot = entityNode->getRotation();
  pos = entityNode->getPosition();
}

bool onClick() {
  
  
}

bool Enemy::isPlayerNearby(float range)
{
  if(range<=0) {
    return false;
  }
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  float distance = std::sqrt((std::pow<float>( (playerPos.X - pos.X), 2) - std::pow<float>((playerPos.Y - pos.Y), 2)));
  return std::abs(distance) <= range;
}
