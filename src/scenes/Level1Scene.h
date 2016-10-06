#include <irrlicht.h>
#include "../levels/Level.h"
class Level;
using namespace irr;

class Level1Scene {
  
public:
  core::array<core::vector3df> points;
  Level1Scene(Level* l);
  ~Level1Scene();
  Level* level;
  void startScene();
  bool sceneStarted;
  void deleteGui();
  irr::scene::ISceneNodeAnimator* sa;
  irr::scene::ICameraSceneNode* cam;
  Gui* gui;
};