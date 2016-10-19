#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Player.h"
#include "Mob.h"
#include "Damageable.h"
#include "../levels/Level.h"

enum EnemyState {
	STATIONARY,
	AGGRO
};

struct EnemyInfo {
	float health;
	float damage;
	float aggroRange;
	EnemyState defaultState;
};

class Enemy : public Entity, public Mob, public Damageable {
public:
	Enemy(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, int id, EnemyInfo info);
	virtual void update(float delta);
	bool isPlayerNearby(float range);
	void setPlayer(Player* play);
	virtual void updateAggroState(const irr::core::vector3df playerPos) = 0;
	virtual void updateStationaryState();
	virtual void updateStates();
	virtual void attack() = 0;
	virtual bool onClick(bool MouseEvent);

protected:
	Player* player;
	float aggroRange;
	enum EnemyState state;
};
