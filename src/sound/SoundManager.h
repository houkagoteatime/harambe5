#pragma once
#include <irrKlang.h>

class SoundManager {
public:
  SoundManager();
  ~SoundManager();
  void startMusic(const char* musicName, irrklang::vec3df pos);
  void updateMusic(irrklang::vec3df pos);
private:
  irrklang::ISoundEngine* engine;
  irrklang::ISound* music;
};