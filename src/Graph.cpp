#include "Graph.hh"

Graph::Graph(std::vector<std::vector<Case> > &_map) : map(_map)
{
  width = map[0].size();
  length = map.size();
  generate();
}

Graph::~Graph()
{
  destroy();
}

void			Graph::destroy()
{
  graph.clear();
}

void			Graph::addLinks(unsigned int x, unsigned int y)
{
  graph[length * y + x]->links.clear();
  if (x - 1 >= 0 && map[x - 1][y].getBlockType() == BlockType::EMPTY)
    graph[length * y + x]->links.push_back(graph[length * y + x - 1]);
  if (x + 1 < map.size() && map[x + 1][y].getBlockType() == BlockType::EMPTY)
    graph[length * y + x]->links.push_back(graph[length * y + x + 1]);
  if (y - 1 >= 0 && map[x][y - 1].getBlockType() == BlockType::EMPTY)
    graph[length * y + x]->links.push_back(graph[length * (y - 1) + x]);
  if (y + 1 < map[0].size() && map[x][y + 1].getBlockType() == BlockType::EMPTY)
    graph[length * y + x]->links.push_back(graph[length * (y + 1) + x]);
}

void			Graph::generate()
{
  unsigned int		x, y;
  Graph::node		*tmp;

  for (y = 0; y < map[0].size(); y++)
    {
      for (x = 0; x < map.size(); x++)
  	graph.push_back(new Graph::node(x, y));
    }
  for (y = 0; y < map[0].size(); y++)
    {
      for (x = 0; x < map.size(); x++)
	{
	  if (map[x][y].getBlockType() == BlockType::EMPTY ||
	      map[x][y].getBlockType() == BlockType::BOMB)
	    {
	      if (map[x][y].getDangerous() > 0)
		graph[length * y + x]->dangerous = true;
	      addLinks(x, y);
	    }
	}
    }
}

std::vector<Graph::node *>	Graph::getGraph()
{
  return (graph);
}
