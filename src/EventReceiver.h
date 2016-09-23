#pragma once

#include <irrlicht.h>
#include <iostream>
#include <cstdio>
#include <ctime>

class EventReceiver : public irr::IEventReceiver {
public:
  EventReceiver();
  typedef struct MouseState
  {
    irr::core::position2di Position;
    bool LeftButtonDown;
    bool spaceKeyDown;
  }MouseState;
  std::clock_t start;
  MouseState m;
  const EventReceiver::MouseState* GetMouseState(void);
  virtual bool OnEvent(const irr::SEvent& event);
};