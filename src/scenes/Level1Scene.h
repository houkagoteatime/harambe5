#include <irrlicht.h>
#include "../levels/Level.h"
class Level;
using namespace irr;

class Level1Scene {
  
public:
  core::array<core::vector3df> points;
  Level1Scene(Level* l);
  Level* level;
  void startScene();
  bool sceneStarted;
};