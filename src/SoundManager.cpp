#include "SoundManager.hh"

SoundManager::SoundManager()
{
  std::string musicBattleDir = "music/battle/";
  
  Sounds[SoundManager::Death].loadFromFile("sound/death.wav");
  Sounds[SoundManager::BombExplosion_medium].loadFromFile("media/sound/BombExpl\
osion_medium.wav");
  Sounds[SoundManager::GetItem].loadFromFile("sound/item2.wav");
  Sounds[SoundManager::SetBomb].loadFromFile("media/sound/SetBomb.wav");
  Sounds[SoundManager::StartBattle].loadFromFile("sound/battlestart.ogg");
  Sounds[SoundManager::Title1].loadFromFile("sound/title_impact1.wav");
  Sounds[SoundManager::Title2].loadFromFile("sound/title_impact2.wav");

  battleMusics.push_back(musicBattleDir + "battle64.ogg");
  battleMusics.push_back(musicBattleDir + "battle64tsa.ogg");
  battleMusics.push_back(musicBattleDir + "battle94.ogg");
  battleMusics.push_back(musicBattleDir + "battlegeneration.ogg");
  battleMusics.push_back(musicBattleDir + "battlehiten.ogg");
  battleMusics.push_back(musicBattleDir + "battleII.ogg");
  battleMusics.push_back(musicBattleDir + "battlejetters.ogg");
  battleMusics.push_back(musicBattleDir + "battlelive.ogg");
  battleMusics.push_back(musicBattleDir + "battlenetde.ogg");
  battleMusics.push_back(musicBattleDir + "battleonlinedc.ogg");
  battleMusics.push_back(musicBattleDir + "battlepartyedition.ogg");
  battleMusics.push_back(musicBattleDir + "battlesaturn.ogg");
  battleMusics.push_back(musicBattleDir + "battlesaturnfight.ogg");
  battleMusics.push_back(musicBattleDir + "battlesuper3.ogg");
  battleMusics.push_back(musicBattleDir + "battlesuper5.ogg");
  battleMusics.push_back(musicBattleDir + "battletournament.ogg");
  battleMusics.push_back(musicBattleDir + "battleworld.ogg");
}
  
  SoundManager::~SoundManager()
{

}

/*void SoundManager::LoadSounds()
{
  Sounds[SoundManager::Death].loadFromFile("media/sound/Death.wav");
  Sounds[SoundManager::BombExplosion_medium].loadFromFile("media/sound/BombExplosion_medium.wav");
  Sounds[SoundManager::GetItem].loadFromFile("media/sound/GetItem.wav");
  Sounds[SoundManager::SetBomb].loadFromFile("media/sound/SetBomb.wav");
  }*/

void SoundManager::playSound(const SoundNames soundName)
{
  if (playingSounds.size() == 0)
    {
      playingSounds.push_back(sf::Sound());
      playingSounds.at(0).setBuffer(Sounds[soundName]);
      playingSounds.at(0).play();
    }
  else
    {
      int location = -1;
      for (int i = 0; i < playingSounds.size(); i++)
	{
	  if (playingSounds.at(i).getStatus() != sf::Sound::Playing && location == -1)
	    {
	      location = i;
	    }
	}

      if (location != -1)
	{
	  playingSounds.at(location).setBuffer(Sounds[soundName]);
	  playingSounds.at(location).play();
	}
      else
	{
	  playingSounds.push_back(sf::Sound());
	  playingSounds.at(playingSounds.size() - 1).setBuffer(Sounds[soundName]);
	  playingSounds.at(playingSounds.size() - 1).play();
	}

    }
}

void SoundManager::playBattleMusic()
{
  this->music.openFromFile(battleMusics[rand() % battleMusics.size()]);
  this->music.setLoop(true);
  this->music.play();
}

void SoundManager::playMusic(const std::string music)
{
  this->music.openFromFile(music);
  this->music.setLoop(true);
  this->music.play();
}

void SoundManager::pauseMusic()
{
  this->music.pause();
}

void SoundManager::unpauseMusic()
{
  this->music.play();
}
