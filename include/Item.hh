#ifndef ITEM_HH
# define ITEM_HH

# include <irrlicht.h>
# include <XEffects.h>
# include "Define.hh"
# include "Pack.hh"
# include <list>

class Explosion
{
public:
  Explosion();
  ~Explosion();
  void setExplosion(const vector3df& position, const int upSize, const int downSize, const int leftSize, const int rightSize, EffectHandler *effect, irr::video::ITexture *texture);

private:
  irr::scene::IParticleSystemSceneNode *up;
  irr::scene::IParticleSystemSceneNode *down;
  irr::scene::IParticleSystemSceneNode *left;
  irr::scene::IParticleSystemSceneNode *right;
  irr::scene::IParticleSystemSceneNode *height;
  EffectHandler *effect;
};

class Object
{
public:
  Object(int &x, int &y, TexturePack *texture, MeshPack *mesh,
	 irr::scene::ISceneManager *smgr, EffectHandler *effect);
  Object();
  const int& getX() const;
  const int& getY() const;
  const BlockType::BlockType &getBlockType() const;

protected:
  TexturePack *texture;
  MeshPack *mesh;
  irr::scene::ISceneManager *smgr;
  EffectHandler *effect;

  int x;
  int y;
  BlockType::BlockType blockType;
};

class Bomb : public Object
{
public:
  Bomb(int &x, int &y, TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, EffectHandler *effect, const int &player, const u32 &timer, const int &radius);
  ~Bomb();

  const u32		&getTime() const;
  const bool		&hasExploded() const;
  void			explode(int upSize, int downSize,
				int leftSize, int rightSize);
  void			addExplosionCase(const vector2di &pos);
  const int		&getEntityNbr() const;
  const int		&getBombRadius() const;
  const std::list<vector2di> &getExplosionList() const;

private:
  irr::scene::IMeshSceneNode* model;
  u32			timer;

  int			bombRadius;

  int			player;
  bool			exploded;
  Explosion		explosion;
  std::list<vector2di>	explosionCoorList;
};

class Block : public Object
{
public:
  Block(int &x, int &y, TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, EffectHandler *effect, BlockType::BlockType block, bool useShadow);
  ~Block();
private:
  irr::scene::IMeshSceneNode* cube;

  bool useShadow;
};


class Item : public Object
{
public:
  Item(int &x, int &y, TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, EffectHandler *effect);
  ~Item();
private:
  irr::scene::IMeshSceneNode* model;
  irr::scene::IMeshSceneNode* socle;
  irr::scene::ISceneNodeAnimator* animator;
};

#endif
