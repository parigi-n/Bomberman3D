#include <iostream>
#include "Bot.hh"

Bot::Bot(TexturePack *texture, MeshPack *mesh,
	 SceneManager *smgr,
	 VideoDriver *video,
	 EffectHandler *_effect,
	 irr::core::vector2di &pos, int _id,
	 std::vector<std::vector<Case> > &_map,
	 std::vector<Entity *> &_entityList)
  : Entity(texture, mesh, smgr, video, _effect, pos, _id,  Entity::BOT), timer(clock())
{
  this->ai = new AI(_map, _entityList, this);
}

void			Bot::getAction(Action::Action *move)
{
  int			i = 0;

  if (((float)(clock() - timer) / CLOCKS_PER_SEC) > 0.2)
    {
      timer = clock();
      action[i++] = ai->Play();
      while (i < 3)
	action[i++] = action[i - 1];
    }
  move[0] = action[0];
  move[1] = action[1];
  move[2] = action[2];
  //printf("%i %i %i\n", move[0], move[1], move[2]);
}
