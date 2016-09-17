#include "Npc.h"
#include <cmath>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


Npc::Npc(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map): 
Entity(dev, mediaPath, position, rotation, map),gui(dev)
{
  initialize();
}

void Npc::setPlayer(Player* play)
{
  player = play;
}
void Npc::initialize()
{
  entityNode->setPosition(irr::core::vector3df(-90,-15,-140)); // Put its feet on the floor.
  entityNode->setPosition(pos);
  entityNode->setRotation(rot);
  entityNode->setMD2Animation(irr::scene::EMAT_ATTACK);
  entityNode->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
  entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  entityNode->setName("Sydney");
  entityNode->setTriangleSelector(manager->createTriangleSelector(entityNode));

}

void Npc::update(float delta)
{
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  rotateTowardsPosition(playerPos);
  entityNode->setRotation(rot);
  if(isPlayerNearby(100)) {
    //
  }
 
  rot = entityNode->getRotation();
  pos = entityNode->getPosition();
}

bool Npc::onClick(bool MouseEvent) {
  entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, MouseEvent);
  gui.setVisibleImage(MouseEvent);
  return false;
}

bool Npc::isPlayerNearby(float range)
{
  if(range<=0) {
    return false;
  }
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  float distance = std::sqrt((std::pow<float>( (playerPos.X - pos.X), 2) - std::pow<float>((playerPos.Y - pos.Y), 2)));
  return std::abs(distance) <= range;
}
