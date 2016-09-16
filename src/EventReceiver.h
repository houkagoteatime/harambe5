#pragma once

#include <irrlicht.h>
class EventReceiver : public irr::IEventReceiver {
public:
  EventReceiver();
 ~EventReceiver();
  typedef struct MouseState
  {
    irr::core::position2di Position;
    bool LeftButtonDown = false;
  }MouseState;
  MouseState m;
  const EventReceiver::MouseState* GetMouseState(void);
  virtual bool OnEvent(const irr::SEvent& event);
  
};