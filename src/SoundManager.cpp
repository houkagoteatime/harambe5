#include "SoundManager.h"

SoundManager::SoundManager()
{
  engine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
  if(music)
    music->drop();
  engine->drop();
}

void SoundManager::startMusic(const char* musicName, irrklang::vec3df pos)
{
  music = engine->play3D(musicName, pos, true, false, true);
  music->setMinDistance(5.0f);
}

void SoundManager::updateMusic(irrklang::vec3df pos)
{
  engine->setListenerPosition(pos, irrklang::vec3df(0,1,0));
  music->setPosition(pos);
}
