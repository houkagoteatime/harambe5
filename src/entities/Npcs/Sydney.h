#pragma once

#include <irrlicht.h>
#include "../Npc.h"
class Sydney : public Npc {
public:
  Sydney(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id);
private:
  static const std::string MEDIA_PATH;
};
