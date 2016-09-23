#include <irrlicht.h>
#include "Game.hh"

void Game::updateMovement(const float &_frame)
{
  f32			fov = this->camera->getFOV();
  Bomb			*bomb;
  int			playerNbr = 0;
  bool			hasMoved = false;

  if (receiver->IsKeyDown(irr::KEY_KEY_T))
    this->camera->setFOV(fov + 0.001);

  frameDeltaTime = _frame;
  updateBomb();
  for (std::vector<Entity *>::iterator itPlayer = this->entityList.begin();
       itPlayer != this->entityList.end(); ++itPlayer)
    {
      if ((*itPlayer)->isAlive() == true)
	checkExplosion(*itPlayer);
      if ((*itPlayer)->isAlive() == true)
  	{
	  // std::map<Action::Action,
	  checkItem(*itPlayer);
	  this->nodePosition = (*itPlayer)->getPosition();
	  this->nodeRotation = (*itPlayer)->getRotation();
	  this->originalX = (int)(nodePosition.X / BLOCK_SIZE);
	  this->originalY = (int)(nodePosition.Z / BLOCK_SIZE);
	  // 	   void (Game::*)(Entity *)>::const_iterator it;
	  (*itPlayer)->getAction(direction);
	  movePlayer(*itPlayer);
	  (*itPlayer)->setPosition(nodePosition);
	  (*itPlayer)->setRotation(nodeRotation);

	  playerNbr++;
  	}
    }
  if (playerNbr <= 1)
    {
      setState(Game::FINISHED);
      soundManager->playMusic("music/scorepin.ogg");
      return;
    }
}

void			Game::movePlayer(Entity *itPlayer)
{
  std::map<Action::Action, Function>::const_iterator it;

  hasMoved = false;
  idxDir = 0;
  while (idxDir < NB_ACTION_PER_FRAME)
    {
      it = actionPtr.find(direction[idxDir]);
      if (it != actionPtr.end())
	{
	  (this->*(it->second))(itPlayer);
	  //if ((itPlayer)->getMove() != true)
	  //(itPlayer)->setMove(true);
	}
      else
	{
	  //	  if ((itPlayer)->getMove() != false)
	    //(itPlayer)->setMove(false);
	}
      if (hasMoved == true)
	(itPlayer)->run();
      else
	(itPlayer)->stop();
      idxDir++;
    }
}

void	Game::goUp(Entity *player)
{
  if (checkCollision(*player, frameDeltaTime, this->getCase(originalX, originalY),
		     this->getCase((int)((nodePosition.X ) / BLOCK_SIZE),
				   (int)((nodePosition.Z + 3.2 +
					  (player->getSpeed() * frameDeltaTime))
					 / BLOCK_SIZE))) == false)
    {
      nodePosition.Z += player->getSpeed() * frameDeltaTime;
      nodeRotation = vector3df(0, 180, 0);
      direction[idxDir] = Action::UP;
      originalX = (int)(nodePosition.X / BLOCK_SIZE);
      originalY = (int)(nodePosition.Z / BLOCK_SIZE);
      hasMoved = true;
    }
}

void	Game::goDown(Entity *player)
{
  if (checkCollision(*player, frameDeltaTime, this->getCase(originalX, originalY),
		     this->getCase((int)((nodePosition.X ) / BLOCK_SIZE),
				   (int)((nodePosition.Z - 3.2 -
					  (player->getSpeed() * frameDeltaTime))
					 / BLOCK_SIZE))) == false)
    {
      nodePosition.Z -= player->getSpeed() * frameDeltaTime;
      nodeRotation = vector3df(0, 0, 0);
      direction[idxDir] = Action::DOWN;
      originalX = (int)(nodePosition.X / BLOCK_SIZE);
      originalY = (int)(nodePosition.Z / BLOCK_SIZE);
      hasMoved = true;
    }
}

void	Game::goLeft(Entity *player)
{
  if (checkCollision(*player, frameDeltaTime, this->getCase(originalX, originalY),
		     this->getCase((int)((nodePosition.X - 3.2 -
					  (player->getSpeed() * frameDeltaTime))
					 / BLOCK_SIZE),
				   (int)(nodePosition.Z ) / BLOCK_SIZE)) == false)
    {
      nodePosition.X -= player->getSpeed() * frameDeltaTime;
      if (idxDir > 0)
	{
	  if (direction[idxDir - 1] == Action::UP)
	    nodeRotation = vector3df(0, 135, 0);
	  else if (direction[idxDir - 1] == Action::DOWN)
	    nodeRotation = vector3df(0, 45, 0);
	}
      else
	nodeRotation = vector3df(0, 90, 0);
      hasMoved = true;
    }
}

void	Game::goRight(Entity *player)
{
  if (checkCollision(*player, frameDeltaTime, this->getCase(originalX, originalY),
		     this->getCase((int)((nodePosition.X + 3.2 +
					  (player->getSpeed() * frameDeltaTime))
					 / BLOCK_SIZE),
				   (int)(nodePosition.Z ) / BLOCK_SIZE)) == false)
    {
      nodePosition.X += player->getSpeed() * frameDeltaTime;
      if (idxDir > 0)
	{
	  if (direction[idxDir - 1] == Action::UP)
	    nodeRotation = vector3df(0, 225, 0);
	  else if (direction[idxDir - 1] == Action::DOWN)
	    nodeRotation = vector3df(0, 315, 0);
	}
      else
	nodeRotation = vector3df(0, 270, 0);
      hasMoved = true;
    }
}

void  Game::setDangerousZone(int &ix, int &iy, int radius)
{
  //std::cout << radius << std::endl;
  int up = 0, down = 0, left = 0, right = 0, i = 0;

  up = this->justCountUpRadius(radius, ix, iy);
  down = this->justCountDownRadius(radius, ix, iy);
  left = this->justCountLeftRadius(radius, ix, iy);
  right = this->justCountRightRadius(radius, ix, iy);

  for (i = 0; i <= up && this->map[ix][iy + i].getDangerous() != DANGEROUS ||
	 this->map[ix][iy + i].getDangerous() != NOT_WALKABLE; i++)
    this->map[ix][iy + i].setDangerous(DANGEROUS);
  for (i = 1; i <= down && this->map[ix][iy - i].getDangerous() != DANGEROUS ||
	 this->map[ix][iy - i].getDangerous() != NOT_WALKABLE; i++)
    this->map[ix][iy - i].setDangerous(DANGEROUS);
  for (i = 1; i <= left && this->map[ix - i][iy].getDangerous() != DANGEROUS ||
	 this->map[ix - i][iy].getDangerous() != NOT_WALKABLE; i++)
    this->map[ix - i][iy].setDangerous(DANGEROUS);
  for (i = 1; i <= right && this->map[ix + i][iy].getDangerous() != DANGEROUS ||
	 this->map[ix + i][iy].getDangerous() != NOT_WALKABLE; i++)
    this->map[ix + i][iy].setDangerous(DANGEROUS);
}

void	Game::updateBomb()
{
  Bomb	*bomb;

  for (std::list<vector2di>::iterator itBomb = this->bombCoorList.begin();
       itBomb != this->bombCoorList.end(); ++itBomb)
    {
      bomb = static_cast<Bomb *> (this->getCase(itBomb->X, itBomb->Y).getObject());
      setDangerousZone(itBomb->X, itBomb->Y, bomb->getBombRadius());
      if ((bomb->hasExploded() == false &&
	   device->getTimer()->getTime() - bomb->getTime() > 2000) ||
	  (bomb->hasExploded() == false &&
	   map[itBomb->X][itBomb->Y].getExplosion() > 0))
	{
	  this->soundManager->playSound(SoundManager::BombExplosion_medium);
	  launchExplosion(bomb, itBomb->X, itBomb->Y);
	}
      if (device->getTimer()->getTime() - bomb->getTime() > 3000)
	{
	  this->entityList[bomb->getEntityNbr()]->removeBombCount();
	  for (std::list<vector2di>::const_iterator itExplosion =
		 bomb->getExplosionList().begin();
	       itExplosion != bomb->getExplosionList().end(); itExplosion++)
	    {
	      this->map[itExplosion->X][itExplosion->Y].removeExplosion();
	    }
	  this->getCase(itBomb->X, itBomb->Y).destroy();
	  itBomb = this->bombCoorList.erase(itBomb);
	}
    }
}

bool			Game::checkCollision(Entity &it,
					     const f32 &frameDeltaTime,
					     const Case &actualCase,
					     const Case &nextCase)
{
  BlockType::BlockType	nextType = nextCase.getBlockType();
  BlockType::BlockType	actualType = actualCase.getBlockType();
  float			size;

  size = it.getSize();
  if (nextType != BlockType::HARD
      && nextType != BlockType::LIGHT &&
      (nextType != BlockType::BOMB ||
       (nextType == BlockType::BOMB &&
	actualType == BlockType::BOMB && &nextCase == &actualCase)))
    return (false);
  return (true);
}

void			Game::checkExplosion(Entity *it)
{
  this->nodePosition = it->getPosition();
  this->originalX = (int)(nodePosition.X / BLOCK_SIZE);
  this->originalY = (int)(nodePosition.Z / BLOCK_SIZE);

  if (map[this->originalX][this->originalY].getExplosion() > 0)
    {
      it->kill();
      this->soundManager->playSound(SoundManager::Death);
    }
}

void                    Game::checkItem(Entity *it)
{
  this->nodePosition = it->getPosition();
  this->originalX = (int)(nodePosition.X / BLOCK_SIZE);
  this->originalY = (int)(nodePosition.Z / BLOCK_SIZE);

  switch(map[this->originalX][this->originalY].getBlockType())
    {
    case (BlockType::SPEED_ITEM):
      this->soundManager->playSound(SoundManager::GetItem);
      map[this->originalX][this->originalY].destroy();
      map[this->originalX][this->originalY].setDangerous(SAFE);
      it->addSpeed(2);
      break;
    case (BlockType::BOMB_ITEM):
      this->soundManager->playSound(SoundManager::GetItem);
      map[this->originalX][this->originalY].destroy();
      map[this->originalX][this->originalY].setDangerous(SAFE);
      it->addBombNumber();
      break;
    case (BlockType::RADIUS_ITEM):
      this->soundManager->playSound(SoundManager::GetItem);
      map[this->originalX][this->originalY].destroy();
      map[this->originalX][this->originalY].setDangerous(SAFE);
      it->addBombRadius();
      break;
    }
}

void			Game::putBomb(Entity* itEntity)
{
  if (this->getCase(originalX, originalY).getBlockType() == BlockType::EMPTY &&
      itEntity->canPutBomb())
    {
      this->getCase(originalX, originalY).setObject(
						    new Bomb(originalX, originalY, this->texturePack, this->meshPack, this->smgr, this->effect, itEntity->getID(), this->device->getTimer()->getTime(), itEntity->getBombRadius()));
      this->addBombCoor(originalX, originalY);
      this->soundManager->playSound(SoundManager::SetBomb);
      itEntity->addBombCount();
    }
}
