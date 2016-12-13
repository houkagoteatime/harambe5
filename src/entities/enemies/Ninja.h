#pragma once
#include "irrlicht.h"
#include "../Enemy.h"
class Ninja : public Enemy {
public:
	Ninja(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id);
	void initialize();
	virtual void update(float delta);
	virtual void updateAggroState(const irr::core::vector3df playerPos);
	virtual void attack();
	static const EnemyInfo ninjaInfo;
	static const std::string MEDIA_PATH;
    static const float COOLDOWN;
private:
    float time;
};
