#ifndef GRAPH_HH_
# define GRAPH_HH_

#include <vector>
#include "Map.hh"

# define BIG_DIST	9999

class	Graph
{
public:
  struct		pos {
    unsigned int	X;
    unsigned int	Y;
    pos(unsigned int x = 0,
    	unsigned int y = 0) : X(x), Y(y) {}
  };

  struct		node {
    pos			coord;
    long int		distance;
    bool		dangerous;
    std::vector<node *>	links;
    node(unsigned int _x, unsigned int _y,
	 unsigned int _distance = BIG_DIST, bool _dangerous = false)
      : coord(_x, _y), distance(_distance), dangerous(_dangerous) {}
  };

  Graph(std::vector<std::vector<Case> > &_map);
  ~Graph();
  void				destroy();
  void				generate();
  std::vector<node *>		getGraph();

private:
  std::vector<std::vector<Case> >	&map;
  std::vector<node *>			graph;
  int					width;
  int					length;

  void		addLinks(unsigned int x, unsigned int y);
};

#endif // GRAPH_HH_
