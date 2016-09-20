#pragma once
#include <irrlicht.h>
#define dropElement(x)	if (x) { x->remove(); x = 0; }
#include <string>
#include "Gui.h"
class MenuGui : public Gui {
  
public:
  MenuGui(irr::IrrlichtDevice* dev);
  void addImage(bool visible);
  void addInstructionText(std::string,bool visible);
  

};