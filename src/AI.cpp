#include "AI.hh"

AI::AI(std::vector<std::vector<Case> > &_map, std::vector<Entity *> &_entityList,
       Entity *_me)
  : map(_map), entityList(_entityList), me(_me), goal(NULL)
{
  width = map[0].size();
  length = map.size();
}

Action::Action	AI::FindNewGoal(Graph::node *mypos)
{
  int i = 0;

  while (i < mypos->links.size())
    {
      if (mypos->links[i]->dangerous == 0)
	goal = mypos->links[i];
      i++;
    }
  if (goal == NULL)
    return (Action::NONE);
  return (goToGoal(mypos, goal));
}

Action::Action	AI::Play()
{
  Graph		mygraph(this->map);
  Graph::node	*mypos;

  this->objectif = NULL;
  this->posi.X = me->getPosition().X;
  this->posi.Y = me->getPosition().Z;
  this->posi.X = (int)(posi.X / BLOCK_SIZE);
  this->posi.Y = (int)(posi.Y / BLOCK_SIZE);
  mygraph.generate();
  graph = mygraph.getGraph();
  mypos = graph[posi.Y * length + posi.X];
  if (goal == NULL && me->canPutBomb())
    canPutBomb(mypos, 0);
  if (objectif != NULL && me->canPutBomb())
    {
      goal = objectif;
      return (Action::ACTION);
    }
  if (goal == NULL && mypos->links.size() > 0)
    {
      return (FindNewGoal(mypos));
    }
  if (goal != NULL)
    return (goToGoal(mypos, goal));
  return (Action::NONE);
}

Action::Action	AI::getDir(Graph::node *nod)
{
  if (posi.X == nod->coord.X && posi.Y == nod->coord.Y - 1)
    return (Action::UP);
  if (posi.X == nod->coord.X && posi.Y == nod->coord.Y + 1)
    return (Action::DOWN);
  if (posi.X == nod->coord.X - 1 && posi.Y == nod->coord.Y)
    return (Action::RIGHT);
  if (posi.X == nod->coord.X + 1 && posi.Y == nod->coord.Y)
    return (Action::LEFT);
  return (Action::NONE);
}

Action::Action	AI::goToGoal(Graph::node *mypos, Graph::node *coord)
{
  Graph::node	*tmp;
  int		place = -1;
  int		i = 0;
  int		min = mypos->distance;

  if (mypos->coord.X == coord->coord.X && mypos->coord.Y == coord->coord.Y)
    {
      goal = NULL;
      return (FindNewGoal(mypos));
    }
  calculateDistances(coord, 0);
  for (std::vector<Graph::node *>::iterator it =
	 graph[mypos->coord.X + (length * mypos->coord.Y)]->links.begin();
       it != graph[mypos->coord.X + (length * mypos->coord.Y)]->links.end(); it++)
    {
      tmp = *it;
      if (tmp->distance < min)
	{
	  min = tmp->distance;
	  objectif = *it;
	}
      ++i;
    }
  if (objectif == NULL || isBlocked(mypos) == true)
    return (Action::NONE);
  else
    return (getDir(objectif));
}

bool		AI::isBlocked(Graph::node *block)
{
  char		i = 0;

  if (block->coord.X - 1 >= 0 &&
      map[block->coord.X - 1][block->coord.Y].getBlockType() ==
      BlockType::EMPTY)
    ++i;
  if (block->coord.X + 1 < length &&
      map[block->coord.X + 1][block->coord.Y].getBlockType() ==
      BlockType::EMPTY)
    ++i;
  if (block->coord.Y - 1 >= 0 &&
      map[block->coord.X][block->coord.Y - 1].getBlockType() ==
      BlockType::EMPTY)
    ++i;
  if (block->coord.Y + 1 < width &&
      map[block->coord.X][block->coord.Y + 1].getBlockType() ==
      BlockType::EMPTY)
    ++i;
  if (i > 1)
    return (false);
  return (false);
}

void		AI::calculateDistances(Graph::node *position, int dist)
{
  if (position->distance < dist)
    return;
  position->distance = dist;
  if (dist < 7)
    {
      for (std::vector<Graph::node *>::iterator it =
	     graph[position->coord.X + (position->coord.Y * length)]->links.begin();
	   it != graph[position->coord.X + (position->coord.Y * length)]->links.end(); ++it)
	{
	  calculateDistances(*it, dist + 1);
	}
    }
}

bool		AI::canPutBomb(Graph::node *block, int distance)
{
  if (block->distance != BIG_DIST)
    return (false);
  if (block->distance > distance)
    block->distance = distance;
  if (objectif != NULL && objectif->distance <= block->distance)
    return (false);
  if ((block->coord.X != posi.X &&
       block->coord.Y != posi.Y))
    {
      objectif = block;
      return (true);
    }
  else
    {
      for (std::vector<Graph::node *>::iterator it =
      	     graph[block->coord.X + block->coord.Y * length]->links.begin();
      	   it != graph[block->coord.X + block->coord.Y * length]->links.end(); ++it)
      	{
      	  canPutBomb(*it, block->distance + 1);
      	}
    }
  return (false);
}
