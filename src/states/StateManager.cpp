#include "StateManager.h"
StateManager::StateManager(irr::IrrlichtDevice* device) : dev(device)
{
  gameState = new MenuState(dev);
  currentState = MENU;
  prevState = MENU;
}


StateManager::~StateManager()
{
  delete dev;
  if ( gameState != NULL )
	  delete gameState;
}


States StateManager::getState()
{
  return currentState;
}

States StateManager::getPrevState()
{
  return prevState;
}

void StateManager::update(float dt)
{
  if(!gameState)
    return;
  gameState->update(dt);
  States curr = gameState->getState();
  if(gameState->getState() != currentState) {
    delete gameState;
    switch(curr) {
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
  currentState = curr;
}
