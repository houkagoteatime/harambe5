#pragma once

#include <irrlicht.h>
#include <string>

class Entity {
public:
  Entity(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation);
  virtual void initialize() = 0;
  virtual void update(float delta) = 0;
  void rotateTowardsPosition(irr::core::vector3df target);
protected:
  irr::core::vector3df pos;
  irr::core::vector3df rot;
  irr::IrrlichtDevice* device;
  std::string path;
  const static float speed = 50;
};