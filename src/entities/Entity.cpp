#include "Entity.h"
#include <cmath>
#include <iostream>
Entity::Entity(irr::IrrlichtDevice* dev, const std::string& mediaPath,irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id) 
		: device(dev),path(mediaPath), pos(position), rot(rotation),mapNode(map)
{
  manager = device->getSceneManager();
  driver = device->getVideoDriver();
  //mesh = manager->getMesh(mediaPath.c_str());
  //why can pass in param
  mesh = manager->getMesh(irr::core::string<irr::fschar_t>(mediaPath.c_str()));
  if(!mesh) {
    mesh = manager->getMesh("media/sydney.md2");
  }
  entityNode = manager->addAnimatedMeshSceneNode(mesh, 0, id);
  gui = device->getGUIEnvironment();
  addCollision();
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
