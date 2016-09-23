#ifndef SOUND_HH
#define SOUND_HH

#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <iostream>

class SoundManager
{
public:
  //SoundNames is an enum
  SoundManager();
  ~SoundManager();

  enum SoundNames
    {
      Death,
      SetBomb,
      BombExplosion_medium,
      GetItem,
      StartBattle,
      Title1,
      Title2
    };
  
  //void LoadSounds();
  void playSound(SoundNames soundName);
  void playBattleMusic();
  void pauseMusic();
  void unpauseMusic();
  void playMusic(const std::string);
  
private:
  std::map<SoundNames, sf::SoundBuffer> Sounds;
  std::vector<sf::Sound> playingSounds;
  std::vector<std::string> battleMusics;
  sf::Music music;
};

#endif
