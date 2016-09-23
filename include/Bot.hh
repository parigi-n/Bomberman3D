#ifndef BOT_HH
# define BOT_HH

# include <ctime>
# include <irrlicht.h>
# include "Item.hh"
# include "Binding.hh"
# include "Entity.hh"
# include "AI.hh"

class Bot : public Entity
{
public:
  Bot(TexturePack *texture, MeshPack *mesh, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *video, EffectHandler *_effect,
	       irr::core::vector2di &pos, int id,
      std::vector<std::vector<Case> > &_map,
      std::vector<Entity *> &_entityList);

  const Binding&	getKey() const;

  void			getAction(Action::Action *);
  void			setAI(IAI *ai);
  IAI const		*getAI();

private:
  IAI			*ai;
  Action::Action	action[3];
  clock_t		timer;
};

#endif
