#include "Projectile.h"

Projectile::Projectile(irr::IrrlichtDevice* dev,irr::core::vector3df start, irr::core::vector3df end) : start(start), end(end)
{
	damage = 50;
	float time = 1000;
	ttl = time;
	smgr = dev->getSceneManager();
	projNode = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(10,10), start);
	projNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	projNode->setMaterialTexture(0, dev->getVideoDriver()->getTexture("media/particle.bmp"));
	projNode->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	projNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	projNode->setPosition(start);
	projNode->setID(-2);
	direction = (end - start).normalize();
	irr::scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(start, end, time);
	projNode->addAnimator(anim);
	anim->drop();
	timeAlive = 0;
	dead = false;
}


Projectile::~Projectile()
{
	if(projNode)
		projNode->remove();
}

void Projectile::update(float dt)
{
	timeAlive += dt;
	if(timeAlive >= ttl)
		dead = true;
}

irr::scene::ISceneNode* Projectile::getNode()
{
	return projNode;
}

float Projectile::getDamage()
{
	return damage;
}

bool Projectile::isDead() const {
	return dead;
}
