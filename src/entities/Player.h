#pragma once

#include "Entity.h"
#include "../InputProcessor.h"
class Player : public Entity{
public:
  Player(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation);
  ~Player();
  virtual void initialize();
  virtual void update(float delta);
  static const float SPEED = 50;
  InputProcessor* getProcessor();
private:
  irr::IrrlichtDevice* device;
  irr::scene::ISceneNode* mapParent;
  irr::scene::IAnimatedMeshSceneNode* weaponNode;
  irr::scene::ICameraSceneNode *camera;
  InputProcessor* proc;
};