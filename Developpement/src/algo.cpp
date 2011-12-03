/*
 * algo.cpp
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#include "includes/algo.h"

path_t
leastFirst(AbstractGraph &g, vertex_t start, vertex_t end)
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

  already_view[0] = true;

  //***************************************************************************
  // Parcours
  file.push_back(start);
  vertex_t u, v;
  list<neighbor_t> neighbors;
  list<neighbor_t>::iterator it;
  while (file.size() != 0)
    {
      u = file.front();
      file.pop_front();

      neighbors = g.getNeighbors(u);
      for (it = neighbors.begin(); it != neighbors.end(); it++)
        {
          v = it->vertex;
          if (!already_view[v])
            {
              file.push_back(v);
              parent[v] = u;
              already_view[v] = true;
            }
        }
    }

  //***************************************************************************
  // Recupération du path
  path.push_front(end);
  while (parent[path.front()] > -1)
    path.push_front(parent[path.front()]);

  if(path.front() != start)
    path.clear();

  return path;
}

path_t
leastArcsPath(AbstractGraph &g, vertex_t start, vertex_t end)
{
  return leastFirst(g, start, end);
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

  for(; it != path.end(); it++)
    {
      src = dest;
      dest = *it;
      current = g.getWeight(src, dest);
      if(current >= 0 && current < min)
        min = current;
    }

  return min;

}

