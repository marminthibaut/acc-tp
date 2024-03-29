/*
 * graph.cpp
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#include <sstream>

#include "../graph.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/

bool
operator==(const neighbor_t& n1, const neighbor_t& n2)
{
  return n1.vertex == n2.vertex;
}


path_t
leastArcsPath(AbstractGraph &g, vertex_t start, vertex_t end)
{
  path_t path;
  list<vertex_t> file;

  bool already_view[g.getNbrVertices()];
  int parent[g.getNbrVertices()];

  //***************************************************************************
  // initialisation
  for (vertex_t v = 0; v < g.getNbrVertices(); ++v)
    {
      already_view[v] = false;
      parent[v] = -1;
    }

  already_view[start] = true;

  //***************************************************************************
  // Parcours
  file.push_back(start);
  vertex_t u, v;
  list<neighbor_t> neighbors;
  list<neighbor_t>::iterator it;
  bool find_end = false;

  while (file.size() != 0 && !find_end)
    {
      u = file.front();
      file.pop_front();

      neighbors = g.getSuccessors(u);
      for (it = neighbors.begin(); it != neighbors.end(); it++)
        {
          v = it->vertex;
          if (!already_view[v])
            {
              file.push_back(v);
              parent[v] = u;
              already_view[v] = true;
              if (v == end)
                {
                  find_end = true;
                  break;
                }

            }
        }
    }

  //***************************************************************************
  // Recupération du path
  path.push_front(end);
  while (parent[path.front()] > -1)
    path.push_front(parent[path.front()]);

  if (path.front() != start)
    path.clear();

  return path;
}



weight_t
lightestArc(AbstractGraph& g, path_t path)
{
  weight_t min, current;

  path_t::iterator it = path.begin();
  vertex_t src = *it;
  it++;
  vertex_t dest = *it;
  min = g.getWeight(src, dest);

  for (; it != path.end(); it++)
    {
      src = dest;
      dest = *it;
      current = g.getWeight(src, dest);
      if (current >= 0 && current < min)
        min = current;
    }

  return min;

}


string
pathToString(path_t path, const AbstractGraph& g)
{
  stringstream s;
  path_t::iterator it = path.begin();
   vertex_t src = *it;
   it++;
   vertex_t dest = *it;
   s << src << "--(" << g.getWeight(src, dest) << ")-->" << dest << endl;

   for (; it != path.end(); it++)
     {
       src = dest;
       dest = *it;
       s << " --(" << g.getWeight(src, dest) << ")--> " << dest << endl;
     }

   return s.str();
}

/*******************************************************************************
 * Class AbstractGraph
 ******************************************************************************/

AbstractGraph::AbstractGraph()
{
}

AbstractGraph::~AbstractGraph()
{
}

string
AbstractGraph::toString() const
{
  stringstream s;
  list<neighbor_t>::iterator it;
  list<neighbor_t> successors;

  for (vertex_t v = 0; v < this->getNbrVertices(); ++v)
    {
      s << v << " : ";
      successors = this->getSuccessors(v);

      for (it = successors.begin(); it != successors.end(); it++)
          s << it->vertex << "(" << it->weight << ")" << ", ";

      s << endl;
    }

  return s.str();
}

