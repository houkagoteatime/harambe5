#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
class Enemy : public Entity {
public:
  Enemy(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation);
  virtual void initialize();
  virtual void update(float delta);
  bool isPlayerNearby(float range);
  void setPlayer(Player* play);
  void updateAggroState(const irr::core::vector3df playerPos);
  enum EnemyState {
    STATIONARY,
    AGGRO
  };
  enum EnemyState state;
protected:
  irr::scene::IAnimatedMeshSceneNode* entityNode;
  Player* player;
};