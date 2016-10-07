#include "Npc.h"
#include "Entity.h"
#include "../levels/Level.h"
#include <cmath>

Npc::Npc(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id): 
Entity(level, mediaPath, position, rotation, map, id)
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
}

void Npc::addMessages(std::string message)
{
  messages.push_back(message);
}

void Npc::initMessages()
{
  messageIt = 0;
  inDialogue = false;
  textAdvanceTimer = device->getTimer()->getTime();
}

void Npc::dialogue(bool MouseEvent)
{
 if((device->getTimer()->getTime() - textAdvanceTimer) > 500) {
  textAdvanceTimer = device->getTimer()->getTime();
  
  if(messageIt >= messages.size()) {
    player->resetPosition(irr::core::vector3df(player->getCamera()->getPosition().X, 5000, player->getCamera()->getPosition().Z));
    messageIt = messageIt % messages.size();
    exitDialogue();
    return;
  }
  inDialogue = true;
  gui->addStaticText(messages[messageIt++], true);
  }
}

void Npc::exitDialogue()
{
  gui->setVisibleStaticText(false);
  inDialogue = false;
  messageIt = 0;
}




