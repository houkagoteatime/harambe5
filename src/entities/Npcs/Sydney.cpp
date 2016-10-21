#include "Sydney.h"

Sydney::Sydney(Level* level, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map, int id) :
Npc(level,mediaPath, position, rotation,map, id)
{
  std::cout << ("hello") << std::endl;
}
