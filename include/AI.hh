#ifndef AI_HH_
# define AI_HH_

# include <irrlicht.h>
# include "BlockType.hh"
# include "Item.hh"
# include "Entity.hh"
# include "Map.hh"
# include "Graph.hh"
# include "IAI.hh"

class AI : public IAI
{
public:
  AI(std::vector<std::vector<Case> > &_map,
     std::vector<Entity *> &_entityList,
     Entity *);
  Action::Action	Play();

private:
  std::vector<std::vector<Case> >	&map;
  std::vector<Graph::node *>		graph;
  std::vector<Entity *>			&entityList;
  Graph::node				*objectif;
  Graph::node				*goal;
  Graph::pos				posi;
  int					width;
  int					length;
  Entity				*me;

  Action::Action	FindNewGoal(Graph::node *mypos);
  bool			canPutBomb(Graph::node *block, int distance);
  Action::Action	goToGoal(Graph::node *, Graph::node *);
  Action::Action	getDir(Graph::node *nod);
  void			calculateDistances(Graph::node *position, int dist);
  bool			isBlocked(Graph::node *position);
  void			generateGraph();
};

#endif // !AI_HH_
