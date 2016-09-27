#pragma once
#include <irrlicht.h>

class Projectile {
public:
  Projectile(irr::IrrlichtDevice* dev, irr::core::vector3df start, irr::core::vector3df end);
  ~Projectile();
  virtual void update(float dt);
  irr::scene::ISceneNode* getNode();
private:
  irr::scene::ISceneNode* projNode;
  float ttl;
  irr::core::vector3df start;
  irr::core::vector3df end;
  irr::core::vector3df direction;
  irr::scene::ISceneManager* smgr;
};