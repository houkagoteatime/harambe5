#include <irrlicht.h>
#include "entities/Player.h"
#include <iostream>
#include "entities/Enemy.h"
#include "EventReceiver.h"
#include "entities/Npc.h"
#include <vector>
#include "states/StateManager.h"
#include <irrKlang.h>
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
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1,
	IDFlag_IsHighlightable = 2
};

int main(int argc, char **argv) {

	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480),16, false, false, false);
	if(!device)
		return 1;
	device->setWindowCaption(L"Harambe 5: The Labyrinth");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");

	StateManager manager(device);
	int prev = device->getTimer()->getTime();
	int current = 0;
	while(device->run()) {
	  
	  States appState = manager.getState();
	  current = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		manager.update((current - prev)/1000.0f);
		smgr->drawAll();
		device->getGUIEnvironment()->drawAll();
		driver->endScene();
	  } else 
	      device->yield();
	  prev = current;
	}
	device->drop();
	return 0;

}
