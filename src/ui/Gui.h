#pragma once
#include <irrlicht.h>
#define dropElement(x)	if (x) { x->remove(); x = 0; }
#include <string>
#include "../GuiValues.h"
class Gui {
  
public:
  Gui(irr::IrrlichtDevice* dev);
  ~Gui();
  virtual void setVisibleImage(bool visible);
  virtual void setVisibleStaticText(bool visible);
  virtual void addStaticText(std::string s, bool visible);
  virtual void addStartButton(bool visible);
  virtual void addImage(bool visible);
  virtual void setVisibleStartButton(bool visible);
  
protected:
  int width,height;
  irr::gui::IGUIEnvironment* gui;
  irr::IrrlichtDevice* device;
  irr::scene::ISceneManager* manager;
  irr::video::IVideoDriver* driver;
  struct guiElements
  {
	guiElements ()
	{
		memset ( this, 0, sizeof ( *this ) );
	}
	void drop()
	{
		dropElement(Window);
		dropElement(Image);
		dropElement(staticText);
		dropElement(startButton);
		dropElement(instructionText);
		
	}
	irr::gui::IGUIImage* Image;
	irr::gui::IGUIWindow* Window;
	irr::gui::IGUIStaticText* staticText;
	irr::gui::IGUIStaticText* instructionText;
	irr::gui::IGUIButton* startButton;
	
  }elements;
};