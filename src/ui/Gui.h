#pragma once
#include <irrlicht.h>
#define dropElement(x)	if (x) { x->remove(); x = 0; }
#include <string>
class Gui {
  
public:
  Gui(irr::IrrlichtDevice* dev);
  ~Gui();
  void setVisibleImage(bool visible);
  void setVisibleStaticText(bool visible);
  void loadGuiElements();
  void addStaticText(std::string s);
  void addStartButton();
  void addImage();
  void setVisibleStartButton(bool visible);
  
private:
  int width,height;
  irr::gui::IGUIEnvironment* gui;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneManager* manager;
  irr::video::IVideoDriver* driver;
  struct guiElements {};
};