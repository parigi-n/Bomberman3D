#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <XEffects.h>

#include "Game.hh"

#define BLOCK_SIZE 10

Case::Case(TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, EffectHandler *effect)
{
  this->object = NULL;
  this->effect = effect;
  this->texture = texture;
  this->mesh = mesh;
  this->smgr = smgr;
  this->explosion = 0;
}

Case::Case()
{
}

void	Case::setBlockType(BlockType::BlockType &block)
{
  this->block = block;
}

void  Case::setDangerous(int dangerous)
{
  this->isDangerous = NOT_WALKABLE;
  return;
  BlockType::BlockType bloc = this->getBlockType();
  if (bloc == BlockType::LIGHT || bloc == BlockType::HARD)
    {
    	this->isDangerous = NOT_WALKABLE;
    	return;
    }
  if (this->getDangerous() != dangerous)
    {
      if ((bloc == BlockType::BOMB_ITEM || bloc == BlockType::RADIUS_ITEM || bloc == BlockType::SPEED_ITEM) && dangerous == SAFE)
	this->isDangerous = INTERESTING;
      else
  	{
	  this->isDangerous = dangerous;
	}
    }
}

int  Case::getDangerous()
{
  return (this->isDangerous);
}

void	Case::setObject(Object *object)
{
  this->object = object;
}

Object *Case::getObject() const
{
  return (this->object);
}
/*
void	Case::setBlockType(const BlockType::BlockType &block)
{
  this->block = block;
}*/

BlockType::BlockType		Case::getBlockType() const
{
  if (this->object == NULL)
    {
      return (BlockType::EMPTY);
    }
  return (this->object->getBlockType());
}

void	Case::spawnBonus(int &x, int &y)
{
  if (rand() % ITEM_CHANCE == 0)
  {
    this->setObject(new Item(x, y, this->texture, this->mesh, this->smgr, this->effect));
    this->setDangerous(INTERESTING);
  }
  else
    this->object = NULL;
}

void	Case::destroy()
{
  int x = 0;
  int y = 0;

  if (this->object != NULL)
    {
      switch (this->object->getBlockType())
	{
	case BlockType::LIGHT:
	  x = this->object->getX();
	  y = this->object->getY();
	  delete (static_cast<Block *> (this->object));
	  this->spawnBonus(x, y);
	  break;
	case BlockType::HARD:
	  x = this->object->getX();
	  y = this->object->getY();
	  delete (static_cast<Block *> (this->object));
	  this->spawnBonus(x, y);
	  break;
	case BlockType::BOMB:
	  delete (static_cast<Bomb *> (this->object));
	  this->object = NULL;
	  break;
	case BlockType::SPEED_ITEM:
	  delete (static_cast<Item *> (this->object));
	  this->object = NULL;
	  break;
	case BlockType::RADIUS_ITEM:
	  delete (static_cast<Item *> (this->object));
	  this->object = NULL;
	  break;
	case BlockType::BOMB_ITEM:
	  delete (static_cast<Item *> (this->object));
	  this->object = NULL;
	  break;
	case BlockType::EMPTY:
	  std::cout << "Error";
	  break;
	}
    }
}

void	Case::addExplosion()
{
  this->explosion++;
  this->setDangerous(NOT_WALKABLE);
}

void	Case::removeExplosion()
{
  this->explosion--;
  if (this->explosion == 0)
    this->setDangerous(SAFE);
}

const int     &Case::getExplosion() const
{
  return (this->explosion);
}
