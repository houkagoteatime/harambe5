#pragma once
#include <irrlicht.h>
#include "../ui/Gui.h"
enum States {
  MENU,
  GAME
};

class State {
protected :
    States currentState;
    irr::IrrlichtDevice* dev;
    irr::scene::ISceneManager* smgr;
    Gui* gui;
public:
  State(irr::IrrlichtDevice* dev);
  virtual ~State();
  virtual void update(float dt) = 0;
  States getState() const;
};
