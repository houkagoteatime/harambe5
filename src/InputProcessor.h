#pragma once
#include <irrlicht.h>

class InputProcessor : public irr::IEventReceiver{
public:
  InputProcessor();
  ~InputProcessor();
  virtual bool OnEvent(const irr::SEvent& event);
  virtual bool isKeyDown(irr::EKEY_CODE code);
private:
  bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
};