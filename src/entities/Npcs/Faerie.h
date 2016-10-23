#pragma once

#include <irrlicht.h>
#include "../Npc.h"
class Faerie : public Npc {
public:
  Faerie(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id);
  void dialogue(bool MouseEvent);
private:
  static const std::string MEDIA_PATH;
  static const char* DIALOGUE_PATH;
};
