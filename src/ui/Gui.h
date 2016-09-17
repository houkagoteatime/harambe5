#pragma once
#include <irrlicht.h>
#define dropElement(x)	if (x) { x->remove(); x = 0; }
class Gui {
  
public:
  Gui(irr::IrrlichtDevice* dev);
  void setVisibleImage(bool visible);
  void clear();
  void loadGuiElements();
  
private:
  irr::gui::IGUIEnvironment* gui;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneManager* manager;
  irr::video::IVideoDriver* driver;
  struct guiElements {};
};