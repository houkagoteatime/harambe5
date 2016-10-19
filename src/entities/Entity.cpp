#include "Entity.h"
#include <cmath>
#include <iostream>

Entity::Entity(Level* level, const std::string& mediaPath,irr::core::vector3df position, irr::core::vector3df rotation, int id)
: level(level),path(mediaPath), pos(position), rot(rotation),mapNode(level->getMapNode())
{
	device = level->getDevice();
	manager = device->getSceneManager();
	driver = device->getVideoDriver();
	mesh = manager->getMesh(mediaPath.c_str());
	entityNode = manager->addAnimatedMeshSceneNode(mesh, 0, id);
	gui = device->getGUIEnvironment();
	if(id != -1) {
		entityNode->setPosition(pos);
		entityNode->setRotation(rot);
		//entityNode->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
		entityNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		entityNode->setTriangleSelector(manager->createTriangleSelector(entityNode));
		addCollision();
	}
}

Entity::~Entity()
{
	if(entityNode) {
		entityNode->remove();
	}
}

irr::scene::IAnimatedMeshSceneNode* Entity::getEntityNode()
{
	return entityNode;
}


void Entity::addCollision()
{
	if(entityNode) {
		irr::scene::ISceneNodeAnimator* anim = manager->createCollisionResponseAnimator(mapNode->getTriangleSelector(), entityNode, irr::core::vector3df(30,50,30),irr::core::vector3df(0,-9.8,0),irr::core::vector3df(0,-15,0),0.0005f);
		entityNode->addAnimator(anim);
		anim->drop();
	}
}

void Entity::rotateTowardsPosition(irr::core::vector3df target)
{
	irr::core::vector3df distance = pos - target;
	distance.Y = distance.getHorizontalAngle().Y + offset;
	rot = irr::core::vector3df(0,distance.Y,0);
}


