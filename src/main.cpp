#include <irrlicht.h>
#include "entities/Player.h"
#include <iostream>
#include "entities/Enemy.h"
#include "EventReceiver.h"
#include "entities/Npc.h"
#include <vector>

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
	
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if(!mesh) {
		device->drop();
		return 1;
	}
	irr::scene::ITriangleSelector* selector = 0;
	
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
	

	
 	device->setEventReceiver(player->getEventReceiver());
	
	EventReceiver* receiver = player->getEventReceiver();
	Npc* testNpc = new Npc(device,"media/sydney.md2", vector3df(-90,-15,-140), vector3df(0,0,0), mapNode);
	Enemy* testEnemy = new Enemy(device,"media/sydney.md2", vector3df(30, 15, 30), vector3df(0,0,0), mapNode);
	testEnemy->setPlayer(player);
	testNpc->setPlayer(player);
	int prev = device->getTimer()->getTime();
	int current = 0;
	
	std::vector <Npc*> npcs;
	npcs.push_back(testNpc);
	while(device->run()) {
	  current = device->getTimer()->getTime();
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		
		
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
		  highlightedSceneNode = selectedSceneNode;
		  string<irr::c8> name = selectedSceneNode->getName();
		    int i = 0;
		    for(i = 0; i < npcs.size(); i++) {
			{
			   if(name == "Sydney") {
			    npcs[i]->onClick(receiver->GetMouseState()->LeftButtonDown);
			   }
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

