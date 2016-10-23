#include "Sydney.h"

const std::string Sydney::MEDIA_PATH = "media/sydney.md2";

Sydney::Sydney(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id) :
Npc(level,MEDIA_PATH, position, rotation, id)
{
  std::cout << ("hello") << std::endl;
}
