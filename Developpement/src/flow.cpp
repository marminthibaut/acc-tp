/*
 * flow.cpp
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#include "includes/flow.h"
#include <sstream>

void
updateArc(AbstractGraph& g, vertex_t src, vertex_t dest, int k)
{

  arc_t arc, arc_inverse;
  arc.vertex_src = src;
  arc.vertex_dest = dest;
  arc.weight = 0;

  arc.weight = g.getWeight(arc.vertex_src, arc.vertex_dest) - k;

  if (arc.weight <= 0)
    g.rmArc(arc);
  else
    g.updateArc(arc);

  arc_inverse.vertex_src = arc.vertex_dest;
  arc_inverse.vertex_dest = arc.vertex_src;
  arc_inverse.weight = g.getWeight(arc.vertex_dest, arc.vertex_src);

  if (arc_inverse.weight >= 0)
    {
      arc_inverse.weight += k;
      g.updateArc(arc_inverse);
    }
  else
    {
      arc_inverse.weight = k;
      g.addArc(arc_inverse);
    }

}

void
updateResidualNetwork(AbstractGraph& g, path_t path, uint k)
{
  path_t::iterator it = path.begin();
  vertex_t src;
  vertex_t dest = *it;

  while (++it != path.end())
    {
      src = dest;
      dest = *it;

      updateArc(g, src, dest, k);
    }
}

string
flowToString(AbstractGraph& graph, AbstractGraph& residualNetwork)
{
  stringstream s;
  weight_t flow;

  for (vertex_t v = 0; v < graph.getNbrVertices(); ++v)
    {
      s << v << " : ";

      list<neighbor_t>::iterator it;
      for (it = graph.getNeighbors(v).begin();
          it != graph.getNeighbors(v).end(); it++)
        {
          flow = residualNetwork.getWeight(it->vertex, v);
          if(flow < 0)
            flow = 0;
          s << it->vertex << "(" << flow << "/" << it->weight << ")" << ", ";
        }

      s << endl;
    }
  return s.str();
}
