#include "GameState.h"
#include <irrlicht.h>

GameState::GameState(irr::IrrlichtDevice* dev): State(dev)
{
  soundManager = new SoundManager();
  currentState = GAME;
  init();
}


GameState::~GameState()
{
  if(level1)
    delete level1;
  if(soundManager)
    delete soundManager;
}

void GameState::init()
{
  irr::scene::IAnimatedMesh* mapMesh = smgr->getMesh("maps/lemap.bsp");
  irr::scene::IMeshSceneNode* mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, 1);
  irr::scene::ITriangleSelector* selector = 0;
  if(mapNode) {
    selector = smgr->createOctreeTriangleSelector(
				mapNode->getMesh(), mapNode, 128);
    mapNode->setTriangleSelector(selector);    
  }
  level1 = new Level(dev, mapNode, this);
  soundManager->startMusic("media/music/aomine.mp3", irrklang::vec3df(smgr->getActiveCamera()->getPosition()));
}


void GameState::update(float dt)
{
  level1->update(dt);
  soundManager->updateMusic(irrklang::vec3df(smgr->getActiveCamera()->getPosition()));
}
