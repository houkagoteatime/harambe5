#include "EventReceiver.h"
#include <iostream>
EventReceiver::EventReceiver()
{
  m.LeftButtonDown = false;
  start = false;
}

EventReceiver::~EventReceiver()
{

}



const EventReceiver::MouseState* EventReceiver::GetMouseState(void)
{
  return &m;
}


bool EventReceiver::OnEvent(const irr::SEvent& event)
{
  
  if (event.EventType == irr::EET_GUI_EVENT)
    {
			irr::s32 id = event.GUIEvent.Caller->getID();

			switch(event.GUIEvent.EventType)
			{
			  case irr::gui::EGET_BUTTON_CLICKED:
				switch(id)
				{
				case 999:
					start = true;
				  std::cout << "@" << std::endl;
					return true;
				default:
				break;
				}
			}
		}
  if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
  {
  switch(event.MouseInput.Event)
  {
    case irr::EMIE_LMOUSE_PRESSED_DOWN:
      m.LeftButtonDown = true;
    break;

    case irr::EMIE_LMOUSE_LEFT_UP:
      m.LeftButtonDown = false;
    break;

    case irr::EMIE_MOUSE_MOVED:
      //m.Position.X = event.MouseInput.X;
     // m.Position.Y = event.MouseInput.Y;
    break;

    default:
    // We won't use the wheel
    break;
  }
  return false;
  
  }
}


			