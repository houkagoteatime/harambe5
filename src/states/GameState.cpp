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
  irr::scene::IAnimatedMesh* mapMesh = smgr->getMesh("20kdm2.bsp");
  irr::scene::IMeshSceneNode* mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, 1);
  irr::scene::ITriangleSelector* selector = 0;
  if(mapNode) {
    mapNode->setPosition(irr::core::vector3df(-1300, -144, -1249));
    mapNode->setPosition(irr::core::vector3df(-1350,-130,-1400));
    selector = smgr->createOctreeTriangleSelector(
				mapNode->getMesh(), mapNode, 128);
    mapNode->setTriangleSelector(selector);    
  }
  level1 = new Level(dev, mapNode);
  soundManager->startMusic("media/music/flight.mp3", smgr->getActiveCamera()->getPosition());
}


void GameState::update(float dt)
{
  level1->update(dt);
  //soundManager->updateMusic(smgr->getActiveCamera()->getPosition());
}


