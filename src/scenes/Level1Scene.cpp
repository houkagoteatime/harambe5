#include "Level1Scene.h"

Level1Scene::Level1Scene(Level* l):level(l)
{
  //points.push_back(core::vector3df(-931.473755f, 138.300003f, 987.279114f)); // -49873
  points.push_back(core::vector3df(-610.17,-9.69,-72.11));
  points.push_back(core::vector3df(-245.38,-1.76,-68.83));
  points.push_back(core::vector3df(82.40,24.38,-46.65));
  points.push_back(core::vector3df(82.40,24.38,-46.65));
  points.push_back(core::vector3df(105.31,382.61,-54.71));
  points.push_back(core::vector3df(-332.01,946.54,250.60));
  points.push_back(core::vector3df(681.604,1875.26,-1184.12));
  points.push_back(core::vector3df(681.604,1875.26,-1184.12));
  points.push_back(core::vector3df(681.604,1885.26,-1184.12));
  points.push_back(core::vector3df(681.604,1895.26,-1184.12));
  sceneStarted = false;
  
  gui = new Gui(level->getDevice());
}

Level1Scene::~Level1Scene()
{
  delete gui;
}


void Level1Scene::startScene()
{
  if(sceneStarted) {
    return;
  }
  cam = level ->getDevice()->getSceneManager()->addCameraSceneNode(0, points[0], core::vector3df(0 ,400,0));
  cam ->setTarget((irr::core::vector3df(0,400,0)));
  sa = level->getDevice()->getSceneManager()->createFollowSplineAnimator(level ->getDevice()->getTimer()->getTime(),points);
  cam->addAnimator(sa);
  gui->addStaticText("WELCOME TO HARAMBE 5", true);
  sceneStarted = true;
}






























