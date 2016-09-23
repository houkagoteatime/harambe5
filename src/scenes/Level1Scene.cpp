#include "Level1Scene.h"

Level1Scene::Level1Scene(Level* l):level(l)
{
  points.push_back(core::vector3df(-931.473755f, 138.300003f, 987.279114f)); // -49873
			points.push_back(core::vector3df(-847.902222f, 136.757553f, 915.792725f)); // -50559
			points.push_back(core::vector3df(-748.680420f, 152.254501f, 826.418945f)); // -51964
			points.push_back(core::vector3df(-708.428406f, 213.569580f, 784.466675f)); // -53251
			points.push_back(core::vector3df(-686.217651f, 288.141174f, 762.965576f)); // -54015
			points.push_back(core::vector3df(-679.685059f, 365.095612f, 756.551453f)); // -54733
			points.push_back(core::vector3df(-671.317871f, 447.360107f, 749.394592f)); // -55588
			points.push_back(core::vector3df(-669.468445f, 583.335632f, 747.711853f)); // -56178
			points.push_back(core::vector3df(-667.611267f, 727.313232f, 746.018250f)); // -56757
			points.push_back(core::vector3df(-665.853210f, 862.791931f, 744.436096f)); // -57859
			points.push_back(core::vector3df(-642.649597f, 1026.047607f, 724.259827f)); // -59705
			points.push_back(core::vector3df(-517.793884f, 838.396790f, 490.326050f)); // -60983
			points.push_back(core::vector3df(-474.387299f, 715.691467f, 344.639984f)); // -61629
			points.push_back(core::vector3df(-444.600250f, 601.155701f, 180.938095f)); // -62319
			points.push_back(core::vector3df(-414.808899f, 479.691406f, 4.866660f)); // -63048
			points.push_back(core::vector3df(-410.418945f, 429.642242f, -134.332687f)); // -63757
			points.push_back(core::vector3df(-399.837585f, 411.498383f, -349.350983f)); // -64418
			points.push_back(core::vector3df(-390.756653f, 403.970093f, -524.454407f)); // -65005
			points.push_back(core::vector3df(-334.864227f, 350.065491f, -732.397400f)); // -65701
			points.push_back(core::vector3df(-195.253387f, 349.577209f, -812.475891f)); // -66335
			points.push_back(core::vector3df(16.255573f, 363.743134f, -833.800415f)); // -67170
			points.push_back(core::vector3df(234.940964f, 352.957825f, -820.150696f)); // -67939
			points.push_back(core::vector3df(436.797668f, 349.236450f, -816.914185f)); // -68596
			points.push_back(core::vector3df(575.236206f, 356.244812f, -719.788513f)); // -69166
			points.push_back(core::vector3df(594.131042f, 387.173828f, -609.675598f)); // -69744
			points.push_back(core::vector3df(617.615234f, 412.002899f, -326.174072f)); // -70640
			points.push_back(core::vector3df(606.456848f, 403.221954f, -104.179291f)); // -71390
			points.push_back(core::vector3df(610.958252f, 407.037750f, 117.209778f)); // -72085
			points.push_back(core::vector3df(597.956909f, 395.167877f, 345.942200f)); // -72817
			points.push_back(core::vector3df(587.383118f, 391.444519f, 566.098633f)); // -73477
			points.push_back(core::vector3df(559.572449f, 371.991333f, 777.689453f)); // -74124
			points.push_back(core::vector3df(423.753204f, 329.990051f, 925.859741f)); // -74941
			points.push_back(core::vector3df(247.520050f, 252.818954f, 935.311829f)); // -75651
			points.push_back(core::vector3df(114.756012f, 199.799759f, 805.014160f));
			points.push_back(core::vector3df(96.783348f, 181.639481f, 648.188110f));
			points.push_back(core::vector3df(97.865623f, 138.905975f, 484.812561f));
			points.push_back(core::vector3df(99.612457f, 102.463669f, 347.603210f));
			points.push_back(core::vector3df(99.612457f, 102.463669f, 347.603210f));
			points.push_back(core::vector3df(99.612457f, 102.463669f, 347.603210f));
			sceneStarted = false;
}

void Level1Scene::startScene()
{
  if(sceneStarted) {
    return;
  }
  irr::scene::ICameraSceneNode* cam = level ->getDevice()->getSceneManager()->addCameraSceneNode(0, points[0], core::vector3df(0 ,400,0));
  cam ->setTarget((irr::core::vector3df(0,400,0)));
  irr::scene::ISceneNodeAnimator* sa = level->getDevice()->getSceneManager()->createFollowSplineAnimator(level ->getDevice()->getTimer()->getTime(),points);
  cam->addAnimator(sa);
  sa ->drop();
  sceneStarted = true;
}






























