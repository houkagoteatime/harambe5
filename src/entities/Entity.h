#pragma once
#include <irrlicht.h>
#include <string>
#include "../levels/Level.h"
class Level;
class Entity {
public:
  Entity(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, int id);
  virtual ~Entity();
  virtual void update(float delta) = 0;
  virtual void addCollision();
  void rotateTowardsPosition(irr::core::vector3df target);
  irr::scene::IAnimatedMeshSceneNode* getEntityNode();

protected:
  Level* level;
  std::string path;
  const static float speed = 1.0;
  float offset;
  int id;
  irr::core::vector3df pos;
  irr::core::vector3df rot;
  irr::gui::IGUIEnvironment* gui;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneManager* manager;
  irr::video::IVideoDriver* driver;
  irr::scene::IAnimatedMesh* mesh;
  const irr::scene::IMeshSceneNode* mapNode;
  irr::scene::IAnimatedMeshSceneNode* entityNode;
  float currTime;
};
