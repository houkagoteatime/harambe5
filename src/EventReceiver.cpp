#include "EventReceiver.h"
EventReceiver::EventReceiver()
{

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


			