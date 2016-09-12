#include <irrlicht.h>

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
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if(!mesh) {
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if(node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
	}
	device->getFileSystem()->addFileArchive("media/mxl_school.pk3");
	IAnimatedMesh* mapMesh = smgr->getMesh("mxl_school.bsp");
	ISceneNode* mapNode = 0;
	if(mapMesh) {
	  mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0),0, -1, 1024);
	}
	if(mapNode)
	  mapNode->setPosition(vector3df(-1300, -144, -1249));
	smgr->addCameraSceneNodeFPS();
	while(device->run()) {
	  if(device->isWindowActive()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		smgr->drawAll();
		driver->endScene();
	  } else 
	      device->yield();
	}
	
	device->drop();
	return 0;

}

