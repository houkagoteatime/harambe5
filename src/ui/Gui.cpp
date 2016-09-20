#include "Gui.h"

Gui::Gui(irr::IrrlichtDevice* dev):device(dev)
{
  manager = device->getSceneManager();
  driver = device->getVideoDriver();
  gui = device->getGUIEnvironment();
  height = driver->getScreenSize().Height;
  width = driver->getScreenSize().Width;
  
}

Gui::~Gui()
{
  elements.drop();
}

void Gui::addStaticText(std::string text, bool visible)
{
  if(elements.staticText) {
    elements.staticText->remove();
  }
  std::wstring wideText = std::wstring(text.begin(), text.end());
  const wchar_t* wideCText = wideText.c_str();
  elements.staticText = gui->addStaticText(wideCText, 
  irr::core::rect<irr::s32>(width/8, height * 0.8, width - (width/8), height * 0.9),  true);
  elements.staticText->setMinSize(irr::core::dimension2d<irr::u32>(20,20));
  elements.staticText->setBackgroundColor(irr::video::SColor(192,192,192,192));
  elements.staticText->setWordWrap(true);
  elements.staticText->setVisible(visible);
}

void Gui::addStartButton(bool visible)
{
  elements.startButton = gui->addButton(
  irr::core::rect<irr::s32>((width/3) + 20, height * 0.4, (width*0.666), height * 0.5), 
  0, GuiValues::START_BUTTON, L"START", L"Enter the dungeon of Dank MEmes");
  setVisibleStartButton(visible);
}

void Gui::addImage(bool visible)
{
  setVisibleImage(visible);
}

void Gui::setVisibleStaticText(bool visible)
{
  elements.staticText->setVisible(visible);
}

void Gui::setVisibleImage(bool visible)
{
  elements.Image->setVisible(visible);
}


void Gui::setVisibleStartButton(bool visible)
{
  elements.startButton->setVisible(visible);
}
