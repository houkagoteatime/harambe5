#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
#include "../ui/Gui.h"
class Npc : public Entity {
public:
  Npc(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map);
  virtual void initialize();
  virtual void update(float delta);
  irr::gui::IGUIEnvironment* guiEnv;
  bool isPlayerNearby(float range);
  bool onClick(bool MouseEvent);
  void setPlayer(Player* play);
  void updateAggroState(const irr::core::vector3df playerPos);
protected:
  Player* player;
  Gui gui;
};