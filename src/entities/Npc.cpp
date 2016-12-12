#include "Npc.h"
#include "Entity.h"
#include "../levels/Level.h"
#include <cmath>

Npc::Npc(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, int id,const char* dialoguePath): 
Entity(level, mediaPath, position, rotation, id)
{
  initialize();
  initMessages();
  messages = new std::vector<std::string>();
  addMessages(dialoguePath);
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
  return false;
}

bool Npc::isPlayerNearby(float range)
{
  return player->getCamera()->getPosition().getDistanceFrom(entityNode->getPosition()) < range;
}

void Npc::addMessages(const char* file)
{
  std::string line;
  std::ifstream myfile;
  myfile.open(file);
  for(std::string line; std::getline(myfile, line);) {
    messages->push_back(line);
  }
  myfile.close();
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
  
  if(messageIt >= messages->size()) {
    messageIt = messageIt % messages->size();
    exitDialogue();
    return;
  }
  inDialogue = true;
  gui->addStaticText(messages->at(messageIt++), true);
  }
}

void Npc::exitDialogue()
{
  gui->setVisibleStaticText(false);
  inDialogue = false;
  messageIt = 0;
}




