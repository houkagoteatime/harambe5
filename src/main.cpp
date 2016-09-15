#include <irrlicht.h>
#include "entities/Player.h"
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

int main(int argc, char **argv) {
	
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480));
	if(!device)
		return 1;
	device->setWindowCaption(L"Harambe 5: Summer School");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	/*
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if(!mesh) {
		device->drop();
		return 1;
	}
	
	irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if(node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
	}
	*/
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
	IAnimatedMesh* mapMesh = smgr->getMesh("20kdm2.bsp");
	IMeshSceneNode* mapNode;
	if(mapMesh) {
	  mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, 1);
	}
	
	irr::scene::ITriangleSelector* selector = 0;
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
// 	device->setEventReceiver(player->getProcessor());
	int start = device->getTimer()->getTime();
	int delta = 0;
	while(device->run()) {
	  delta = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
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

