#include <sstream>
#include "Entity.hh"

Entity::Entity(TexturePack *texture, MeshPack *mesh,
	       SceneManager *smgr,
	       VideoDriver *video, EffectHandler *_effect,
	       vector2di &pos, int _id,
	       Entity::Type _type)
  : size(3.2), bombNumber(DEFAULT_BNUMBER),
    bombRadius(DEFAULT_BRADIUS),
    speed(DEFAULT_SPEED), bombCount(0),
    id(_id), type(_type), effect(_effect), moving(false)
{
  std::stringstream textureName;
  textureName << "media/Bomberman_" << _id + 1 << ".png";
  ITexture * textureBomberman;
  try
    {
      textureBomberman = video->getTexture(textureName.str().c_str());
      if (textureBomberman == NULL)
	throw (textureName.str().c_str());
    }
  catch (char const *file)
    {
      openError(file, this->effect->getIrrlichtDevice());
    }
  this->model = smgr->addAnimatedMeshSceneNode(mesh->getMesh(BlockType::PLAYER));
  if (this->model)
    {
      this->model->setPosition(vector3df((float)(pos.X * BLOCK_SIZE + BLOCK_SIZE / 2),
					 0,(float)(pos.Y * BLOCK_SIZE + BLOCK_SIZE / 2)));
      this->model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->model->setFrameLoop(0, 32);
      this->model->setAnimationSpeed(42);
      this->model->setMaterialTexture(0, textureBomberman);
      this->model->setScale(vector3df(8, 8, 8));
      this->model->setVisible(false);
      this->staticModel = smgr->addMeshSceneNode(mesh->getMesh(BlockType::BOMBERMAN));
      this->staticModel->setPosition(vector3df((float)(pos.X * BLOCK_SIZE + BLOCK_SIZE / 2),
					       0,(float)(pos.Y * BLOCK_SIZE + BLOCK_SIZE / 2)));
      this->staticModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->staticModel->setMaterialTexture(0, textureBomberman);
      // this->staticModel->setFrameLoop(33, 34);
      // this->staticModel->setAnimationSpeed(0);
      this->staticModel->setScale(vector3df(8, 8, 8));
      //this->effect->addShadowToNode(this->staticModel, EFT_16PCF, ESM_CAST);
      this->staticModel->setVisible(true);
    }
  this->alive = true;
}

Entity::~Entity()
{
}

const vector3df&	Entity::getPosition() const
{
  return (this->model->getPosition());
}

const vector3df&	Entity::getRotation() const
{
  return (this->model->getRotation());
}

const float&		Entity::getX() const
{
  return (this->model->getPosition().X);
}
const float&		Entity::getY() const
{
  return (this->model->getPosition().Z);
}

void			Entity::setPosition(const vector3df &newpos)
{
  this->model->setPosition(newpos);
  this->staticModel->setPosition(newpos);
}

void			Entity::setRotation(const vector3df &newpos)
{
  this->model->setRotation(newpos);
  this->staticModel->setRotation(newpos);
}

const float&		Entity::getSize() const
{
  return (this->size);
}

const bool		Entity::canPutBomb() const
{
  if (this->bombCount < this->bombNumber)
    return (true);
  else
    return (false);
}

void			Entity::run()
{
  if (this->model->isVisible() == false)
    {
      this->model->setVisible(true);
      this->effect->addShadowToNode(this->model, EFT_16PCF, ESM_CAST);
    }
  if (this->staticModel->isVisible() == true)
    {
      this->staticModel->setVisible(false);
      this->effect->removeShadowFromNode(this->staticModel);
      }
}

void			Entity::stop()
{
    if (this->staticModel->isVisible() == false)
    {
      this->staticModel->setVisible(true);
      this->effect->addShadowToNode(this->staticModel, EFT_16PCF, ESM_CAST);
    }
  if (this->model->isVisible() == true)
    {
      this->effect->removeShadowFromNode(this->model);
      this->model->setVisible(false);
      }
}

/*
void			Entity::setFrameLoop (const irr::s32 &begin,
					      const irr::s32 &end)
{
  if (begin != this->model->getStartFrame() && end != this->model->getEndFrame())
    {
      this->model->setFrameLoop(begin, end);
      if (begin - end == 0)
	this->model->setAnimationSpeed(0);
      else if ((int)(this->model->getAnimationSpeed()) != 42)
	this->model->setAnimationSpeed(42);
    }
}*/

const bool &Entity::isAlive() const
{
  return (this->alive);
}

void Entity::kill()
{
  this->alive = false;
  if (this->model != NULL)
    {
      this->effect->removeShadowFromNode(this->model);
      this->model->remove();
    }
  if (this->staticModel != NULL)
    {
      this->effect->removeShadowFromNode(this->staticModel);
      this->staticModel->remove();
    }
}

const Entity::Type &Entity::getType() const
{
  return (this->type);
}

const int &Entity::getID() const
{
  return (this->id);
}

void			Entity::setMove(bool status)
{
  moving = status;
}

const bool		Entity::getMove() const
{
  return (moving);
}

void			Entity::getAction(Action::Action *ok)
{
  (void)ok;
}


void			Entity::addBombCount()
{
  this->bombCount++;
}

void			Entity::removeBombCount()
{
  this->bombCount--;
}

const int		&Entity::getBombNumber() const
{
  return (this->bombNumber);
}

const int		&Entity::getBombCount() const
{
  return (this->bombCount);
}

const int		&Entity::getBombRadius() const
{
  return (this->bombRadius);
}

const float		&Entity::getSpeed() const
{
  return (this->speed);
}

void			Entity::setBombNumber(const int &nb)
{
  bombNumber = nb;
}

void			Entity::setBombCount(const int &nb)
{
  bombCount = nb;
}

void			Entity::setBombRadius(const int &nb)
{
  bombRadius = nb;
}

void			Entity::setSpeed(const float &nb)
{
  speed = nb;
}

void                    Entity::addBombNumber()
{
  bombNumber++;
}

void                    Entity::addBombRadius()
{
  bombRadius++;
}

void			Entity::addSpeed(const float &nb)
{
  speed += nb;
  if (speed > MAX_SPEED)
    speed = MAX_SPEED;
}
