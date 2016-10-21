#pragma once
#include "../input/EventReceiver.h"
#include "../levels/Level.h"
#include "Damageable.h"
#include "Entity.h"
class Player : public Entity, public Damageable  {
public:
  Player(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation);
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
  void resetPosition(irr::core::vector3df pos);
  int jumpDelay;
  irr::scene::ISceneNodeAnimator* anim;
  const static float PROJECTILE_DELAY_TIME;
protected:
  irr::scene::IAnimatedMeshSceneNode* weaponNode;
  irr::scene::ICameraSceneNode* camera;
  EventReceiver* receiver;
private:
  float shootDelay;
  irr::scene::IBillboardSceneNode * bill;
};
