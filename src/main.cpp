#include <unistd.h>
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
#include "Tools.hh"
#include "RunGame.hh"

int main()
{

  Config conf;

  // Init irrlicht
  Device *device;
  VideoDriver* video;
  SceneManager* smgr;
  GUIEnv* env;
  GUIFont *font;

  conf.refreshConfig();
  try
    {
      device = irr::createDevice(irr::video::EDT_OPENGL, conf.screenSize, 32,
				 conf.getFullScreen(), false, false, 0);
      if (device == NULL)
	throw ("Can't create device");
      video = device->getVideoDriver();
      if (video == NULL)
	throw ("Can't create video driver");
      smgr = device->getSceneManager();
      if (smgr == NULL)
	throw ("Can't create scene manager");
      env = device->getGUIEnvironment();
      if (env == NULL)
	throw ("Can't create gui");
    }
  catch (char const *message)
    {
      messageError(message);
    }

  irr::core::stringw windowTitle = L"Bomberman3D (Indie studio)";
  device->setWindowCaption(windowTitle.c_str());
  
  try
    {
      if ((font = env->getFont("font/artoffighting.xml")) == NULL)
	throw ("font/artoffighting.xml");
    }
  catch (char const *file)
    {
      openError(file);
    }
  
  // Setup event reciever
  SoundManager soundManager;
  MyEventReceiver receiver(device, video, &soundManager);
  device->setEventReceiver(&receiver);

  TexturePack *texture = new TexturePack(video);
  MeshPack *mesh = new MeshPack(smgr);
  Game game(device, &soundManager, mesh, texture, &receiver);
  Score score;

  splash(device, env, video, &soundManager, &receiver, font, conf.getScreenSize());

  Interface menu(device);
  menu.setInterface(video);

  runGame(device, env, video, &soundManager, &receiver, smgr, conf, texture, mesh, game, score, menu, font);
}
