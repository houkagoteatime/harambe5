#pragma once
#include <irrlicht.h>
#include "../ui/MenuGui.h"
enum States {
  MENU,
  GAME
};

class State {
protected :
    irr::IrrlichtDevice* dev;
    irr::scene::ISceneManager* smgr;
    MenuGui* menuGui;
public:
  State(irr::IrrlichtDevice* dev);
  virtual ~State();
  virtual void update(float dt) = 0;
  States getState() const;
  States currentState;
};
