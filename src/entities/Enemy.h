#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
#include "../levels/Level.h"
class Enemy : public Entity {
public:
  Enemy(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id);
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
  Player* player;
};