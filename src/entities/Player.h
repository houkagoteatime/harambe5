#pragma once

#include "Entity.h"
#include "../InputProcessor.h"
class Player : public Entity{
public:
  Player(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int test);
  Player(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map);
  ~Player();
  virtual void initialize();
  virtual void update(float delta);
  static const float SPEED = 50;
  InputProcessor* getProcessor();
private:
  int test;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneNode* mapParent;
  irr::scene::IAnimatedMeshSceneNode* weaponNode;
  irr::scene::ICameraSceneNode *camera;
  irr::scene::IMeshSceneNode* mapNode;
  InputProcessor* proc;
};