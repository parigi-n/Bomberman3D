#include <irrlicht.h>
#include "Game.hh"

// #define NEWPOSX(x) (nodePosition.X + x + MOVEMENT_SPEED * frameDeltaTime)
// #define NEWPOSY(y) (nodePosition.Y + y + MOVEMENT_SPEED * frameDeltaTime)
// #define NEWPOS(x, y) (this->getCase((int)(NEWPOSX(x), NEWPOSY(y))))

Game::Game(Device *device, SoundManager *soundManager,
	   MeshPack *_meshPack, TexturePack *_tpack,
	   MyEventReceiver *_receiver)
  : meshPack(_meshPack), texturePack(_tpack), receiver(_receiver)
{
  this->meshList[BlockType::EMPTY] = "media/fire_item.3ds";
  this->meshList[BlockType::SOCLE] = "media/goldensocle.3ds";
  this->meshList[BlockType::BOMB] = "media/bomb.obj";
  this->meshList[BlockType::BOMB_ITEM] = "media/bomb.obj";
  this->meshList[BlockType::SPEED_ITEM] = "media/speed_item.obj";
  this->meshList[BlockType::RADIUS_ITEM] = "media/fire_item.3ds";
  this->meshList[BlockType::BOMBERMAN] = "media/BombyStatic.b3d";

  this->textureList[BlockType::TGRID] = "media/grid.png";
  this->textureList[BlockType::THARD] = "media/hardblock.png";
  this->textureList[BlockType::TEND] = "media/endblock2.png";
  this->textureList[BlockType::TLIGHT] = "media/lightblock5.png";
  this->textureList[BlockType::TPARTICULE1] = "media/explosion00.png";
  this->textureList[BlockType::TPARTICULE2] = "media/fireball.bmp";

  this->animatedmeshList[BlockType::PLAYER] = "media/bomberman_anim4.b3d";

  this->actionPtr[Action::ACTION] = &Game::putBomb;
  this->actionPtr[Action::UP] = &Game::goUp;
  this->actionPtr[Action::DOWN] = &Game::goDown;
  this->actionPtr[Action::LEFT] = &Game::goLeft;
  this->actionPtr[Action::RIGHT] = &Game::goRight;

  this->playerNb = 4;
  this->device = device;
  this->effect = NULL;

  this->soundManager = soundManager;
  this->gameState = Game::MENU;
  this->loadTexture();
}

std::vector<std::vector<Case> > const	&Game::getMap() const
{
  return (this->map);
}

std::vector<Entity *> const		&Game::getEntityList() const
{
  return (this->entityList);
}

void    Game::clearMap()
{
  int   i;
  int   len;
  i = 0;
  len = this->map.size();
  while (i != len)
    {
      this->map[i].clear();
      i++;
    }
  this->map.clear();
}

void    Game::clearPlayers()
{
  this->playerList.clear();
}

void    Game::clearEntities()
{
  this->entityList.clear();
}

void    Game::clearSmgr()
{
  this->smgr->clear();
}

int Game::getLength()const
{
  return (this->length);
}

int Game::getWidth()const
{
  return (this->width);
}

int	Game::setLength(int len)
{
  this->length = len;
}

int	Game::setWidth(int wid)
{
  this->width = wid;
}

CameraScene	*Game::getCamera()
{
  return (this->camera);
}

Entity &Game::getEntity(int nb)
{
  return (*this->entityList[nb]);
}

Case &Game::getCase(int x, int y)
{
  return (this->map[x][y]);
}

void	Game::loadTexture()
{
  for (std::map<BlockType::BlockType,
	 std::string>::iterator it = meshList.begin();
       it != meshList.end(); ++it)
    {
      if (meshPack->addMesh(it->first, it->second) == false)
	throw("Can't Load texture");
    }
  for (std::map<BlockType::AnimateType,
	 std::string>::iterator it = animatedmeshList.begin();
       it != animatedmeshList.end(); ++it)
    {
      if (meshPack->addMesh(it->first, it->second) == false)
	throw("Can't Load texture");
    }
  for (std::map<BlockType::Texture,
	 std::string>::iterator it = textureList.begin();
       it != textureList.end(); ++it)
    {
      if (texturePack->addTexture(it->first, it->second) == false)
	throw("Can't Load texture");
    }
}

int   Game::justCountUpRadius(const int radius, const int ix, const int iy)
{
  BlockType::BlockType type;
  int incX = 0, incY = 0;
  int size = 0;
  for (incY = 1; incY <= radius; incY++)
  {
    type = map[ix][iy + incY].getBlockType();
    if (type == BlockType::HARD)
      {
	break;
      }
    else if (type == BlockType::LIGHT)
      {
	break;
      }
    else
      {
        size++;
      }
  }
  return size;
}

int   Game::justCountDownRadius(const int radius, const int ix, const int iy)
{
  BlockType::BlockType  type;
  int incX = 0, incY = 0;
  int size = 0;
  for(incY = -1; -incY <= radius; incY--)
    {
      type = map[ix][iy + incY].getBlockType();
      if (type == BlockType::HARD)
  break;
      else if (type == BlockType::LIGHT)
  {
    break;
  }
      else
  size++;
    }
  return size;
}

int   Game::justCountLeftRadius(const int radius, const int ix, const int iy)
{
  int incX = 0, incY = 0;
  BlockType::BlockType  type;
  int size = 0;
  for(incX = -1; -incX <= radius; incX--)
    {
      type = map[ix + incX][iy].getBlockType();
      if (type == BlockType::HARD)
  break;
      else if (type == BlockType::LIGHT)
  {
  break;
  }
      else
  size++;
    }
  return size;
}

int   Game::justCountRightRadius(const int radius, const int ix, const int iy)
{
  int incX = 0, incY = 0;
  BlockType::BlockType  type;
  int size = 0;
  for(incX = 1; incX <= radius; incX++)
    {
      type = map[ix + incX][iy].getBlockType();
      if (type == BlockType::HARD)
	break;
      else if (type == BlockType::LIGHT)
	{
	  break;
	}
      else
	size++;
    }
  return size;
}

int	  Game::countUpRadius(const int radius, const int ix, const int iy)
{
	int incX = 0, incY = 0;
	BlockType::BlockType	type;
	int size = 0;
	for (incY = 1; incY <= radius; incY++)
	{
		type = map[ix][iy + incY].getBlockType();
		if (type == BlockType::HARD)
		{
			break;
		}
		else if (type == BlockType::LIGHT)
		{
			map[ix][iy + incY].destroy();
			map[ix][iy + incY].setDangerous(SAFE);
			break;
		}
		/*else if (type = BlockType::BOMB)
		{
			std::cout << " STOP BOMB" << std::endl;
			break;
		}*/
		else
		  {
		    size++;
		  }
			//ICI ON TRACE L'EXPLOSION ET ON CONTINUE LA BOUCLE
	}
	return size;
}

int	  Game::countDownRadius(const int radius, const int ix, const int iy)
{
  BlockType::BlockType	type;
  int incX = 0, incY = 0;
  int size = 0;
  for(incY = -1; -incY <= radius; incY--)
    {
      type = map[ix][iy + incY].getBlockType();
      if (type == BlockType::HARD)
	break;
      else if (type == BlockType::LIGHT)
	{
    map[ix][iy + incY].destroy();
	  map[ix][iy + incY].setDangerous(SAFE);
	  break;
	}
      /*else if (type = BlockType::BOMB)
      //ICI ON TRIGGER L'AUTRE BOMBE
      break;*/
      else
	size++;
      //ICI ON TRACE L'EXPLOSION ET ON CONTINUE LA BOUCLE
    }
  return size;
}

int	  Game::countLeftRadius(const int radius, const int ix, const int iy)
{
  int incX = 0, incY = 0;
  BlockType::BlockType	type;
  int size = 0;
  for(incX = -1; -incX <= radius; incX--)
    {
      type = map[ix + incX][iy].getBlockType();
      if (type == BlockType::HARD)
	break;
      else if (type == BlockType::LIGHT)
	{
	  map[ix + incX][iy].destroy();
    map[ix + incX][iy].setDangerous(SAFE);
	//ICI ON PETE LE LIGHTBLOCK
	break;
	}
      /*else if (type = BlockType::BOMB)
      //ICI ON TRIGGER L'AUTRE BOMBE
      break;*/
      else
	size++;
      //ICI ON TRACE L'EXPLOSION ET ON CONTINUE LA BOUCLE
    }
  return size;
}

int	  Game::countRightRadius(const int radius, const int ix, const int iy)
{
  int incX = 0, incY = 0;
  BlockType::BlockType	type;
  int size = 0;
  for(incX = 1; incX <= radius; incX++)
    {
      type = map[ix + incX][iy].getBlockType();
      if (type == BlockType::HARD)
	break;
      else if (type == BlockType::LIGHT)
	{
	  //ICI ON PETE LE LIGHTBLOCK
	  map[ix + incX][iy].destroy();
    map[ix + incX][iy].setDangerous(SAFE);
	  break;
	}
      /*else if (type = BlockType::BOMB)
      //ICI ON TRIGGER L'AUTRE BOMBE
      break;*/
      else
	size++;
			//ICI ON TRACE L'EXPLOSION ET ON CONTINUE LA BOUCLE
    }
  return size;
}

void  Game::launchExplosion(Bomb *bomb, const int &x, const int &y)
{
  std::list<vector2di>	radiusCoorList;
  int	radius;
  int up = 0, down = 0, left = 0, right = 0, i = 0;

  radius  = bomb->getBombRadius();
  up = this->countUpRadius(radius, x, y);
  down = this->countDownRadius(radius, x, y);
  left = this->countLeftRadius(radius, x, y);
  right = this->countRightRadius(radius, x, y);

  bomb->explode(up, down, left, right);

  //remplissage
  for (i = 0; i <= up; i++)
    {
      bomb->addExplosionCase(vector2di(x, y + i));
      this->map[x][y + i].addExplosion();
    }
  for (i = 1; i <= down; i++)
    {
      bomb->addExplosionCase(vector2di(x, y - i));
      this->map[x][y - i].addExplosion();
    }
  for (i = 1; i <= left; i++)
    {
      bomb->addExplosionCase(vector2di(x - i, y));
      this->map[x - i][y].addExplosion();
    }
  for (i = 1; i <= right; i++)
    {
      bomb->addExplosionCase(vector2di(x + i, y));
      this->map[x + i][y].addExplosion();
    }
}

void	Game::addBombCoor(const int &x, const int &y)
{
  this->bombCoorList.push_back(vector2di(x, y));
}

void	Game::deleteBombCoor(const int &x, const int &y)
{
  this->bombCoorList.remove(vector2di(x, y));
}

Device	*Game::getDevice()
{
  return (this->device);
}

const Game::GameState	&Game::getState() const
{
  return (this->gameState);
}

void		Game::setState(const GameState &gameState)
{
  this->gameState = gameState;
}
