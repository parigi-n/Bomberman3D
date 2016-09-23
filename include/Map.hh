#ifndef MAP_HH
# define MAP_HH

# define SAFE 0
# define DANGEROUS 1
# define INTERESTING 2
# define NOT_WALKABLE 3

# include <vector>
# include <irrlicht.h>
# include <XEffects.h>
# include "BlockType.hh"
# include "Item.hh"

class Case
{
public:
  Case(TexturePack *texture, MeshPack *mesh,
       irr::scene::ISceneManager *smgr,
       EffectHandler *effect);
  Case();
  BlockType::BlockType		getBlockType() const;

  void				setObject(Object *object);
  Object			*getObject() const;
  void				spawnBonus(int &x, int &y);

  void				setDangerous(int);
  int				getDangerous();

  void				addExplosion();
  void				removeExplosion();
  const int			&getExplosion() const;
  void				destroy();
  void				setBlockType(BlockType::BlockType &block);

private:
  BlockType::BlockType		block;
  TexturePack			*texture;
  MeshPack			*mesh;
  irr::scene::ISceneManager	*smgr;
  EffectHandler			*effect;

  Object			*object;
  int				explosion;
  int				isDangerous;

  int				x;
  int				y;
};

#endif
