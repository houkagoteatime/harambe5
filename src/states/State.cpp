#include "State.h"

State::State(irr::IrrlichtDevice* dev) : dev(dev)
{
  smgr = dev->getSceneManager();
  guienv = dev->getGUIEnvironment();
}

State::~State()
{

}

States State::getState() const
{
  return currentState;
}
