#include "GuiEventReceiver.h"

GuiEventReceiver::GuiEventReceiver()
{
  start = false;
}


bool  GuiEventReceiver::OnEvent(const irr::SEvent& event)
{
  if (event.EventType == irr::EET_GUI_EVENT)
  {
    irr::s32 id = event.GUIEvent.Caller->getID();
    switch(event.GUIEvent.EventType)
    {
      case irr::gui::EGET_BUTTON_CLICKED:
      switch(id)
      {
	case GuiValues::START_BUTTON:
	  GuiVariables.start = true;
	  return true;
	default:
	break;
      }
    }
  }
  return false;
}


			
