#include "Item.hh"

Explosion::Explosion()
{
  this->up = NULL;
  this->down = NULL;
  this->right = NULL;
  this->left = NULL;
  this->effect = NULL;
}

Explosion::~Explosion()
{
  if (this->up != NULL)
    {
      this->effect->removeShadowFromNode(this->up);
      //this->up->removeAll();
      this->up->remove();
    }
  if (this->down != NULL)
    {
      this->effect->removeShadowFromNode(this->down);
      //this->down->removeAll();
      this->down->remove();
    }
  if (this->left != NULL)
    {
      this->effect->removeShadowFromNode(this->left);
      //this->left->removeAll();
      this->left->remove();
    }
  if (this->right != NULL)
    {
      this->effect->removeShadowFromNode(this->right);
      //this->right->removeAll();
      this->right->remove();
    }
  if (this->height != NULL)
    {
      this->effect->removeShadowFromNode(this->height);
      //this->height->removeAll();
      this->height->remove();
    }
}

void	Explosion::setExplosion(const vector3df& position, const int upSize, const int downSize, const int leftSize, const int rightSize, EffectHandler *effect, irr::video::ITexture *texture)
{
  this->effect = effect;
  
  SceneManager *smgr = this->effect->getIrrlichtDevice()->getSceneManager();
  VideoDriver* video = this->effect->getIrrlichtDevice()->getVideoDriver();

  //----HEIGHT-----
  this->height = smgr->addParticleSystemSceneNode(false);
  this->effect->addShadowToNode(this->height, EFT_NONE, ESM_EXCLUDE);

  ParticleEmitter* em = this->height->createSphereEmitter(vector3df(1, 3, 1),			// emitter size
								       5,					//Radius
								       vector3df(0, 0.018, 0),                           // initial direction
								       5,10,                                          // emit rate
								       irr::video::SColor(0,255,255,255),               // darkest color
								       irr::video::SColor(0,255,255,255),              // brightest color
								       1000,
								       1000,
								       0,                                              // min and max age, angle
								       irr::core::dimension2df(20, 20),                        // min size
								       irr::core::dimension2df(25, 25));                       // max size
  
  this->height->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it

  //irr::scene::IParticleAffector* affector = this->height->createFadeOutParticleAffector();

  //this->height->addAffector(affector); // same goes for the affector
  
  this->height->setPosition(position);
  this->height->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->height->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  this->height->setMaterialTexture(0, texture);
  this->height->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  
  //----UP-----
  this->up = smgr->addParticleSystemSceneNode(false);
  this->effect->addShadowToNode(this->up, EFT_NONE, ESM_EXCLUDE);
  
  em = this->up->createBoxEmitter(aabbox3d(-3,0,-3,3,1,3),	// emitter size
				  vector3df(0, 0, 0.2),				// initial direction
				  30,35,						// emit rate
				  irr::video::SColor(0,255,255,50),		// darkest color
				  irr::video::SColor(0,255,255,255),		// brightest color
				  (upSize * 50) + (BLOCK_SIZE / 4) * 5,
				  (upSize * 50) + (BLOCK_SIZE / 4) * 5,
				  0,						// min and max age, angle
				  irr::core::dimension2df(15, 15),			// min size
				  irr::core::dimension2df(15, 15));			// max size

  this->up->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it
  
  this->up->setPosition(position);
  this->up->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->up->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  this->up->setMaterialTexture(0, texture);
  this->up->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  
  //----DOWN-----
  this->down = smgr->addParticleSystemSceneNode(false);
  this->effect->addShadowToNode(this->down, EFT_NONE, ESM_EXCLUDE);
  
  em = this->down->createBoxEmitter(aabbox3d(-3,0,-3,3,1,3),	// emitter size
				    vector3df(0, 0, -0.2),			// initial direction
				    30,35,					// emit rate
				    irr::video::SColor(0,255,255,255),		// darkest color
				    irr::video::SColor(0,255,255,255),		// brightest color
				    (downSize * 50) + (BLOCK_SIZE / 4) * 5,
				    (downSize * 50) + (BLOCK_SIZE / 4) * 5,
				    0,						// min and max age, angle
				    irr::core::dimension2df(15, 15),		// min size
				    irr::core::dimension2df(15, 15));		// max size
  
  this->down->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it
  
  this->down->setPosition(position);
  this->down->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->down->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  this->down->setMaterialTexture(0, texture);
  this->down->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  
  //----LEFT-----
  this->left = smgr->addParticleSystemSceneNode(false);
  this->effect->addShadowToNode(this->left, EFT_NONE, ESM_EXCLUDE);
  
  em = this->left->createBoxEmitter(aabbox3d(-3,0,-3,3,1,3),	// emitter size
				    vector3df(-0.2, 0, 0),			// initial direction
				    30,35,					// emit rate
				    irr::video::SColor(0,255,255,255),		// darkest color
				    irr::video::SColor(0,255,255,255),		// brightest color
				    (leftSize * 50) + (BLOCK_SIZE / 4) * 5,
				    (leftSize * 50) + (BLOCK_SIZE / 4) * 5,
				    0,						// min and max age, angle
				    irr::core::dimension2df(15, 15),		// min size
				    irr::core::dimension2df(15, 15));		// max size
  
  this->left->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it
  
  this->left->setPosition(position);
  this->left->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->left->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  this->left->setMaterialTexture(0, texture);
  this->left->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  
  //----RIGHT-----
  this->right = smgr->addParticleSystemSceneNode(false);
  this->effect->addShadowToNode(this->right, EFT_NONE, ESM_EXCLUDE);
  
  em = this->right->createBoxEmitter(aabbox3d(-3,0,-3,3,1,3),	// emitter size
				     vector3df(0.2, 0, 0),			// initial direction
				     30,35,					// emit rate
				     irr::video::SColor(0,255,255,255),		// darkest color
				     irr::video::SColor(0,255,255,255),		// brightest color
				     (rightSize * 50) + (BLOCK_SIZE / 4) * 5,
				     (rightSize * 50) + (BLOCK_SIZE / 4) * 5,
				     0,						// min and max age, angle
				     irr::core::dimension2df(15, 15),		// min size
				     irr::core::dimension2df(15, 15));		// max size
  
  this->right->setEmitter(em); // this grabs the emitter
  em->drop(); // so we can drop it here without deleting it
  
  this->right->setPosition(position);
  this->right->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->right->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  this->right->setMaterialTexture(0, texture);
  this->right->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Object::Object(int &x, int &y, TexturePack *texture,
	       MeshPack *mesh, SceneManager *smgr,
	       EffectHandler *effect)
{
  this->x = x;
  this->y = y;
  this->blockType = BlockType::EMPTY;

  this->effect = effect;
  this->texture = texture;
  this->mesh = mesh;
  this->smgr = smgr;
}

const int&    Object::getX() const
{
  return (this->x);
}

const int&    Object::getY() const
{
  return (this->y);
}

const BlockType::BlockType &Object::getBlockType() const
{
  return (this->blockType);
}

Bomb::Bomb(int &x, int &y, TexturePack *texture,
	   MeshPack *mesh, SceneManager *smgr,
	   EffectHandler *effect, const int &player,
	   const u32 &timer, int const &_radius) :
  Object(x, y, texture, mesh, smgr, effect), bombRadius(_radius)
{
  this->model = smgr->addMeshSceneNode(mesh->getMesh(BlockType::BOMB), 0, -1,
    vector3df((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), 0, (float)(y * BLOCK_SIZE + BLOCK_SIZE / 2)));;
  effect->addShadowToNode(this->model, EFT_16PCF, ESM_BOTH);
  this->model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->model->setScale(vector3df(1.0, 1.0, 1.0));
  this->timer = timer;
  this->player = player;

  this->exploded = false;
  this->blockType = BlockType::BOMB;
}

Bomb::~Bomb()
{
  if (this->model != NULL)
    {
      effect->removeShadowFromNode(this->model);
      this->model->remove();
    }
  this->blockType = BlockType::EMPTY;
}

const int		&Bomb::getBombRadius() const
{
  return (bombRadius);
}

const u32		&Bomb::getTime() const
{
  return (timer);
}

const bool		&Bomb::hasExploded() const
{
  return (exploded);
}

void			Bomb::explode(int upSize, int downSize,
				      int leftSize, int rightSize)
{
  this->exploded = true;
  explosion.setExplosion(this->model->getPosition(), upSize, downSize, leftSize, rightSize, this->effect, this->texture->getTexture(BlockType::TPARTICULE1));
}

void			Bomb::addExplosionCase(const vector2di &pos)
{
    this->explosionCoorList.push_back(pos);
}

const int		&Bomb::getEntityNbr() const
{
  return (player);
}

const std::list<vector2di>	&Bomb::getExplosionList() const
{
  return (explosionCoorList);
}

Block::Block(int &x, int &y, TexturePack *texture,
	     MeshPack *mesh,
	     SceneManager *smgr,
	     EffectHandler *effect,
	     BlockType::BlockType block, bool useShadow) :
Object(x, y, texture, mesh, smgr, effect)
{
	this->useShadow = useShadow;
	this->cube = smgr->addCubeSceneNode(BLOCK_SIZE);
    if (this->useShadow == true)
    {
    	effect->addShadowToNode(cube, EFT_16PCF, ESM_CAST);
    	cube->setPosition(vector3df(x * BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 4, y * BLOCK_SIZE + BLOCK_SIZE / 2));
    }
    else
    	cube->setPosition(vector3df(x * BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2, y * BLOCK_SIZE + BLOCK_SIZE / 2));
    if (BlockType::LIGHT)
      cube->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, true);
    else
      cube->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false); //Suprime flou des textures
      switch (block)
      {
        case (BlockType::HARD):
          if (useShadow == true)
            cube->setMaterialTexture(0, texture->getTexture(BlockType::THARD));
          else
          	cube->setMaterialTexture(0, texture->getTexture(BlockType::TEND));
          break;
        case (BlockType::LIGHT):
          cube->setMaterialTexture(0, texture->getTexture(BlockType::TLIGHT));
          break;
      }
  this->blockType = block;
}

Block::~Block()
{
  if (this->cube != NULL)
    {
      effect->removeShadowFromNode(this->cube);
      this->cube->remove();
    }
  this->blockType = BlockType::EMPTY;
}

Item::Item(int &x, int &y, TexturePack *texture, MeshPack *mesh,
	   SceneManager *smgr, EffectHandler *effect) :
Object(x, y, texture, mesh, smgr, effect)
{
  this->effect = effect;

    switch (rand() % NB_BONUS)
    {
    case 0:
      this->model = smgr->addMeshSceneNode(mesh->getMesh(BlockType::SPEED_ITEM), 0, -1,
					   vector3df((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), BLOCK_SIZE / 2, (float)(y * BLOCK_SIZE + BLOCK_SIZE / 2)));
      this->blockType = BlockType::SPEED_ITEM;
      this->model->setScale(vector3df(13.0, 13.0, 13.0));
      break;
    case 1:
      this->model = smgr->addMeshSceneNode(mesh->getMesh(BlockType::BOMB_ITEM), 0, -1,
					   vector3df((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), BLOCK_SIZE / 2, (float)(y * BLOCK_SIZE + BLOCK_SIZE / 2)));
      this->blockType = BlockType::BOMB_ITEM;
      this->model->setScale(vector3df(1.0, 1.0, 1.0));
      break;
    case 2:
      this->model = smgr->addMeshSceneNode(mesh->getMesh(BlockType::RADIUS_ITEM), 0, -1,
					   vector3df((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), BLOCK_SIZE / 2, (float)(y * BLOCK_SIZE + BLOCK_SIZE / 2)));
      this->blockType = BlockType::RADIUS_ITEM;
      this->model->setScale(vector3df(4, 4, 4));
      break;
    }

  this->animator = smgr->createRotationAnimator(vector3df(0,1,0));
  this->model->addAnimator(this->animator);
  this->model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->effect->addShadowToNode(this->model, EFT_16PCF, ESM_CAST);

  this->socle = smgr->addMeshSceneNode(mesh->getMesh(BlockType::SOCLE), 0, -1,
    vector3df((float)(x * BLOCK_SIZE + BLOCK_SIZE / 2), 0, (float)(y * BLOCK_SIZE + BLOCK_SIZE / 2)));
  this->socle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->effect->addShadowToNode(this->socle, EFT_16PCF, ESM_RECEIVE);
  this->socle->setScale(vector3df(3.0, 3.0, 3.0));
}

Item::~Item()
{
  if (this->model != NULL)
    {
      if (this->animator != NULL)
	this->animator->drop();
      this->effect->removeShadowFromNode(this->model);
      this->model->remove();
    }
  if (this->socle != NULL)
    {
      this->effect->removeShadowFromNode(this->socle);
      this->socle->remove();
    }
  this->blockType = BlockType::EMPTY;
}
