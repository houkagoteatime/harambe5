#pragma once
#include "../input/EventReceiver.h"
#include "../levels/Level.h"
#include "Entity.h"
class Player : public Entity  {
public:
  Player(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map);
  ~Player();
  virtual void initialize();
  virtual void update(float delta);
  virtual void addCollision();
  void attack();
  void addBillboard();
  irr::scene::IBillboardSceneNode* getBillBoard();
  EventReceiver* getEventReceiver();
  static const float SPEED = 50;
  irr::scene::ICameraSceneNode* getCamera();
  void jump();
  int jumpDelay;
protected:
  irr::scene::IAnimatedMeshSceneNode* weaponNode;
  irr::scene::ICameraSceneNode* camera;
  EventReceiver* receiver;
private:
  irr::scene::IBillboardSceneNode * bill;
};
