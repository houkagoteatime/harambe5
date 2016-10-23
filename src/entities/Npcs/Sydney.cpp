#include "Sydney.h"

const std::string Sydney::MEDIA_PATH = "media/sydney.md2";
const char* Sydney::DIALOGUE_PATH = "assets/data/sydney.dat";

Sydney::Sydney(Level* level, irr::core::vector3df position, irr::core::vector3df rotation, int id) :
Npc(level,MEDIA_PATH, position, rotation, id, DIALOGUE_PATH)
{
  std::cout << ("hello") << std::endl;
}
