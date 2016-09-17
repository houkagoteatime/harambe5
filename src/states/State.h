#pragma once
#include <irrlicht.h>
enum States {
  MENU,
  GAME
};

class State {
protected :
    States currentState;
    irr::IrrlichtDevice* dev;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIEnvironment* guienv;
public:
  State(irr::IrrlichtDevice* dev);
  virtual ~State();
  virtual void update(float dt) = 0;
  States getState() const;
};
