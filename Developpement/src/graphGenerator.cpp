/*
 * graphGenerator.cpp
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#include "includes/graphGenerator.h"
#include <stdlib.h>

void
graphGenerator(VertexListGraph& graph, uint min_weight, uint max_weight)
{
  srand(time(NULL));

  int nbr_vertex_max = ((graph.getNbrVertices() * (graph.getNbrVertices() - 1))
      / 2) - graph.getNbrVertices() + 1;

  uint nbr = rand() % nbr_vertex_max + 1;
  while(nbr-- > 0)
    {
      arc_t arc;
      arc.vertex_src = rand() % graph.getNbrVertices();
      arc.vertex_dest = rand() % graph.getNbrVertices();
      arc.weight = (rand() % (max_weight)); //@FIXME min_weight

      if(arc.vertex_src != arc.vertex_dest)
          if( graph.getWeight(arc.vertex_src, arc.vertex_dest) < 0 )
            graph.addArc(arc);

    }
}

void
generateChemin(VertexListGraph& graph)
{
  arc_t arc;
  for (vertex_t v = 1; v < graph.getNbrVertices(); ++v)
    {
      arc.vertex_src = v - 1;
      arc.vertex_dest = v;
      arc.weight = 1;
      graph.addArc(arc);
    }
}
