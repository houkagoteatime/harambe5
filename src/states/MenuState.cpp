#include "MenuState.h"

MenuState::MenuState(irr::IrrlichtDevice* dev): State(dev)
{
  guiReceiver = new GuiEventReceiver();
  menuGui = new MenuGui(dev);
  dev->setEventReceiver(guiReceiver);
  currentState = MENU;
  init();
}


MenuState::~MenuState()
{
  if(menuGui) {
    delete menuGui;
  }
  if(guiReceiver){
    delete guiReceiver;
  }
}

void MenuState::init()
{
  
}


void MenuState::update(float dt)
{
  if(guiReceiver->GuiVariables.start == true) {
   currentState = GAME; 
  }
}
