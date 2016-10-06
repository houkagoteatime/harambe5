#pragma once
#include <irrlicht.h>

class Projectile {
public:
  Projectile(irr::IrrlichtDevice* dev, irr::core::vector3df start, irr::core::vector3df end);
  virtual ~Projectile();
  virtual void update(float dt);
  irr::scene::ISceneNode* getNode();
  float getDamage();

	const irr::core::vector3df& getEnd() const {
		return end;
	}

	const irr::core::vector3df& getStart() const {
		return start;
	}

	bool isDead() const;

private:
  irr::scene::ISceneNode* projNode;
  float ttl;
  float timeAlive;
  float damage;
  bool dead;
  irr::core::vector3df start;
  irr::core::vector3df end;
  irr::core::vector3df direction;
  irr::scene::ISceneManager* smgr;
};
