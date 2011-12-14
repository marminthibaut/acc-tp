
#include <list>

#include "../flow.h"

AdjacencyListGraph
edmondsKarp(const AbstractGraph& graph, vertex_t src, vertex_t dest)
{
  AdjacencyListGraph residual_network(graph);
  path_t path;
  path_t::iterator it;
  int k;

  while ((path = leastArcsPath(residual_network, src, dest)).size() != 0)
    {
      k = lightestArc(residual_network, path);
      updateResidualNetwork(residual_network, path, k);
    }

    return residual_network;

}

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

void
updateResidualNetwork(AbstractGraph& graph, AbstractGraph& flow)
{
  list<neighbor_t>::iterator it;
  list<neighbor_t> successors;

  for (vertex_t v = 0; v < flow.getNbrVertices(); ++v)
    {
      successors = flow.getSuccessors(v);
      for (it = successors.begin(); it != successors.end(); it++)
        updateArc(graph, v, it->vertex, it->weight);
    }

}
