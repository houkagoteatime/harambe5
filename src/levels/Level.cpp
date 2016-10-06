#include "Level.h"

#include <aabbox3d.h>
#include <irrList.h>
#include <IAnimatedMeshSceneNode.h>
#include <IBillboardSceneNode.h>
#include <ICameraSceneNode.h>
#include <IMeshSceneNode.h>
#include <IrrlichtDevice.h>
#include <ISceneCollisionManager.h>
#include <ISceneManager.h>
#include <ISceneNode.h>
#include <ISceneNodeAnimator.h>
#include <line3d.h>
#include <sys/types.h>
#include <triangle3d.h>
#include <vector3d.h>
#include <iterator>

#include "../entities/Enemy.h"
#include "../entities/Npc.h"
#include "../entities/Player.h"
#include "../input/EventReceiver.h"
#include "../scenes/Level1Scene.h"

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1,
	IDFlag_IsHighlightable = 2
};

Level::Level(irr::IrrlichtDevice* dev, irr::scene::IMeshSceneNode* map) : device(dev), mapNode(map)
{
	createLevel();
}


Level::~Level()
{
	if(player)
		delete player;
	if(gui)
		delete gui;
	enemies.clear();
}

void Level::createLevel()
{
	collMan = device->getSceneManager()->getSceneCollisionManager();
	gui = new Gui(device);
	player = new Player(this,"media/gun.md2", irr::core::vector3df(40,1000,0),irr::core::vector3df(0,0,0), mapNode);
	Enemy* testEnemy = new Enemy(this,"media/faerie.md2", irr::core::vector3df(60, 200, 0), irr::core::vector3df(0,0,0), mapNode, 7);
	Enemy* testEnemy1 = new Enemy(this,"media/faerie.md2", irr::core::vector3df(70, 200, 0), irr::core::vector3df(0,0,0), mapNode, 3);
	Npc* testNpc = new Npc(this,"media/sydney.md2", irr::core::vector3df(90, 200,-140), irr::core::vector3df(0,0,0), mapNode, 5);

	enemies.push_back(testEnemy);
	npcs.push_back(testNpc);
	enemies.push_back(testEnemy1);
	int8_t i;
	for(i = 0; i < enemies.size(); i++) {
		enemies.at(i)->setPlayer(player);
	}
	for(i = 0; i<npcs.size(); i++) {
		npcs.at(i)->setPlayer(player);
		npcs.at(i)->setGui(gui);
	}
	scene = new Level1Scene(this);
	scene->startScene();
}

void Level::update(float dt)
{
	//std::cout << player->getCamera()->getPosition().X  << ","
  //<< player->getCamera()->getPosition().Y << "," 
  //<< player->getCamera()->getPosition().Z << std::endl;
  if(scene) {
  if(scene->sceneStarted) {
  if(player->getEventReceiver()->GetMouseState()->LeftButtonDown == true) {
   device->getSceneManager()->setActiveCamera(player->getCamera()); 
   scene->deleteGui();
  }
  }
  
  if(scene->sa->hasFinished()) {
    device->getSceneManager()->setActiveCamera(player->getCamera()); 
    scene->sceneStarted = true;
    scene->deleteGui();
  }
  }
	player->update(dt);
	handlePlayerClick();
	int8_t i;
	for(i = 0; i<enemies.size(); i++) {
		enemies.at(i)->update(dt);
		if(checkCollision(enemies[i]->getEntityNode(), player->getEntityNode())) {
			std::cout << "OUCH" << player->getEntityNode()->getPosition().X << player->getEntityNode()->getPosition().Y << std::endl;
		} else {
			std::cout <<"NOU" <<std::endl;
		}
		if(enemies.at(i)->isDead()) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}
	for(i = 0; i<npcs.size(); i++) {
		npcs.at(i)->update(dt);
	}
	updateProjectiles(dt);
}

void Level::addProjectile(Projectile* proj)
{
	projectiles.push_back(proj);
}

void Level::updateProjectiles(float dt)
{
	int8_t j;
	int8_t i;
	for(i = 0; i<projectiles.size(); i++) {
		projectiles[i]->update(dt);
		if(projectiles[i]->isDead() || projectiles[i]->getNode()->getAnimators().empty()) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		} else {
			irr::scene::ISceneNode* collNode = getIntersectionNode(projectiles[i]->getStart(), projectiles[i]->getEnd());
			for(j = 0; j<enemies.size(); j++) {
				if(checkCollision(enemies[j]->getEntityNode(), projectiles[i]->getNode())) {
					//if(collNode == enemies[j]->getEntityNode()) {
					enemies[j]->takeDamage(projectiles[i]->getDamage());
					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					break;
				}
			}
		}
	}
}

void Level::handlePlayerClick()
{
	irr::core::line3df ray;
	ray.start = player->getCamera()->getPosition();
	ray.end = ray.start + (player->getCamera()->getTarget() - ray.start).normalize() * 1000.0f;
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection, hitTriangle, IDFlag_IsPickable,0);
	player->getBillBoard()->setPosition(intersection);
	if(selectedSceneNode)
	{
		if(selectedSceneNode->getAbsolutePosition().getDistanceFrom(player->getCamera()->getAbsolutePosition()) < 200)
		{
			//player->getBillBoard()->setPosition(intersection);
			int j = 0;
			for(j = 0; j < npcs.size(); j++) {
				//if(selectedSceneNode = npcs[j]->getEntityNode()) {
				if(selectedSceneNode == npcs[j]->getEntityNode()) {
					npcs[j]->onClick(player->getEventReceiver()->GetMouseState()->LeftButtonDown);
				}
			}
		}
	}
}

irr::IrrlichtDevice* Level::getDevice()
{
	return device;
}

bool Level::checkCollision(irr::scene::ISceneNode* node1, irr::scene::ISceneNode* node2) {
	irr::core::aabbox3df box1, box2;
	if(node2 && node1) {
		box1 = node1->getBoundingBox();
		box2 = node2->getBoundingBox();
		node1->getRelativeTransformation().transformBox(box1);
		node2->getRelativeTransformation().transformBox(box2);
		return box1.intersectsWithBox(box2);
	}
	return false;
}

irr::scene::ISceneNode* Level::getIntersectionNode(irr::core::vector3df start, irr::core::vector3df end) {
	irr::core::line3df ray;
	ray.start = start;
	ray.end = end;
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection, hitTriangle, IDFlag_IsPickable,0);
	return selectedSceneNode;
}
