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
  //printf("donezo");
  if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
    keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
  return false;
}

bool InputProcessor::isKeyDown(irr::EKEY_CODE code)
{
  return keyIsDown[code];
}
