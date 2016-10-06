#include "MenuGui.h"


MenuGui::MenuGui(irr::IrrlichtDevice* dev):Gui(dev)
{
  addImage(true);
  addStartButton(true);
  addInstructionText("WASD MOVE :: CLICK/FIRE TO INTERACT", true);
}

void MenuGui::addImage(bool visible)
{
  elements.Image = gui->addImage(driver->getTexture("assets/images/harambe.jpg"),irr::core::position2d<int>(0,0));
  irr::gui::IGUIFont* font = gui->getFont("media/bigfont.png");
  if(font) {
    gui->getSkin()->setFont(font);
  }
  
  elements.Image->setVisible(visible);
}

void MenuGui::addInstructionText(std::string text, bool visible)
{
  if(elements.instructionText) {
    elements.instructionText->remove();
  }
  std::wstring wideText = std::wstring(text.begin(), text.end());
  const wchar_t* wideCText = wideText.c_str();
  elements.instructionText = gui->addStaticText(wideCText, 
  irr::core::rect<irr::s32>(width/16, height * 0.8, width - (width/16), height * 0.95),  true);
  elements.instructionText->setMinSize(irr::core::dimension2d<irr::u32>(20,20));
  elements.instructionText->setBackgroundColor(irr::video::SColor(192,255,192,203));
  elements.instructionText->setWordWrap(true);
  elements.instructionText->setTextRestrainedInside(true);
  elements.instructionText->setVisible(visible);
}
