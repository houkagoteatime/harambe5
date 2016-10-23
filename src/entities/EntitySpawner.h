#pragma once
class Enemy;
class Ninja;
class Level;
#include "irrlicht.h"

class EntitySpawner {
public:
	static EntitySpawner* getInstance();
	template<typename T>T* spawnEnemy(irr::core::vector3df position, irr::core::vector3df rotation);
	template<typename T>T* spawnNpc(irr::core::vector3df position, irr::core::vector3df rotation);
	void init(Level* level);
private:
	Level* level;
	static EntitySpawner* instance;
	static int entityCount;
};

template<typename T>
inline T* EntitySpawner::spawnEnemy(irr::core::vector3df position, irr::core::vector3df rotation) {
	entityCount+=2;
	return new T(level, position, rotation, entityCount);
}
template<typename T>
inline T* EntitySpawner::spawnNpc(irr::core::vector3df position, irr::core::vector3df rotation) {
	entityCount+=2;
	return new T(level, position, rotation, entityCount);
}
