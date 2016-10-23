#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
#include "../ui/Gui.h"
#include "Mob.h"
#include <vector>

#include <sstream>
#include <fstream>
#include <string>
class Entity;
class Npc : public Entity, public Mob {
public:
  Npc(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, int id, const char* dialoguePath);
  virtual void initialize();
  virtual void update(float delta);
  irr::gui::IGUIEnvironment* guiEnv;
  bool isPlayerNearby(float range);
  virtual bool onClick(bool MouseEvent);
  void setPlayer(Player* play);
  void setGui(Gui* gui);
  void initMessages();
  virtual void dialogue(bool MouseEvent);
  void exitDialogue();
  void addMessages(const char* file);
protected:
  Player* player;
  Gui* gui;
  std::vector<std::string>* messages;
  int messageIt;
  bool inDialogue;
  int textAdvanceTimer;
};
