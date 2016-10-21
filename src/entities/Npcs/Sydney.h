#pragma once

#include <irrlicht.h>
#include "../Npc.h"
class Sydney : public Npc {
public:
  Sydney(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id);
private:
  static const std::string MEDIA_PATH;
};
