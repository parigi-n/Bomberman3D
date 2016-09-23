#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <XEffects.h>

#include "UserInterface.hh"
#include "Game.hh"

//Ajouter bouton pour couper la musique

Interface::Interface(Device *device)
{
  try
    {
      this->env = device->getGUIEnvironment();
      if (this->env == NULL)
	throw ("Can't create gui");
      this->font = this->env->getFont("font/MenuFont.xml");
      if (this->font == NULL)
	throw ("font/MenuFont.xml");
      this->env->getSkin()->setFont(this->font);
    }
  catch (char const *file)
    {
      openError(file);
    }
}

void	Interface::drawLogo(VideoDriver* video)
{
  irr::video::ITexture *background;
  irr::video::ITexture *logo;

  try
    {
      if ((background = video->getTexture("media/background.png")) == NULL)
	throw ("media/background.png");;
      if ((logo = video->getTexture("media/battlefest_logo.png")) == NULL)
	throw ("media/battlefest_logo.png");
      this->env->addImage(background, 
			  irr::core::position2d<int>(0,0));
      this->env->addImage(logo,
			  irr::core::position2d<int>(420,10));
    }
  catch (char const *file)
    {
      openError(file);
    }
}

// Ajouter les scores

void	Interface::setScores(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addButton(irr::core::rect<irr::s32>(860,650,1060,650 + 32), 0, GUI_ID_BACK_BUTTON,
		       L"GO BACK", L"");
}

void	Interface::setInterface(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addButton(irr::core::rect<irr::s32>(860,510,1060,510 + 32), 0, GUI_ID_PLAY_BUTTON,
		       L"PLAY", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,550,1060,550 + 32), 0, GUI_ID_LOAD_BUTTON,
		       L"LOAD GAME", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,590,1060,590 + 32), 0, GUI_ID_OPTION_BUTTON,
		       L"OPTIONS", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,650,1060,650 + 32), 0, GUI_ID_QUIT_BUTTON,
		       L"EXIT", L"");
}

void	Interface::setPause(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addButton(irr::core::rect<irr::s32>(860,510,1060,510 + 32), 0, GUI_ID_MAIN_BUTTON,
		       L"MAIN MENU", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,550,1060,550 + 32), 0, GUI_ID_RESUME_BUTTON,
		       L"RESUME", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,590,1060,590 + 32), 0, GUI_ID_SAVE_BUTTON,
		       L"SAVE GAME", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,650,1060,650 + 32), 0, GUI_ID_QUIT_BUTTON,
		       L"EXIT", L"");
}

void	Interface::setLoad(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addButton(irr::core::rect<irr::s32>(860,510,1060,510 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 1", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,550,1060,550 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 2", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,590,1060,590 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 3", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,650,1060,650 + 32), 0, GUI_ID_MAIN_BUTTON,
		       L"GO BACK", L"");
}

void	Interface::setSave(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addButton(irr::core::rect<irr::s32>(860,510,1060,510 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 1", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,550,1060,550 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 2", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,590,1060,590 + 32), 0, GUI_ID_FIRST_BUTTON,
		       L"SLOT 3", L"");
  this->env->addButton(irr::core::rect<irr::s32>(860,650,1060,650 + 32), 0, GUI_ID_RETURN_BUTTON,
		       L"GO BACK", L"");
}

void	Interface::setOptions(VideoDriver* video)
{
  this->drawLogo(video);
  this->env->addStaticText(L"number of players:",
			irr::core::rect<irr::s32>(760,498,1160,498 + 22), true);
  irr::gui::IGUIScrollBar* players = this->env->addScrollBar(true, 
			irr::core::rect<irr::s32>(810, 535, 1110, 535 + 15), 0, GUI_ID_PLAYER_SCROLL_BAR);
  this->env->addStaticText(L"0",
			   irr::core::rect<irr::s32>(780,530,800,530 + 22), true);
  this->env->addStaticText(L"4",
			irr::core::rect<irr::s32>(1120,530,1140,530 + 22), true);
  players->setMax(4);
  players->setMin(0);
  players->setPos(1);
  players->setLargeStep(1);
  players->setSmallStep(1);

  this->env->addStaticText(L"field width:",
			irr::core::rect<irr::s32>(825,560,1095,560 + 22), true);
  irr::gui::IGUIScrollBar* posX = this->env->addScrollBar(true, 
			irr::core::rect<irr::s32>(810, 595, 1110, 595 + 15), 0, GUI_ID_X_SCROLL_BAR);
  this->env->addStaticText(L"29",
			irr::core::rect<irr::s32>(1120,590,1160,590 + 22), true);
  this->env->addStaticText(L"9",
			irr::core::rect<irr::s32>(780,590,800,590 + 22), true);
  posX->setMax(29);
  posX->setMin(9);
  posX->setPos(29);
  posX->setLargeStep(2);
  posX->setSmallStep(2);

  this->env->addStaticText(L"field height:",
			irr::core::rect<irr::s32>(815,620,1105,620 + 22), true);
  irr::gui::IGUIScrollBar* posY = this->env->addScrollBar(true, 
			irr::core::rect<irr::s32>(810, 655, 1110, 655 + 15), 0, GUI_ID_Y_SCROLL_BAR);
  this->env->addStaticText(L"19",
			irr::core::rect<irr::s32>(1120,650,1160,650 + 22), true);
  this->env->addStaticText(L"9",
			irr::core::rect<irr::s32>(780,650,800,650 + 22), true);
  posY->setMax(19);
  posY->setMin(9);
  posY->setPos(19);
  posY->setLargeStep(2);
  posY->setSmallStep(2);

  this->env->addStaticText(L"block density:",
			irr::core::rect<irr::s32>(805,680,1115,680 + 22), true);
  irr::gui::IGUIScrollBar* random = this->env->addScrollBar(true, 
			irr::core::rect<irr::s32>(810, 715, 1110, 715 + 15), 0, GUI_ID_RAND_SCROLL_BAR);
  this->env->addStaticText(L"max",
			irr::core::rect<irr::s32>(740,710,800,710 + 22), true);
  this->env->addStaticText(L"min",
			irr::core::rect<irr::s32>(1120,710,1180,710 + 22), true);
  random->setMax(10);
  random->setMin(1);
  random->setPos(3);
  random->setLargeStep(1);
  random->setSmallStep(1);

  this->env->addStaticText(L"Low graphic",
			irr::core::rect<irr::s32>(875,750,1135,750 + 22), true);

  this->env->addButton(irr::core::rect<irr::s32>(860,810,1060,810 + 32), 0, GUI_ID_VALID_BUTTON,
		       L"confirm", L"");
}

GameOption::GameOption()
{
  this->Players = 1;
  this->x = 29;
  this->y = 19;
  this->random = 3;
}

void	GameOption::setPlayers(irr::s32 const nb)
{
  this->Players = nb;
}

void	GameOption::setPosX(irr::s32 const pos)
{
  this->x = pos;
}

void	GameOption::setPosY(irr::s32 const pos)
{
  this->y = pos;
}


void	GameOption::setRandom(irr::s32 const rand)
{
  this->random = rand;
}

const irr::s32&	GameOption::getPlayers() const
{
  return (this->Players);
}

const irr::s32&	GameOption::getPosX() const
{
  return (this->x);
}

const irr::s32&	GameOption::getPosY() const
{
  return (this->y);
}

const irr::s32&	GameOption::getRandom() const
{
  return (this->random);
}
