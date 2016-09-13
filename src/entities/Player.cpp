
#include "Player.h"

Player::Player(irr::IrrlichtDevice* dev, const std::string& mediaPath, irr::core::vector3df position, irr::core::vector3df rotation) : Entity(mediaPath, position, rotation), device(dev) {

  proc = new InputProcessor();
  initialize();
}

Player::~Player()
{
  if(proc)
    delete proc;
}

void Player::update(float delta) {
  if(proc->isKeyDown(irr::KEY_KEY_W)) {
   pos.Z += delta * SPEED; 
  }
  else if(proc->isKeyDown(irr::KEY_KEY_S)) {
    pos.Z -= delta * SPEED;
  }
  if(proc->isKeyDown(irr::KEY_KEY_A)) {
    pos.X -= delta * SPEED;
  }
  else if(proc->isKeyDown(irr::KEY_KEY_D)) { 
    pos.X += delta * SPEED;
  }
  camera->setPosition(pos);
}

void Player::initialize()
{
  irr::scene::ISceneManager* manager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  camera = manager->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);
  if(camera) {
    camera->setPosition(pos);
    camera->setRotation(rot);
    camera->setFarValue(8000.0f);
  }
  irr::scene::IAnimatedMeshMD2* weapon = static_cast<irr::scene::IAnimatedMeshMD2*>(manager->getMesh("media/gun.md2"));
  weaponNode = manager->addAnimatedMeshSceneNode(weapon, manager->getActiveCamera(), 10, irr::core::vector3df(0, 0, 0), irr::core::vector3df(-90, 90, 90));
  weaponNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  weaponNode->setMaterialTexture(0, driver->getTexture("media/gun.jpg"));
  weaponNode->setLoopMode(false);
}

InputProcessor* Player::getProcessor()
{
  return proc;
}
