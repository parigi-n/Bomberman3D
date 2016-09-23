#ifndef RUNGAME_HH_
# define RUNGAME_HH_

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

void runGame(Device *device, GUIEnv* env, VideoDriver* video, SoundManager *soundManager, MyEventReceiver *receiver, SceneManager *smgr, Config conf, TexturePack *texture, MeshPack *mesh, Game game, Score score, Interface menu, GUIFont *font);

#endif // RUNGAME_HH_
