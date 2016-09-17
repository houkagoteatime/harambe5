#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
class Npc : public Entity {
public:
  Npc(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map);
  virtual void initialize();
  virtual void update(float delta);
  bool isPlayerNearby(float range);
  bool onClick(bool MouseEvent);
  void setPlayer(Player* play);
  void updateAggroState(const irr::core::vector3df playerPos);
  void gui();
protected:
  Player* player;
};