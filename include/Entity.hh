#ifndef ENTITY_HH
# define ENTITY_HH

# include <irrlicht.h>
# include "BlockType.hh"
# include "Item.hh"
# include "Binding.hh"

# define DEFAULT_SPEED		35
# define DEFAULT_BRADIUS	1
# define DEFAULT_BNUMBER	1
# define NB_ACTION_PER_FRAME	3
# define MAX_SPEED		50

class Entity
{
public:
  enum Type
    {
      UNDEFINED,
      PLAYER,
      BOT
    };

  Entity(TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *video, EffectHandler *_effect,
	       irr::core::vector2di &pos, int id, Type = UNDEFINED);

  virtual ~Entity();
  const vector3df&	getPosition() const;
  const vector3df&	getRotation() const;
  const irr::f32&	getX() const;
  const irr::f32&	getY() const;
  void			setPosition(const vector3df &newpos);
  void			setRotation(const vector3df &newpos);
  const Binding&	getKey() const;
  const float&		getSize() const;
  const Type&		getType() const;
  const int&		getID() const;
  //void			setFrameLoop(const irr::s32 &begin,
	//			     const irr::s32 &end);
  void			setMove(bool status);
  const bool		getMove() const;
  virtual void		getAction(Action::Action *);
  const bool		&isAlive() const;
  void			kill();

  void			run();
  void			stop();

  //action
  void			setBombCount(const int &);
  void			setBombNumber(const int &);
  void			setBombRadius(const int &);
  void			setSpeed(const float &);

  const int		&getBombNumber() const;
  const int		&getBombRadius() const;
  const int		&getBombCount() const;
  const float		&getSpeed() const;

  void                  addBombNumber();
  void                  addBombRadius();
  void                  addSpeed(const float &nb);

  void			addBombCount();
  void			removeBombCount();
  const bool		canPutBomb() const;

private:
  float					size;
  AnimatedMeshSceneNode			*model;
  MeshScene				*staticModel;
  ITexture				*texture;

  int					bombRadius;
  int					bombNumber;
  float					speed;

  int					bombCount; //initialize = 0
  bool					alive;
  int					id;
  Type					type;
  bool					moving;
  EffectHandler				*effect;
};

#endif
