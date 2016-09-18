#pragma once
#include <irrlicht.h>
#define dropElement(x)	if (x) { x->remove(); x = 0; }
#include <string>
class Gui {
  
public:
  Gui(irr::IrrlichtDevice* dev);
  void setVisibleImage(bool visible);
  void setVisibleStaticText(bool visible);
  void clear();
  void loadGuiElements();
  void addStaticText(std::string s);
  
private:
  int width,height;
  irr::gui::IGUIEnvironment* gui;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneManager* manager;
  irr::video::IVideoDriver* driver;
  struct guiElements {};
};