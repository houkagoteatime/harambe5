#include "../levels/Level.h"
#include "Entity.h"
#include <cmath>
#include <iostream>
Entity::Entity(Level* level, const std::string& mediaPath,irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id) 
		: lev(level),path(mediaPath), pos(position), rot(rotation),mapNode(map)
{
  manager = device->getSceneManager();
  driver = device->getVideoDriver();
  mesh = manager->getMesh(mediaPath.c_str());
  if(!mesh) {
    mesh = manager->getMesh("media/sydney.md2");
  }
  entityNode = manager->addAnimatedMeshSceneNode(mesh, 0, id);
  //entityNode = manager->addAnimatedMeshSceneNode(mesh, 0);
  gui = device->getGUIEnvironment();
  if(id != -1) {
  entityNode->setPosition(pos);
  entityNode->setRotation(rot);
  entityNode->setMD2Animation(irr::scene::EMAT_ATTACK);
  entityNode->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
  entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  entityNode->setTriangleSelector(manager->createTriangleSelector(entityNode));
  addCollision();
  }
}

void Entity::addCollision()
{
  if(entityNode) {
  irr::scene::ISceneNodeAnimator* anim = manager->createCollisionResponseAnimator( mapNode->getTriangleSelector(), entityNode, irr::core::vector3df(30,50,30),irr::core::vector3df(0,-10,0),irr::core::vector3df(0,30,0),0.0005f);
  entityNode->addAnimator(anim);
  anim->drop();
  }
}

void Entity::rotateTowardsPosition(irr::core::vector3df target)
{
  irr::core::vector3df distance = pos - target;
  distance.Y = distance.getHorizontalAngle().Y + 90;
  rot = irr::core::vector3df(0,distance.Y,0);
}
