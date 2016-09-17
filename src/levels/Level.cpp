#include "Level.h"

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
}

void Level::createLevel()
{
  collMan = device->getSceneManager()->getSceneCollisionManager();
  player = new Player(device,"media/gun.md2", irr::core::vector3df(0,15,0),irr::core::vector3df(0,0,0), mapNode);
  Enemy* testEnemy = new Enemy(device,"media/sydney.md2", irr::core::vector3df(30, 15, 30), irr::core::vector3df(0,0,0), mapNode);
  Npc* testNpc = new Npc(device,"media/sydney.md2", irr::core::vector3df(-90,-15,-140), irr::core::vector3df(0,0,0), mapNode);
  enemies.push_back(testEnemy);
  npcs.push_back(testNpc);
  int8_t i;
  for(i = 0; i < enemies.size(); i++) {
    enemies.at(i)->setPlayer(player);
  }
  for(i = 0; i<npcs.size(); i++) {
    npcs.at(i)->setPlayer(player);
  }
}

void Level::update(float dt)
{
    player->update(dt);
    handlePlayerClick();
    int8_t i;
    for(i = 0; i<enemies.size(); i++) {
      enemies.at(i)->update(dt);
    }
    for(i = 0; i<npcs.size(); i++) {
      npcs.at(i)->update(dt);
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
 if(selectedSceneNode)
  {
	if(selectedSceneNode->getAbsolutePosition().getDistanceFrom(player->getCamera()->getAbsolutePosition()) < 200) 
	{
	  player->getBillBoard()->setPosition(intersection);
	  int j = 0;
	  for(j = 0; j < npcs.size(); j++) {
	    if(selectedSceneNode = npcs[j]->getEntityNode()) {
	      npcs[j]->onClick(player->getEventReceiver()->GetMouseState()->LeftButtonDown);
	    }
	  }
	}
  }
}

