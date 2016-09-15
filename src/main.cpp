#include <irrlicht.h>
#include "entities/Player.h"
#include <iostream>
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

int main(int argc, char **argv) {
	
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480));
	if(!device)
		return 1;
	device->setWindowCaption(L"Harambe 5: Summer School");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if(!mesh) {
		device->drop();
		return 1;
	}
	
	irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh,
	0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	if(node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
		node->setPosition(core::vector3df(-90,-15,-140)); // Put its feet on the floor.
		node->setScale(core::vector3df(1.6f)); // Make it appear realistically scaled
		node->setMD2Animation(scene::EMAT_POINT);
		node->setAnimationSpeed(20.f);
		//node->setID(666);
	}
	
	irr::scene::ITriangleSelector* selector = 0;
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop(); // We're done with this selector, so drop it now.
	
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
	IAnimatedMesh* mapMesh = smgr->getMesh("20kdm2.bsp");
	IMeshSceneNode* mapNode;
	if(mapMesh) {
	  mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, 1);
	}
	
	//irr::scene::ITriangleSelector* selector = 0;
	if(mapNode)
	{
	  mapNode->setPosition(vector3df(-1300, -144, -1249));
	  mapNode->setPosition(irr::core::vector3df(-1350,-130,-1400));

		selector = device->getSceneManager()->createOctreeTriangleSelector(
				mapNode->getMesh(), mapNode, 128);
		mapNode->setTriangleSelector(selector);
		// We're not done with this selector yet, so don't drop it.
	}
	
	Player* player = new Player(device,"media/gun.md2", vector3df(0,15,0),vector3df(0,0,0), mapNode, 0);
 	//device->setEventReceiver(player->getProcessor());
	int start = device->getTimer()->getTime();
	int delta = 0;
	
	
	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("../../media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	
	
	
	while(device->run()) {
	  delta = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		
		if (highlightedSceneNode)
		{
			highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
			highlightedSceneNode = 0;
		}

		// All intersections in this example are done with a ray cast out from the camera to
		// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
		// trajectory or a sword's position, or create a ray from a mouse click position using
		// ISceneCollisionManager::getRayFromScreenCoordinates()
		core::line3d<f32> ray;
		ray.start = smgr->getActiveCamera()->getPosition();
		ray.end = ray.start + (smgr->getActiveCamera()->getTarget() - ray.start).normalize() * 1000.0f;

		// Tracks the current intersection point with the level or a mesh
		core::vector3df intersection;
		// Used to show with triangle has been hit
		core::triangle3df hitTriangle;

		// This call is all you need to perform ray/triangle collision on every scene node
		// that has a triangle selector, including the Quake level mesh.  It finds the nearest
		// collision point/triangle, and returns the scene node containing that point.
		// Irrlicht provides other types of selection, including ray/triangle selector,
		// ray/box and ellipse/triangle selector, plus associated helpers.
		// See the methods of ISceneCollisionManager
		scene::ISceneNode * selectedSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
					ray,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					IDFlag_IsPickable, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0); // Check the entire scene (this is actually the implicit default)

		// If the ray hit anything, move the billboard to the collision position
		// and draw the triangle that was hit.
		if(selectedSceneNode)
		{
			if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
			{
			 highlightedSceneNode = selectedSceneNode;
			 if(smgr->getActiveCamera()->getPosition().getDistanceFrom(highlightedSceneNode->getPosition()) < 100) {
			   
			      std::cout << "hit" << delta << "\n";
			      highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
			 }
			}
			bill->setPosition(intersection);

		}
		
		player->update((delta - start)/1000.0f);
		smgr->drawAll();
		driver->endScene();
	  } else 
	      device->yield();
	  start = delta;
	}
	
	device->drop();
	return 0;

}

