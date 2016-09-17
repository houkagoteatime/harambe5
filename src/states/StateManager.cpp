#include "StateManager.h"

StateManager::StateManager(irr::IrrlichtDevice* device) : dev(device)
{
  gameState = new GameState(dev);
  currentState = GAME;
}


StateManager::~StateManager()
{
  delete dev;
}


States StateManager::getState()
{
  return currentState;
}

void StateManager::update(float dt)
{
  if(!gameState)
    return;
  gameState->update(dt);
  if(gameState->getState() != currentState) {
    delete gameState;
    switch(currentState) {
      case MENU:
	gameState = new MenuState(dev);
	break;
      case GAME:
	gameState = new GameState(dev);
	break;
      default:
	break;
    }
  }
}
