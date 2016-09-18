#include "Gui.h"

struct guiElements
{
	guiElements ()
	{
		memset ( this, 0, sizeof ( *this ) );
	}

	void drop()
	{
		dropElement ( Window );
		dropElement ( Image );
		dropElement( staticText);
	}
	
	irr::gui::IGUIImage* Image;
	irr::gui::IGUIWindow* Window;
	irr::gui::IGUIStaticText* staticText;
}elements;

Gui::Gui(irr::IrrlichtDevice* dev):device(dev)
{
  manager = device->getSceneManager();
  driver = device->getVideoDriver();
  gui = device->getGUIEnvironment();
  
  height = driver->getScreenSize().Height;
  width = driver->getScreenSize().Width;
  
  loadGuiElements();
}

void Gui::loadGuiElements()
{
  elements.Image = gui->addImage(driver->getTexture("media/irrlichtlogo2.png"),irr::core::position2d<int>(20,20));
  std::string text = "test";
  std::wstring wideText = std::wstring(text.begin(), text.end());
  const wchar_t* wideCText = wideText.c_str();
  irr::core::rect<irr::s32> box(width/8, height * 0.8, width - (width/8), height * 0.9);
  //elements.staticText = gui->addStaticText(wideCText, box, true);
  //elements.staticText->setMinSize(irr::core::dimension2d<irr::u32>(20,20));
  //elements.staticText->setBackgroundColor(irr::video::SColor(192,192,192,192));
  setVisibleImage(false);
  //setVisibleStaticText(false);
}

void Gui::setVisibleStaticText(bool visible)
{
  elements.staticText->setVisible(visible);
}

void Gui::addStaticText(std::string text)
{
  if(elements.staticText) {
    elements.staticText->remove();
  }
  std::wstring wideText = std::wstring(text.begin(), text.end());
  const wchar_t* wideCText = wideText.c_str();
  irr::core::rect<irr::s32> box(width/8, height * 0.8, width - (width/8), height * 0.9);
  elements.staticText = gui->addStaticText(wideCText, box, true);
  elements.staticText->setMinSize(irr::core::dimension2d<irr::u32>(20,20));
  elements.staticText->setBackgroundColor(irr::video::SColor(192,192,192,192));
}


void Gui::setVisibleImage(bool visible)
{
  elements.Image->setVisible(visible);
}

void Gui::clear() 
{
  elements.drop();
}

