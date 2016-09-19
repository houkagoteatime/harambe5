#include "Gui.h"

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
	}
	
	irr::gui::IGUIImage* Image;
	irr::gui::IGUIWindow* Window;
	irr::gui::IGUIStaticText* staticText;
	irr::gui::IGUIButton* startButton;
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
  elements.Image = gui->addImage(driver->getTexture("media/MonkeyHeaven.png"),irr::core::position2d<int>(0,0));
  irr::gui::IGUIFont* font = gui->getFont("media/bigfont.png");
  if(font) {
    gui->getSkin()->setFont(font);
  }
  addImage();
  addStartButton();
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
  elements.staticText = gui->addStaticText(wideCText, 
  irr::core::rect<irr::s32>(width/8, height * 0.8, width - (width/8), height * 0.9), 
					   true);
  elements.staticText->setMinSize(irr::core::dimension2d<irr::u32>(20,20));
  elements.staticText->setBackgroundColor(irr::video::SColor(192,192,192,192));
  elements.staticText->setWordWrap(true);
  elements.staticText->setVisible(false);
}


void Gui::setVisibleImage(bool visible)
{
  elements.Image->setVisible(visible);
}

void Gui::addImage()
{
  //elements.Image = gui->addImage(driver->getTexture("media/monkey.png"),irr::core::position2d<int>(20,20));
  setVisibleImage(false);
}

void Gui::addStartButton()
{
  //999 = id
  elements.startButton = gui->addButton(
  irr::core::rect<irr::s32>((width/3) + 20, height * 0.4, (width*0.666), height * 0.5), 
  0, 999, L"START", L"Enter the dungeon of Dank MEmes");
  setVisibleStartButton(false);
}

void Gui::setVisibleStartButton(bool visible)
{
  elements.startButton->setVisible(visible);
}

void Gui::clear() 
{
  elements.drop();
}