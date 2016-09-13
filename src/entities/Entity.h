#pragma once

#include <irrlicht.h>
#include <string>

class Entity {
public:
  Entity(const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation);
  virtual void initialize() = 0;
  virtual void update(float delta) = 0;
protected:
  irr::core::vector3df pos;
  irr::core::vector3df rot;
  std::string path;
};