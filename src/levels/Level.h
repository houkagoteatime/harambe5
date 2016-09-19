#pragma once

#include "irrlicht.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../entities/Npc.h"
#include "../ui/Gui.h"
#include <vector>
class Level {
public:
  Level(irr::IrrlichtDevice* dev,irr::scene::IMeshSceneNode* map);
  ~Level();
  virtual void createLevel();
  virtual void update(float dt);
  void handlePlayerClick();
private:
  std::vector<Enemy*> enemies;
  std::vector<Npc*> npcs;
  Player *player;
  Gui* gui;
  float prevTime;
  irr::IrrlichtDevice* device;
  irr::scene::IMeshSceneNode* mapNode;
  irr::scene::ISceneCollisionManager* collMan;
};