#include "Faerie.h"

const std::string Faerie::MEDIA_PATH = "media/faerie.md2";
const char* Faerie::DIALOGUE_PATH = "assets/data/faerie.dat";

Faerie::Faerie(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id) :
Npc(level,MEDIA_PATH, position, rotation, id, DIALOGUE_PATH)
{
  std::cout << ("hello") << std::endl;
}

void Faerie::dialogue(bool MouseEvent)
{
 if((device->getTimer()->getTime() - textAdvanceTimer) > 500) {
  textAdvanceTimer = device->getTimer()->getTime();
  
  if(messageIt >= messages->size()) {
    player->getCamera()->removeAnimator(player->anim);
    player->anim = manager->createCollisionResponseAnimator( mapNode->getTriangleSelector(), player->getCamera(), irr::core::vector3df(30,50,30),irr::core::vector3df(0, 2,0),irr::core::vector3df(0,30,0),0.0005f);
    player->getCamera()->addAnimator(player->anim);
    messageIt = messageIt % messages->size();
    exitDialogue();
    return;
  }
  inDialogue = true;
  gui->addStaticText(messages->at(messageIt++), true);
  }
}