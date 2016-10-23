#pragma once

#include "irrlicht.h"
class Player;
class Enemy;
class Npc;
class Ninja;
class EntitySpawner;
class Sydney;
#include "../ui/Gui.h"
#include "../weapons/Projectile.h"
#include <vector>
#include "../entities/EntitySpawner.h"
class Level1Scene;
class Level {
public:
	Level(irr::IrrlichtDevice* dev,irr::scene::IMeshSceneNode* map);
	virtual ~Level();
	virtual void createLevel();
	virtual void update(float dt);
	bool checkCollision(irr::scene::ISceneNode* node1, irr::scene::ISceneNode* node2);
	void updateProjectiles(float dt);
	irr::IrrlichtDevice* getDevice();
	void handlePlayerClick();
	Level1Scene* scene;
	template<typename T> void createEntity(irr::core::vector3df pos);
	template<typename T> void createNpc(irr::core::vector3df pos);
	void addProjectile(Projectile* proj);
	irr::scene::ISceneNode* getIntersectionNode(irr::core::vector3df start, irr::core::vector3df end);
	Player* getPlayer() const;
	const irr::scene::IMeshSceneNode* getMapNode();

private:
	EntitySpawner* spawner;
	std::vector<Enemy*> enemies;
	std::vector<Npc*> npcs;
	std::vector<Projectile*> projectiles;
	Player *player;
	Gui* gui;
	float prevTime;
	irr::IrrlichtDevice* device;
	irr::scene::IMeshSceneNode* mapNode;
	irr::scene::ISceneCollisionManager* collMan;

};

template<typename T>
inline void Level::createEntity(irr::core::vector3df pos) {
	Enemy* enem = spawner->spawnEnemy<T>(pos, irr::core::vector3df(0, 0, 0));
	enemies.push_back(enem);
}

template<typename T>
inline void Level::createNpc(irr::core::vector3df pos) {
	Npc* npc = spawner->spawnNpc<T>(pos, irr::core::vector3df(0, 0, 0));
	npcs.push_back(npc);
}
