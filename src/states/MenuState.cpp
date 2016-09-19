#include "MenuState.h"

MenuState::MenuState(irr::IrrlichtDevice* dev): State(dev)
{
  //@@@@@@@@@@@@@@@@@@@@@@@
  receiver = new EventReceiver();
  gui = new Gui(dev);
  dev->setEventReceiver(receiver);
  currentState = MENU;
  init();
}


MenuState::~MenuState()
{
  if(gui) {
    gui->clear();
    delete gui;
  }
}

void MenuState::init()
{
 gui->setVisibleImage(true);
 gui->setVisibleStartButton(true);
}


void MenuState::update(float dt)
{
  if(receiver->start == true) {
   currentState = GAME; 
   gui->clear();
  }
}
