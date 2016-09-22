#include "Projectile.h"

Projectile::Projectile(irr::IrrlichtDevice* dev,irr::core::vector3df start, irr::core::vector3df end, float time) : smgr(dev->getSceneManager()), start(start), end(end), ttl(time)
{
  projNode = smgr->addBillboardSceneNode();
  projNode->setMaterialTexture(0, dev->getVideoDriver()->getTexture("media/fireball.bmp"));
  projNode->setPosition(start);
  projNode->setMaterialFlag(irr::video::EMF_ZBUFFER, false);
  projNode->setID(0);
  direction = (end - start).normalize();
  irr::scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(start, end, time);
  projNode->addAnimator(anim);
  anim->drop();
  anim = smgr->createDeleteAnimator(time);
  projNode->addAnimator(anim);
  anim->drop();
}


Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
  projNode->setPosition(projNode->getPosition() + direction * dt);
}
