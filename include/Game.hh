#ifndef GAME_HH
# define GAME_HH

# include <vector>
# include <list>
# include <iostream>
# include <irrlicht.h>
# include <XEffects.h>

# include "Define.hh"
# include "Exception.hh"
# include "EventReceiver.hpp"
# include "Binding.hh"
# include "Entity.hh"
# include "Player.hh"
# include "Bot.hh"
# include "Map.hh"
# include "Pack.hh"
# include "Item.hh"
# include "SoundManager.hh"
# include "BlockType.hh"

# define MAX_PLAYER 4

class Game
{
public:
  enum GameState
    {
      NO,
      READY,
      GO,
      PAUSED,
      PLAY,
      FINISHED,
      MENU
    };

  EffectHandler*	effect;

  Game(Device *device, SoundManager *soundManager,
       MeshPack *, TexturePack *, MyEventReceiver *);
  std::vector<std::vector<Case> > const	&getMap() const;
  std::vector<Entity *> const		&getEntityList() const;
  void					setMap(std::vector<int> mymap);
  int					getLength()const;
  int					getWidth()const;
  int					setLength(int len);
  int					setWidth(int wid);
  void					loadBlock();
  void					loadMap(int _x, int _y, int _playerNb);
  void					loadEntity();
  CameraScene				*getCamera();

  void		initMap(int x, int y, int playerNb,
			int random, bool graphism);
  void		createMap(int x, int y, int playerNb,
			  int random, bool graphism);
  void		updateMovement(const float &frameDeltaTime);
  bool		isBorder(int, int);
  Case		&getCase(int x, int y);
  Entity	&getEntity(int nb);

  void		launchExplosion(Bomb *bomb, const int &x, const int &y);
  void		addBombCoor(const int &x, const int &y);
  void		deleteBombCoor(const int &x, const int &y);
  Device	*getDevice();
  const GameState		&getState() const;
  void		setState(const GameState &gameState);

  void		clearSmgr();
  void		clearEntities();
  void		clearPlayers();
  void		clearMap();

private:
  std::vector<std::vector<Case> >	map;
  Device				*device;
  std::vector<std::vector<int> >	dangermap;
  std::vector<Player *>			playerList;
  std::vector<Bot *>			botList;
  std::vector<Entity *>			entityList;
  MeshScene				*grid;
  TexturePack				*texturePack;
  MeshPack				*meshPack;
  CameraScene				*camera;
  VideoDriver				*video;
  SceneManager				*smgr;
  Scene					*skybox;
  std::list<vector2di>			bombCoorList;
  int					length;
  int					width;
  int					playerNb;
  SoundManager				*soundManager;
  MyEventReceiver			*receiver;
  GameState				gameState;

  std::map<BlockType::Texture, std::string>	textureList;
  std::map<BlockType::BlockType, std::string>	meshList;
  std::map<BlockType::AnimateType, std::string>	animatedmeshList;

  typedef void (Game::*Function)(Entity *);
  std::map<Action::Action, Function>		actionPtr;
  //  std::map<Action::Action, void (Game::*)(Entity *)>	actionPtr;

  float			frameDeltaTime;
  Action::Action	direction[3];
  vector3df		nodeRotation;
  vector3df		nodePosition;
  int			idxDir;
  bool			hasMoved;
  int			originalX;
  int			originalY;

  void		movePlayer(Entity *);
  void		setDangerousZone(int &, int &, int);
  void		updateBomb();
  void		checkExplosion(Entity *it);
  void		checkItem(Entity * it);
  bool		checkCollision(Entity &it, const f32 &,
			       const Case &actualCase, const Case &nextCase);
  void		loadTexture();
  void		placeBlock(int);
  void		createPlayer(AnimatedMesh *);
  void		putBomb(Entity* itEntity);
  void		goUp(Entity *player);
  void		goDown(Entity *player);
  void		goLeft(Entity *player);
  void		goRight(Entity *player);

  int		countUpRadius(const int radius, const int ix, const int iy);
  int		countDownRadius(const int radius, const int ix, const int iy);
  int		countRightRadius(const int radius, const int ix, const int iy);
  int		countLeftRadius(const int radius, const int ix, const int iy);
  int		justCountUpRadius(const int radius, const int ix, const int iy);
  int		justCountDownRadius(const int radius, const int ix, const int iy);
  int		justCountRightRadius(const int radius, const int ix, const int iy);
  int		justCountLeftRadius(const int radius, const int ix, const int iy);
};

#endif
