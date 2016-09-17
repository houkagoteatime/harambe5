#include "MenuState.h"

MenuState::MenuState(irr::IrrlichtDevice* dev): State(dev)
{
  currentState = MENU;
}


MenuState::~MenuState()
{

}

void MenuState::update(float dt)
{

}
