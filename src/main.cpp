#include <irrlicht.h>
#include "entities/Player.h"
#include <iostream>
#include "entities/Enemy.h"
#include "entities/Npc.h"
#include <vector>
#include "states/StateManager.h"
#include <irrKlang.h>

#include "input/EventReceiver.h"
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

// Main entry point
int main(int argc, char **argv) {
	
	// Create Irrilicht Device
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480),16, false, false, false);
	// Exit if device creation failed
	if(!device)
		return 1;
	device->setWindowCaption(L"Harambe 5: The Labyrinth");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	// Load maps
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
	device->getFileSystem()->addFileArchive("media/maps/lemap.pk3");
	StateManager manager(device);
	int prev = device->getTimer()->getTime();
	int current = 0;
	// Main game loop
	while(device->run()) {
	  
	  States appState = manager.getState();
	  current = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		manager.update((current - prev));
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
