#pragma once
#include "irrlicht.h"
class Player;
class Enemy;
class Npc;
#include "../ui/Gui.h"
#include "../weapons/Projectile.h"
#include <vector>
class Level1Scene;
class Level {
public:
  Level(irr::IrrlichtDevice* dev,irr::scene::IMeshSceneNode* map);
  ~Level();
  virtual void createLevel();
  virtual void update(float dt);
  void updateProjectiles(float dt);
  irr::IrrlichtDevice* getDevice();
  void handlePlayerClick();
  Level1Scene* scene;
  void addProjectile(Projectile* proj);
private:
  std::vector<Enemy*> enemies;
  std::vector<Npc*> npcs;
  std::vector<Projectile*> projectiles;
  Player *player;
  Gui* gui;
  float prevTime;
  irr::IrrlichtDevice* device;
  irr::scene::IMeshSceneNode* mapNode;
  irr::scene::ISceneCollisionManager* collMan;
};