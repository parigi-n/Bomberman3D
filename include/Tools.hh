#ifndef TOOLS_HH_
# define TOOLS_HH_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <string>
#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <XEffects.h>

#include "Exception.hh"
#include "Game.hh"
#include "UserInterface.hh"
#include "UserInterface.hh"

class Config
{
public:
  Config();
  ~Config();

  void				refreshConfig();
  irr::core::dimension2d<u32>	*getScreenSize();
  void				setScreenSize(irr::core::dimension2d<u32> const sSize);
  bool			        getFullScreen();
  void			        setFullScreen(const bool fullScreen);
  irr::core::dimension2d<u32>	screenSize;

private:
  bool				isFullScreen;
};

class Score
{
public:
  Score();
  ~Score();

  void				refreshName();
  void				saveScore(const std::string &);
  int				countLinesInFile(const std::string &);
  std::string			getScoreFromFile(const std::string &);
  void				endScreen(Device *device, GUIEnv* env, VideoDriver* video,
					  SoundManager *soundManager, MyEventReceiver *receiver,
					  GUIFont *font, dimension2d *screenSize, Interface menu, Game *game, u32 then);
  std::string		_name;
  std::string		_alphabet;
  int			_playerScore;
  int			_index[3];
  int			_letter;
  std::wstring		_displayScoreName;
  const wchar_t*	_finalScoreName;
  std::string		_temp;
};

void	splash(Device *device, GUIEnv* env, VideoDriver* video,
	       SoundManager *soundManager, MyEventReceiver *receiver,
	       GUIFont *font, dimension2d *screenSize);
void	displayMenu(Game *game, irr::gui::IGUIEnvironment* env, 
		    irr::video::IVideoDriver* video, MyEventReceiver *receiver);

#endif // TOOLS_HH_
