#include "EventReceiver.h"
#include <iostream>
#include <string>
EventReceiver::EventReceiver()
{
  m.LeftButtonDown = false;
  m.spaceKeyDown = false;
  start = std::clock();
}

const EventReceiver::MouseState* EventReceiver::GetMouseState(void)
{
  return &m;
}


bool EventReceiver::OnEvent(const irr::SEvent& event)
{
  
  //m.spaceKeyDown = false;
  //if(event.EventType == irr::EET_KEY_INPUT_EVENT)
 // {
    //m.spaceKeyDown = event.KeyInput.Key == irr::KEY_SPACE;
  //m.spaceKeyDown = false;
 // }
  //if(!event.KeyInput.PressedDown) {
  //std::cout << event.KeyInput.PressedDown << std::endl;
  //if(event.KeyInput.PressedDown) {
    m.spaceKeyDown = false;
  //}
  //}
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

      default:
      break;
    } 
    return false;
  }
  else if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
    switch(event.KeyInput.Key) {
      case irr::KEY_SPACE:
	std::cout << "true" << std::endl;
	m.spaceKeyDown = true;
      break;
      default:
	break;
    }
      return false;
  
  }
  return true;
}


			