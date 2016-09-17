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
	}
	
	irr::gui::IGUIImage* Image;
	irr::gui::IGUIWindow* Window;
}elements;

Gui::Gui(irr::IrrlichtDevice* dev):device(dev)
{
  manager = device->getSceneManager();
  driver = device->getVideoDriver();
  gui = device->getGUIEnvironment();
  loadGuiElements();
}

void Gui::loadGuiElements()
{
  elements.Image = gui->addImage(driver->getTexture("media/irrlichtlogo2.png"),irr::core::position2d<int>(20,20), false);
  elements.Image->setVisible(false);
}


void Gui::setVisibleImage(bool visible)
{
  elements.Image->setVisible(visible);
}

void Gui::clear() 
{
  //gui->clear();
  elements.Image->setVisible(false);
}

