#include "Npc.h"
#include <cmath>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#include <iostream>

Npc::Npc(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id): 
Entity(dev, mediaPath, position, rotation, map, id)
{
  initialize();
  initMessages();
}

void Npc::setPlayer(Player* play)
{
  player = play;
}

void Npc::setGui(Gui* gui)
{
  this->gui = gui;
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
  if(inDialogue) {
    if(!(isPlayerNearby(200))) {
      exitDialogue();
    }
  }
  rot = entityNode->getRotation();
  pos = entityNode->getPosition();
}

bool Npc::onClick(bool MouseEvent) {
  entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, MouseEvent);
  if(MouseEvent) {
     dialogue(MouseEvent);
  }
}

bool Npc::isPlayerNearby(float range)
{
  return player->getCamera()->getPosition().getDistanceFrom(entityNode->getPosition()) < range;
  if(range<=0) {
    return false;
  }
  const irr::core::vector3df playerPos = player->getCamera()->getPosition();
  float distance = std::sqrt((std::pow<float>( (playerPos.X - pos.X), 2) - std::pow<float>((playerPos.Y - pos.Y), 2)));
  return std::abs(distance) <= range;
}

void Npc::initMessages()
{
  messages.push_back("Welcome to harambe5");
  //messages.push_back("This is the Labyritnh of Dank Memes");
  messages.push_back("H");
  messages.push_back("A");
  messages.push_back("R");
  messages.push_back("A");
  messages.push_back("M");
  messageIt = 0;
  inDialogue = false;
  textAdvanceTimer = device->getTimer()->getTime();
}

void Npc::dialogue(bool MouseEvent)
{
  
  //std::cout << device->getTimer()->getTime() << "::" << textAdvanceTimer << "::" << device->getTimer()->getTime() - textAdvanceTimer << std::endl;
  if((device->getTimer()->getTime() - textAdvanceTimer) > 500) {
  textAdvanceTimer = device->getTimer()->getTime();
  
  if(messageIt >= messages.size()) {
    messageIt = messageIt % messages.size();
    exitDialogue();
    return;
  }
  inDialogue = true;
  gui->addStaticText(messages[messageIt++]);
  gui->setVisibleStaticText(true);
  }
}

void Npc::exitDialogue()
{
  gui->setVisibleStaticText(false);
  inDialogue = false;
  messageIt = 0;
}




