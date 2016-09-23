#ifndef PLAYER_HH
# define PLAYER_HH

# include <irrlicht.h>
# include "Item.hh"
# include "Binding.hh"
# include "EventReceiver.hpp"
# include "Entity.hh"

class Player : public Entity
{
public:
  Player(TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *video, EffectHandler *_effect,
	       irr::core::vector2di &pos, int id, Binding Keys, MyEventReceiver *);
  const Binding&	getKey() const;
  void			getAction(Action::Action *);
private:
  Binding		keys;
  MyEventReceiver	*receiver;
};

#endif
