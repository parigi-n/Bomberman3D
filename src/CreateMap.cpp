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

bool Game::isBorder(int ix, int iy)
{
  if (iy == 1)
    {
      if (ix == 1 || ix == 2 || ix == length - 3 || ix == length - 2)
	return (true);
    }
  else if (iy == 2)
    {
      if (ix == 1 || ix == length - 2)
	return (true);
    }
  else if (iy == width - 2)
    {
      if (ix == 1 || ix == 2 || ix == length - 3 || ix == length - 2)
	return (true);
    }
  else if (iy == width - 3)
    {
      if (ix == 1 || ix == length - 2)
	return (true);
    }
  return (false);
}

void Game::createPlayer(irr::scene::IAnimatedMesh *playerMesh)
{
  Binding keyList[] = {Binding(irr::KEY_KEY_Z, irr::KEY_KEY_S,
			       irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_KEY_E),
		       Binding(irr::KEY_KEY_Y, irr::KEY_KEY_H,
			       irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_C),
		       Binding(irr::KEY_KEY_O, irr::KEY_KEY_L,
			       irr::KEY_KEY_K, irr::KEY_KEY_M, irr::KEY_KEY_P),
		       Binding(irr::KEY_UP, irr::KEY_DOWN,
			       irr::KEY_LEFT, irr::KEY_RIGHT, irr::KEY_RCONTROL)};
  vector2di posPlayer[4] = {vector2di(1,1),
			    vector2di(length - 2, 1),
			    vector2di(1, width - 2),
			    vector2di(length - 2, width - 2)};
  int i = 0;

  entityList.clear();
  botList.clear();
  playerList.clear();
  while (i < MAX_PLAYER)
    {
      if (i < playerNb)
	{
	  Player *tmp = new Player(this->texturePack, this->meshPack, this->smgr, this->video, this->effect, posPlayer[i],
				   i, keyList[i], receiver);
	  entityList.push_back(tmp);
	  playerList.push_back(tmp);
	}
      else
	{
	  Bot *tmp = new Bot(this->texturePack, this->meshPack, this->smgr, this->video, this->effect, posPlayer[i],
			     i, this->map, this->entityList);
	  entityList.push_back(tmp);
	  botList.push_back(tmp);
	}
      i++;
    }
}

void Game::placeBlock(int random)
{
  int ix = 0;
  int iy = 0;

  while (ix < length)
    {
      iy = 0;
      while (iy < width)
	{
	  if (ix == 0 || iy == 0 || ix == length - 1 || iy == width - 1)
	    {
	      map[ix][iy].setObject(new Block(ix, iy, this->texturePack, this->meshPack, this->smgr, this->effect, BlockType::HARD, false));
	    }
	  else if (ix % 2 == 0 && iy % 2 == 0)
	    {
	      map[ix][iy].setObject(new Block(ix, iy, this->texturePack, this->meshPack, this->smgr, this->effect, BlockType::HARD, true));
	    }
	  else if (rand() % random == 0 && isBorder(ix, iy) == false)
	    {
	      map[ix][iy].setObject(new Block(ix, iy, this->texturePack, this->meshPack, this->smgr, this->effect, BlockType::LIGHT, true));
	    }
	  // else
	  //   {
	  //     map[ix][iy].setObject(new Block(ix, iy, this->texturePack, this->meshPack, this->smgr, this->effect, BlockType::EMPTY, true));
	  //   }
	  map[ix][iy].setDangerous(SAFE);
	  iy++;
	}
      ix++;
    }
}

void Game::initMap(int _x, int _y, int _playerNb, int random, bool graphism)
{
  playerNb = _playerNb;
  length = _x;
  width = _y;
  this->video = this->device->getVideoDriver();
  this->smgr = this->device->getSceneManager();
  smgr->clear();
  //smgr->setAmbientLight(irr::video::SColor(1.0, 1.0, 1.0, 1.0));
  bombCoorList.clear();
  if (this->effect != NULL)
    delete (this->effect);
  EffectHandler *effect = new EffectHandler(device, video->getScreenSize(),
					    false, false, false);

  effect->setAmbientColor(irr::video::SColor(255, 100, 100, 255));
  effect->setClearColour(irr::video::SColor(0x0));
  if (graphism == false)
    effect->addShadowLight(SShadowLight(2048, vector3df(-80, 500, -80),
					vector3df(150, 0, 150),
					irr::video::SColor(255, 255, 255, 255),
					10.0f, 700.0f, 1000.0f * irr::core::DEGTORAD));
  this->effect = effect;

  // SOl de la map :
  irr::scene::ISceneNode * cube;
  irr::scene::IMesh* grid = smgr->getGeometryCreator()->
    createPlaneMesh(irr::core::dimension2df(BLOCK_SIZE * 2, BLOCK_SIZE * 2),
		    irr::core::dimension2d<u32>((length / 2), (width / 2)), 0,
		    irr::core::dimension2df((length / 2), (width / 2)));

  this->grid = smgr->addMeshSceneNode(grid);
  this->grid->setPosition(vector3df(length / 2 * BLOCK_SIZE, 0, width / 2 * BLOCK_SIZE));
  this->grid->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  //this->grid->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
  this->grid->setMaterialTexture(0, texturePack->getTexture(BlockType::TGRID));
  this->effect->addShadowToNode(this->grid, EFT_16PCF, ESM_RECEIVE); //Le plan n'emet pas d'ombre, mais en reçoit

  //Map
  std::vector<std::vector<Case> > newMap(length, std::vector<Case>(width, Case(this->texturePack, this->meshPack, this->smgr, this->effect)));
  this->map = newMap;
  std::cout << this->map.size() << this->map[4].size();
  srand(time(NULL));
  //Creation de la skybox
  video->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->skybox = smgr->addSkyBoxSceneNode(
					  video->getTexture("media/desertsky_up.tga"),
					  video->getTexture("media/desertsky_dn.tga"),
					  video->getTexture("media/desertsky_rt.tga"),
					  video->getTexture("media/desertsky_lf.tga"),
					  video->getTexture("media/desertsky_ft.tga"),
					  video->getTexture("media/desertsky_bk.tga"));
  video->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);


  // Add a camera

  //xthis->camera = smgr->addCameraSceneNodeFPS();
  this->camera = smgr->addCameraSceneNode(0, vector3df(length * BLOCK_SIZE / 2,
						       145, width * BLOCK_SIZE / 2),
					  vector3df(length * BLOCK_SIZE / 2, -1000,
						    width * BLOCK_SIZE / 1.8));
  //this->camera->setFOV((float)(PI / 2.2));
}

void Game::createMap(int _x, int _y, int _playerNb, int random, bool graphism)
{
  initMap(_x, _y, _playerNb, random, graphism);
  placeBlock(random);
  createPlayer(this->meshPack->getMesh(BlockType::PLAYER));

}
