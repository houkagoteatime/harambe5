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
  /*
  class GuiEventReceiver : public irr::IEventReceiver {
  public:
    GuiEventReceiver();
    ~GuiEventReceiver();
    GuiEventReceiver(Gui * g);
    virtual bool OnEvent(const irr::SEvent& event);
    Gui* gui;
  };
  */
};