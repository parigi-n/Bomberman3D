#include "Tools.hh"

void 	splash(Device *device, GUIEnv* env, VideoDriver* video,
	       SoundManager *soundManager, MyEventReceiver *receiver,
	       GUIFont *font, dimension2d *screenSize)
{
  irr::video::ITexture	*tex;
  irr::u32		now = device->getTimer()->getTime();
  irr::gui::IGUIImage*	img;
  irr::gui::IGUIImage*	startImg;
  int			posX = 900, posY = 700;

  try
    {
      if ((tex = video->getTexture("media/splashscreen.png")) == NULL)
	throw ("media/splashscreen.png");
    }
  catch (char const *file)
    {
      openError(file);
    }
  img = env->addImage(irr::core::rect<irr::s32>(10,10, 100,225));
  soundManager->playSound(SoundManager::Title1);
  soundManager->playMusic("music/menu/title.ogg");
  while(device->run() && device)
    {
      while (posX < 1300)
	{
	  img = env->addImage(irr::core::rect<irr::s32>(650, 50, posX += 5, posY += 1));
	  img->setImage(tex);
	  img->setScaleImage(true);
	  video->beginScene(true, true, irr::video::SColor(0,200,200,200));
	  env->drawAll();
	  now = device->getTimer()->getTime();
	  video->endScene();
	  env->clear();
	}
      now = device->getTimer()->getTime();
      video->beginScene(true, true, irr::video::SColor(0,200,200,200));
      img = env->addImage(irr::core::rect<irr::s32>(650, 50, posX, posY));
      img->setImage(tex);
      img->setScaleImage(true);
      env->drawAll();
      if ((now / 700) % 2 == 0)
	font->draw(L"PRESS START", irr::core::recti(posX - 900, posY + 20, posX + 200, posY + 30), irr::video::SColor(255, 248, 216, 56), true, true);
      video->endScene();
      env->clear();
      if (receiver->IsKeyDown(irr::KEY_RETURN) == true)
	break;
      else
	continue;
    }
  video->endScene();
  env->clear();
  video->removeTexture(tex);
  soundManager->pauseMusic();
  soundManager->playSound(SoundManager::Title2);
}

Config::Config()
{
  this->screenSize.Width = 1920;
  this->screenSize.Height = 1080;
  setFullScreen(false);
}

Config::~Config()
{
}

irr::core::dimension2d<u32>	*Config::getScreenSize()
{
  irr::core::dimension2d<u32>	tmp;

  tmp.Width = screenSize.Width;
  tmp.Height = screenSize.Height;
  return (&tmp);
}

void				Config::setScreenSize(irr::core::dimension2d<u32> const sSize)
{
  this->screenSize = sSize;
}

bool				Config::getFullScreen()
{
  return (this->isFullScreen);
}

void				Config::setFullScreen(const bool fullScreen)
{
  this->isFullScreen = fullScreen;
}

void				Config::refreshConfig()
{
  std::ifstream file;
  file.open("bomberman.conf");
  std::string line;
  while( std::getline(file, line) )
    {
      std::istringstream is_line(line);
      std::string key;
      if( std::getline(is_line, key, '=') )
	{
	  std::string value;
	  if(std::getline(is_line, value))
	    {
	      if (key == "Width" && atoi(value.c_str()) > 1)
		screenSize.Width = atoi(value.c_str());
	      else if (key == "Height" && atoi(value.c_str()) > 1)
		screenSize.Height = atoi(value.c_str());
	      else if (key == "Fullscreen")
		{
		  if (value == "true")
		    setFullScreen(true);
		  else
		    setFullScreen(false);
		}
	      else if (key == "Fullscreen" && value == "false")
		setFullScreen(false);
	    }
	}
    }
}

void				displayMenu(Game *game, irr::gui::IGUIEnvironment* env, irr::video::IVideoDriver* video, MyEventReceiver *receiver)
{
  if (receiver->getRestart() == true)
    {
      game->setState(Game::MENU);
      receiver->setRestart();
    }
  if (game->getState() == Game::MENU)
    {
      game->createMap(receiver->getX(), receiver->getY(), 0,
		      receiver->getRandom(), receiver->getGraphism());
      game->setState(Game::NO);
    }
  video->beginScene(true, true, irr::video::SColor(255,113,0,255));
  game->effect->update();
  env->drawAll();
  video->endScene();
}

Score::Score()
{
  this->_name = ("AAA");
  this->_alphabet = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
  this->_index[0] = 0;
  this->_index[1] = 0;
  this->_index[2] = 0;
  this->_letter = 0;
  this->_playerScore = 0;
  this->_displayScoreName = (L"");
  this->_finalScoreName = _displayScoreName.c_str();
  this->_temp = "\0";
}

Score::~Score()
{
}

void		Score::refreshName()
{
  this->_name[0] = this->_alphabet[_index[0]];
  this->_name[1] = this->_alphabet[_index[1]];
  this->_name[2] = this->_alphabet[_index[2]];
}

std::string	Score::getScoreFromFile(const std::string &scoreFile)
{
  std::string result;
  std::ifstream file;
  int i = 0;

  try
    {
      file.open(scoreFile.c_str());
      std::string line;
      while (std::getline(file, line) && i++ != 10)
	{
	  std::istringstream is_line(line);
	  std::string key;
	  if ( std::getline(is_line, key, '=') )
	    {
	      std::string value;
	      if ( std::getline(is_line, value) )
		{
		  result += key;
		  result += "...............";
		  result += value;
		  result += "\n";
		}
	    }
	}
      file.close();
    }
  catch (std::runtime_error &e)
    {
      std::cout << "runtime_error caught: " << e.what() << std::endl;
    }
  return (result);
}

int		Score::countLinesInFile(const std::string &file)
{
  int		nbLine;

  try
    {
      std::ifstream f(file.c_str());
      std::string line;
      for(int i = 0; std::getline(f, line); ++i)
	nbLine++;
      std::cout << "Nb line =" << nbLine << std::endl;
    }
  catch (std::ifstream::failure &e)
    {
      std::cout << "runtime_error caught: " << e.what() << std::endl;
    }
  return nbLine;
}

void		Score::saveScore(const std::string &name)
{
  std::ofstream	out;

  try
    {
      out.open("bomberman.score", std::ios::app);
      out << name;
      out << "=";
      out << _playerScore;
      out << "\n";
      out.close();
    }
  catch (std::ofstream::failure &e)
    {
      std::cout << "ofstream_error caught: " << e.what() << std::endl;
    }

}

std::string	convertScore(int score)
{
  std::stringstream convert;

  convert << score;
  return(convert.str());
}

void		Score::endScreen(Device *device, GUIEnv* env, VideoDriver* video,
				 SoundManager *soundManager, MyEventReceiver *receiver,
				 GUIFont *font, dimension2d *screenSize, Interface menu, Game *game, u32 then)
{
  if (receiver->IsKeyDown(irr::KEY_DOWN) == true)
    {
      if (_index[_letter] == 35)
	_index[_letter] = 0;
      else
	_index[_letter] += 1;
      refreshName();
    }
  if (receiver->IsKeyDown(irr::KEY_UP) == true)
    {
      if (_index[_letter] == 0)
	_index[_letter] = 35;
      else
	_index[_letter] -= 1;
      refreshName();
    }
  if (receiver->IsKeyDown(irr::KEY_LEFT) == true)
    {
      if (_letter != 0)
	_letter -= 1;
    }
  if (receiver->IsKeyDown(irr::KEY_RIGHT) == true)
    {
      if (_letter != 2)
	_letter += 1;
    }
  if (receiver->IsKeyDown(irr::KEY_RETURN) == true)
    {
      saveScore(_name);
      device->getTimer()->stop();
      receiver->setInGame();
      menu.setInterface(video);
      soundManager->pauseMusic();
      game->setState(Game::MENU);
    }

  for (int i = 0; i < 3; ++i)
    _displayScoreName += wchar_t( _name[i] );
  _displayScoreName += (L"...............");
  std::string strScore = convertScore(_playerScore);

  for (int i = 0; i < strScore.size(); ++i)
    _displayScoreName += wchar_t(strScore[i]);
  _finalScoreName = _displayScoreName.c_str();
  font->draw(_finalScoreName, irr::core::recti(0, 0, screenSize->Width, 200), irr::video::SColor(255, 248, 216, 56), true, true);
  _displayScoreName.clear();
  _temp = getScoreFromFile("bomberman.score");
  for(int i = 0; i < _temp.size(); ++i)
    {
      _displayScoreName += wchar_t( _temp[i] );
      _finalScoreName = _displayScoreName.c_str();
    }
  _finalScoreName = _displayScoreName.c_str();
  if ((then/500 )%2==0)
    font->draw(_finalScoreName, irr::core::recti(0, 200, screenSize->Width, screenSize->Height - 200), irr::video::SColor(255, 248, 216, 56), true, true);
  _displayScoreName.clear();
}
