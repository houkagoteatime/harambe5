#include "InputProcessor.h"

InputProcessor::InputProcessor()
{
  for(int i = 0; i <irr::KEY_KEY_CODES_COUNT; i++) {
    keyIsDown[i] = false;
  }
}

InputProcessor::~InputProcessor()
{

}

bool InputProcessor::OnEvent(const irr::SEvent& event)
{
  if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
    keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
}

bool InputProcessor::isKeyDown(irr::EKEY_CODE code)
{
  return keyIsDown[code];
}
