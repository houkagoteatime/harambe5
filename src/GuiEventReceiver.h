#pragma once

#include <irrlicht.h>
#include "EventReceiver.h"
#include "GuiValues.h"
class GuiEventReceiver : public EventReceiver {
public:
  GuiEventReceiver();
  bool OnEvent(const irr::SEvent& event);
  bool start;
  struct GuiVariables {
  GuiVariables ()
    {
      memset ( this, 0, sizeof ( *this ) );
    }
  bool start;
  }GuiVariables;
private:
};