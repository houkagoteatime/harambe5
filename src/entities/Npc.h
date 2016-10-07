#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
#include "../ui/Gui.h"
#include "Mob.h"
#include <vector>
#include <string>
class Entity;
class Npc : public Entity, public Mob {
public:
  Npc(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id);
  virtual void initialize();
  virtual void update(float delta);
  irr::gui::IGUIEnvironment* guiEnv;
  bool isPlayerNearby(float range);
  virtual bool onClick(bool MouseEvent);
  void setPlayer(Player* play);
  void setGui(Gui* gui);
  void updateAggroState(const irr::core::vector3df playerPos);
  void initMessages();
  void dialogue(bool MouseEvent);
  void exitDialogue();
  void addMessages(std::string message);
protected:
  Player* player;
  Gui* gui;
  std::vector<std::string> messages;
  int messageIt;
  bool inDialogue;
  int textAdvanceTimer;
};
