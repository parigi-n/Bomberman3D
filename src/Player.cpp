#include "Player.hh"

Player::Player(TexturePack *texture, MeshPack *mesh,
	       irr::scene::ISceneManager *smgr, VideoDriver *video,
	       EffectHandler *_effect,
	       vector2di &pos,
	       int _id, Binding _keys, MyEventReceiver *_receiver)
  : Entity(texture, mesh, smgr, video, _effect, pos, _id, Entity::PLAYER),
    keys(_keys), receiver(_receiver)
{
}

const Binding&		Player::getKey() const
{
  return (this->keys);
}

void			Player::getAction(Action::Action *move)
{
  int			i = 0;

  move[0] = Action::NONE;
  if (receiver->IsKeyDown(keys.action()))
    move[i++] = Action::ACTION;
  if (receiver->IsKeyDown(keys.up()))
    move[i++] = Action::UP;
  else if (receiver->IsKeyDown(keys.down()))
    move[i++] = Action::DOWN;
  if (receiver->IsKeyDown(keys.left()))
    move[i++] = Action::LEFT;
  else if(receiver->IsKeyDown(keys.right()))
    move[i++] = Action::RIGHT;
  while (i < 3)
    move[i++] = Action::NONE;
}
