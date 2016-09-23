#ifndef EVENT_HH
# define EVENT_HH

#include <iostream>
#include <string>
#include <irrlicht.h>
#include "UserInterface.hh"
#include "SoundManager.hh"

enum
  {
    GUI_ID_QUIT_BUTTON,
    GUI_ID_PLAY_BUTTON,
    GUI_ID_RESUME_BUTTON,
    GUI_ID_OPTION_BUTTON,
    GUI_ID_PLAYER_SCROLL_BAR,
    GUI_ID_X_SCROLL_BAR,
    GUI_ID_Y_SCROLL_BAR,
    GUI_ID_RAND_SCROLL_BAR,
    GUI_ID_VALID_BUTTON,
    GUI_ID_RETURN_BUTTON,
    GUI_ID_BACK_BUTTON,
    GUI_ID_FIRST_BUTTON,
    GUI_ID_LOAD_BUTTON,
    GUI_ID_SAVE_BUTTON,
    GUI_ID_MAIN_BUTTON,
    GUI_ID_CHECKED
  };

class MyEventReceiver : public irr::IEventReceiver
{
public:
  // This is the one method that we have to implement
  virtual bool				OnEvent(const irr::SEvent& event)
  {
    // Remember whether each key is down or up

    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      {

	KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	/*if ((KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown) != true)
	  KeyIsReleased[event.KeyInput.Key] = true;*/
      }
    if (event.EventType == irr::EET_GUI_EVENT)
      {
	irr::s32			id = event.GUIEvent.Caller->getID();
	irr::gui::IGUIEnvironment*	env = device->getGUIEnvironment();
	Interface			menu(device);
	irr::s32			pos;

	switch (event.GUIEvent.EventType)
	  {
	  case irr::gui::EGET_SCROLL_BAR_CHANGED:
	    switch (id)
	      {
	      case GUI_ID_PLAYER_SCROLL_BAR:
	        pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
		options.setPlayers(pos);
		return true;

	      case GUI_ID_X_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
		options.setPosX(pos);
		return true;

	      case GUI_ID_Y_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
		options.setPosY(pos);
		return true;

	      case GUI_ID_RAND_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
		options.setRandom(pos);
		return true;

	      default:
		break;
	      }
	    break;

	  case irr::gui::EGET_CHECKBOX_CHANGED:
	    if (id == GUI_ID_CHECKED)
	      {
		graphism = box->isChecked();
		return true;
	      }

	  case irr::gui::EGET_BUTTON_CLICKED:
	    switch (id)
	      {
	      case GUI_ID_QUIT_BUTTON:
		device->closeDevice();
		return true;

	      case GUI_ID_PLAY_BUTTON:
		env->clear();
		device->getTimer()->start();
		inGame = true;
		return true;

	      case GUI_ID_RESUME_BUTTON:
		env->clear();
		device->getTimer()->start();
		inGame = true;
		return true;
		
	      case GUI_ID_BACK_BUTTON:
		env->clear();
		menu.setInterface(video);
		return true;

	      case GUI_ID_OPTION_BUTTON:
		env->clear();
		menu.setOptions(video);
		box = env->addCheckBox(graphism,irr::core::rect<irr::s32>(840,750,840 + 22, 750 + 22), 0, GUI_ID_CHECKED, L"graphism");
		return true;

	      case GUI_ID_LOAD_BUTTON:
		return true;

	      case GUI_ID_SAVE_BUTTON:
		return true;

	      case GUI_ID_VALID_BUTTON:
		env->clear();
		menu.setInterface(video);
		return true;

	      case GUI_ID_RETURN_BUTTON:
		env->clear();
		menu.setPause(video);
		return true;

	      case GUI_ID_MAIN_BUTTON:
		env->clear();
		menu.setInterface(video);
		restart = true;
		return true;

	      case GUI_ID_FIRST_BUTTON:
		return true;

	      default:
		return false;
	      }
	    break;
	  default:
	    break;
	  }
      }
    return false;
  }

  // This is used to check whether a key is being held down
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }

  virtual const int&	getSave() const
  {
    return save;
  }

  virtual void	setSave()
  {
    save = 0;
  }

  virtual const int&	getLoad() const
  {
    return load;
  }

  virtual void	setLoad()
  {
    load = 0;
  }

  virtual const bool&	getInGame() const
  {
    return inGame;
  }

  virtual const bool&	getRestart() const
  {
    return restart;
  }

  virtual void	setRestart()
  {
    restart = !restart;
  }

  virtual void	setInGame()
  {
    inGame = !inGame;
  }

  virtual const int&	getX() const
  {
    return (options.getPosX());
  }

  virtual const int&	getY() const
  {
    return (options.getPosY());
  }

  virtual const int&	getPlayers() const
  {
    return (options.getPlayers());
  }

  virtual const int&	getRandom() const
  {
    return (options.getRandom());
  }

  virtual const bool&	getGraphism() const
  {
    return (graphism);
  }

  MyEventReceiver(irr::IrrlichtDevice * dev, irr::video::IVideoDriver * vid, SoundManager *sdmr)
  {
    device = dev;
    video = vid;
    inGame = false;
    restart = false;
    graphism = false;
    soundManager = sdmr;
    save = 0;
    load = 0;
    for (u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
      {
	KeyIsDown[i] = false;
      }
  }

private:
  // We use this array to store the current state of each key
  bool				KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool				inGame;
  bool				restart;
  int				save;
  int				load;
  bool				graphism;
  GameOption			options;
  SoundManager			*soundManager;
  irr::IrrlichtDevice		*device;
  irr::video::IVideoDriver	*video;
  irr::gui::IGUICheckBox	*box;
};

#endif
