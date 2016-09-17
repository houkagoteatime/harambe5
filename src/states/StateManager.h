#pragma once
#include <irrlicht.h>
#include "State.h"
#include "MenuState.h"
#include "GameState.h"
class StateManager {
public:
  StateManager(irr::IrrlichtDevice* device);
  ~StateManager();
  void update(float dt);
  States getState();
private:
  States currentState;
  State* gameState;
  irr::IrrlichtDevice* dev;
};