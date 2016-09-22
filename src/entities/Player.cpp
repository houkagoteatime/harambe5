
#include "Player.h"

Player::Player(Level* level, const std::string& mediaPath,  irr::core::vector3df position,  irr::core::vector3df rotation, irr::scene::IMeshSceneNode* map) : 
	       Entity(level, mediaPath, position, rotation, map, -1)
	       {
  receiver = new EventReceiver();
  device = level->getDevice();
  device->setEventReceiver(receiver);
  initialize();
  jumpDelay = 0;
}

Player::~Player()
{
  if(receiver)
    delete receiver;
}

void Player::update(float delta) {
  
 if((device->getTimer()->getTime() - jumpDelay) > 2000) {
  if(receiver->m.spaceKeyDown) {
    jumpDelay = device->getTimer()->getTime();
    jump();
  }
 }
 
}

void Player::jump()
{
    camera->setPosition(irr::core::vector3df(camera->getPosition().X, camera->getPosition().Y + 5, camera->getPosition().Z));
  
}

void Player::attack()
{
  if(receiver->GetMouseState()->LeftButtonDown) {
     
  }
}

void Player::initialize() 
{
  jumpDelay = device->getTimer()->getTime();
  driver = device->getVideoDriver();
  irr::SKeyMap keys[6];
  keys[0].Action = irr::EKA_MOVE_FORWARD;
  keys[0].KeyCode = irr::KEY_KEY_W;
  keys[1].Action = irr::EKA_MOVE_BACKWARD;
  keys[1].KeyCode = irr::KEY_KEY_S;
  keys[2].KeyCode = irr::KEY_KEY_A;
  keys[2].Action = irr::EKA_STRAFE_LEFT;
  keys[3].KeyCode = irr::KEY_KEY_D;
  keys[3].Action = irr::EKA_STRAFE_RIGHT;
  keys[4].KeyCode = irr::KEY_SPACE;
  keys[4].Action = irr::EKA_JUMP_UP;
  keys[5].KeyCode = irr::KEY_SHIFT;
  keys[5].Action = irr::EKA_CROUCH;
  camera = manager->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keys, 6, false, 10.0f);
  if(camera) {
    camera->setPosition(pos);
    camera->setRotation(rot);
    camera->setFarValue(8000.0f);
  }
  irr::scene::IAnimatedMeshMD2* weapon = static_cast<irr::scene::IAnimatedMeshMD2*>(manager->getMesh("media/gun.md2"));
  weaponNode = manager->addAnimatedMeshSceneNode(weapon, manager->getActiveCamera(), 10	, irr::core::vector3df(0, 0, 0), irr::core::vector3df(-90, -90, 90));
  weaponNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  weaponNode->setMaterialTexture(0, driver->getTexture("media/gun.jpg"));
  weaponNode->setLoopMode(true);
  addCollision();
  addBillboard();
}

void Player::addCollision()
{
  irr::scene::ISceneNodeAnimator* anim = manager->createCollisionResponseAnimator( mapNode->getTriangleSelector(), camera, irr::core::vector3df(30,50,30),irr::core::vector3df(0,-9.8,0),irr::core::vector3df(0,30,0),0.0005f);
  camera->addAnimator(anim);
  anim->drop();
  device->getCursorControl()->setVisible(false);
}
void Player::addBillboard()
{
	
	bill = manager->addBillboardSceneNode();
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZBUFFER, false);
	bill->setSize(irr::core::dimension2d<irr::f32>(20.0f, 20.0f));
	bill->setID(0);
}

irr::scene::ICameraSceneNode* Player::getCamera()
{
  return camera;
}

EventReceiver* Player::getEventReceiver()
{
  return receiver;
}

irr::scene::IBillboardSceneNode* Player::getBillBoard()
{
  return bill;
}

