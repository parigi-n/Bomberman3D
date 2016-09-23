#ifndef USERINTERFACE_HH_
# define USERINTERFACE_HH_

#include "irrlicht.h"
#include "BlockType.hh"

class	Interface
{
  irr::gui::IGUIEnvironment	*env;
  irr::gui::IGUIFont*		font;
  /*  irr::gui::IGUIButton		*play;*/
public:
  Interface(irr::IrrlichtDevice *);
  ~Interface() { }

  void	setInterface(VideoDriver*);
  void	setLoad(VideoDriver*);
  void	setSave(VideoDriver*);
  void	setPause(VideoDriver*);
  void	setOptions(VideoDriver*);
  void	setScores(VideoDriver*);
  void	drawLogo(VideoDriver*);
};

class	GameOption
{
  irr::s32	Players;
  irr::s32	x;
  irr::s32	y;
  irr::s32	random;
public:
  GameOption();
  ~GameOption() { }
  void	setPlayers(irr::s32 const);
  void	setPosX(irr::s32 const);
  void	setPosY(irr::s32 const);
  void	setRandom(irr::s32 const);
  const irr::s32&	getPlayers() const;
  const irr::s32&	getPosX() const;
  const irr::s32&	getPosY() const;
  const irr::s32&	getRandom() const;
};

#endif
