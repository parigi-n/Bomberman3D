#ifndef ITEM_HH
# define ITEM_HH

# include <irrlicht.h>
# include <XEffects.h>
# include "Define.hh"
# include <list>

class Explosion
{
public:
  Explosion();
  ~Explosion();
  void setExplosion(const vector3df& position, const int upSize, const int downSize, const int leftSize, const int rightSize, EffectHandler *effect);

private:
  irr::scene::IParticleSystemSceneNode *up;
  irr::scene::IParticleSystemSceneNode *down;
  irr::scene::IParticleSystemSceneNode *left;
  irr::scene::IParticleSystemSceneNode *right;
  EffectHandler *effect;
};

class Item
{
  Item();
  ~Item();

class Bomb
{
public:
  Bomb(irr::scene::IMeshSceneNode *model, const int player, const u32 &timer, EffectHandler *effect);
  ~Bomb();

  const vector3df& getPosition() const;
  const irr::f32& getX() const;
  const irr::f32& getY() const;
  const int getIntX() const;
  const int getIntY() const;
  void setPosition(const vector3df &newpos);
  const u32 &getTime() const;
  const bool &hasExploded() const;
  void explode(int upSize, int downSize, int leftSize, int rightSize);
  void addExplosionCase(const vector2di &pos);
  const int &getEntityNbr() const;
  const std::list<vector2di> &getExplosionList() const;

private:
  irr::scene::IMeshSceneNode* model;
  EffectHandler *effect;
  u32 timer;

  int bombRadius; //default = 1
  int bombNumber; //default = 1

  int player;

  bool exploded;
  Explosion explosion;
  std::list<vector2di> explosionCoorList;
};

class Item
{
public:
  Item(irr::scene::IMeshSceneNode *model, irr::scene::IMeshSceneNode *socle, EffectHandler *effect);
  ~Item();
  const vector3df& getPosition() const;
  const irr::f32& getX() const;
  const irr::f32& getY() const;
  const int getIntX() const;
  const int getIntY() const;

private:
  irr::scene::IMeshSceneNode* model;
  irr::scene::IMeshSceneNode* socle;
  irr::scene::ISceneNodeAnimator* animator;
  EffectHandler *effect;
};

#endif
