#include "Projectile.h"

Projectile::Projectile(irr::IrrlichtDevice* dev,irr::core::vector3df start, irr::core::vector3df end) : start(start), end(end)
{
  float time = 1000;
  ttl = time;
  irr::core::vector3df stor = end;
  end.normalize();
  start += end;
  end = start + stor;
  smgr = dev->getSceneManager();
  projNode = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(10,10), start);
  projNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  projNode->setMaterialTexture(0, dev->getVideoDriver()->getTexture("media/particle.bmp"));
  projNode->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  projNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  projNode->setPosition(start);
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
  if(projNode)
    delete projNode;
}

void Projectile::update(float dt)
{
  
}

irr::scene::ISceneNode* Projectile::getNode()
{
  return projNode;
}
