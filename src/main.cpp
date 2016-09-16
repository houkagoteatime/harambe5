#include <irrlicht.h>
#include "entities/Player.h"
#include <iostream>
#include "entities/Enemy.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};

class MyEventReceiver : public IEventReceiver
{
public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}

		// The state of each connected joystick is sent to us
		// once every run() of the Irrlicht device.  Store the
		// state of the first joystick, ignoring other joysticks.
		// This is currently only supported on Windows and Linux.
		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
			&& event.JoystickEvent.Joystick == 0)
		{
			JoystickState = event.JoystickEvent;
		}

		return false;
	}

	const SEvent::SJoystickEvent & GetJoystickState(void) const
	{
		return JoystickState;
	}

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}


	MyEventReceiver()
	{
	}

private:
	SEvent::SJoystickEvent JoystickState;
};

int main(int argc, char **argv) {
	
  
	MyEventReceiver receiver;
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480),16, false, false, false, &receiver);
	if(!device)
		return 1;
	device->setWindowCaption(L"Harambe 5: The Labyrinth");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if(!mesh) {
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh);
	if(node) {
	  node ->setName("Sydney");
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
		node->setPosition(core::vector3df(-90,-15,-140)); // Put its feet on the floor.
		node->setScale(core::vector3df(1.6f)); // Make it appear realistically scaled
		//node->setMD2Animation(scene::EMAT_POINT);
		node->setAnimationSpeed(20.f);
	}
	irr::scene::ITriangleSelector* selector = 0;
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop(); // We're done with this selector, so drop it now.
	
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
	IAnimatedMesh* mapMesh = smgr->getMesh("20kdm2.bsp");
	IMeshSceneNode* mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, 1);
	if(mapNode)
	{
	  mapNode->setPosition(vector3df(-1300, -144, -1249));
	  mapNode->setPosition(irr::core::vector3df(-1350,-130,-1400));

		selector = device->getSceneManager()->createOctreeTriangleSelector(
				mapNode->getMesh(), mapNode, 128);
		mapNode->setTriangleSelector(selector);
	}
	
	Player* player = new Player(device,"media/gun.md2", vector3df(0,15,0),vector3df(0,0,0), mapNode);
	
	
	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	

	
// 	device->setEventReceiver(player->getProcessor());
	Enemy* testEnemy = new Enemy(device,"media/sydney.md2", vector3df(30, 15, 30), vector3df(0,0,0));
	testEnemy->setPlayer(player);
	int prev = device->getTimer()->getTime();
	int current = 0;
	while(device->run()) {
	  current = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		
		const SEvent::SJoystickEvent & joystickData = receiver.GetJoystickState();
		
		if (highlightedSceneNode)
		{
			highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
			highlightedSceneNode = 0;
		}

		core::line3d<f32> ray;
		ray.start = smgr->getActiveCamera()->getPosition();
		ray.end = ray.start + (smgr->getActiveCamera()->getTarget() - ray.start).normalize() * 1000.0f;

		core::vector3df intersection;
		core::triangle3df hitTriangle;
		scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection, hitTriangle, IDFlag_IsPickable,0);
		if(selectedSceneNode)
		{
		  string<irr::c8> name = selectedSceneNode->getName();
		  if(name == "Sydney") 
			{
			 highlightedSceneNode = selectedSceneNode;
			 if(smgr->getActiveCamera()->getPosition().getDistanceFrom(highlightedSceneNode->getPosition()) < 200) {
			      highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, receiver.GetMouseState().LeftButtonDown);
			 }
			}
		  bill->setPosition(intersection);
		}
		
		player->update((current - prev)/1000.0f);
		testEnemy->update((current - prev)/1000.0f);
		smgr->drawAll();
		driver->endScene();
	  } else 
	      device->yield();
	  prev = current;
	}
	
	device->drop();
	return 0;

}

