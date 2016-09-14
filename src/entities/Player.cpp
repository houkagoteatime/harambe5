
#include "Player.h"

Player::Player(irr::IrrlichtDevice* dev, 
	       const std::string& mediaPath, 
	       irr::core::vector3df position, 
	       irr::core::vector3df rotation) : 
	       Entity(mediaPath, position, rotation), 
	       device(dev) {

  proc = new InputProcessor();
  initialize();
}

Player::~Player()
{
  if(proc)
    delete proc;
}

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1
};

void Player::update(float delta) {
  if(proc->isKeyDown(irr::KEY_KEY_W)) {
//    pos.Z += delta * SPEED; 
  }
  else if(proc->isKeyDown(irr::KEY_KEY_S)) {
//     pos.Z -= delta * SPEED;
  }
  if(proc->isKeyDown(irr::KEY_KEY_A)) {
//     pos.X -= delta * SPEED;
  }
  else if(proc->isKeyDown(irr::KEY_KEY_D)) { 
//     pos.X += delta * SPEED;
  }
//   camera->setPosition(pos);
}

void Player::initialize() 
{
  irr::scene::ISceneManager* manager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::SKeyMap keys[4];
  keys[0].Action = irr::EKA_MOVE_FORWARD;
  keys[0].KeyCode = irr::KEY_KEY_W;
  keys[1].Action = irr::EKA_MOVE_BACKWARD;
  keys[1].KeyCode = irr::KEY_KEY_S;
  keys[2].KeyCode = irr::KEY_KEY_A;
  keys[2].Action = irr::EKA_STRAFE_LEFT;
  keys[3].KeyCode = irr::KEY_KEY_D;
  keys[3].Action = irr::EKA_STRAFE_RIGHT;
  camera = manager->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keys, 4, true, 3.f);
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
  
  //collision
  
   device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
   irr::scene::IAnimatedMesh* q3levelmesh = manager->getMesh("20kdm2.bsp");
   irr::scene::IMeshSceneNode* q3node = 0;
  
  if (q3levelmesh)
		q3node = manager->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);

  
  irr::scene::ITriangleSelector* selector = 0;

	if (q3node)
	{
		q3node->setPosition(irr::core::vector3df(0,0,0));

		selector = device->getSceneManager()->createOctreeTriangleSelector(
				q3node->getMesh(), q3node, 128);
		q3node->setTriangleSelector(selector);
		// We're not done with this selector yet, so don't drop it.
	}
  camera->setTarget(irr::core::vector3df(-70,30,-60));
  
  if (selector)
	{
		irr::scene::ISceneNodeAnimator* anim = manager->createCollisionResponseAnimator(
			selector, camera, irr::core::vector3df(30,50,30),
			irr::core::vector3df(0,-10,0), irr::core::vector3df(0,30,0));
		selector->drop(); // As soon as we're done with the selector, drop it.
		camera->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
	}
}

InputProcessor* Player::getProcessor()
{
  return proc;
}
