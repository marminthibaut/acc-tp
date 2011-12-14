
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>

#include "../../AdjacencyListGraph.h"
#include "../../LevelGraph.h"

#include "../flow.h"
#include "../../../includes/utils.h"


/**
 * Generate a flow network with the vertex 0 as source and the vertex which has
 * the max value as sink
 */
void
flowNetworkGenerator(AbstractGraph& flow_network, float rate, uint min_weight,
    uint max_weight)
{
  edge e;
  vector<edge> list;
  uint val;

  uint nbr_vertices = flow_network.getNbrVertices();
  uint nbr_arcs_max = (nbr_vertices * (nbr_vertices - 1)) / 2;
  uint nbr_arcs_wanted = nbr_arcs_max * rate;
  uint current_arc = 1;

  flow_network.rmAllArc();

  for (vertex_t u = 0; u < nbr_vertices - 1; ++u)
    {
      //Pour tout u, on crée l'arc u, u+1 afin d'assurer l'existance
      //d'un chemin de la source vers le puit
      flow_network.addArc(u,u+1,randMinMax(min_weight, max_weight));
      ++current_arc;

      for (vertex_t v = u + 2; v < nbr_vertices; ++v)
        {
          e.u = u;
          e.v = v;
          list.push_back(e);
        }
    }

  uint size = list.size();

  while(current_arc <= nbr_arcs_wanted)
    {
      val = rand() % size;
      while(list[val].v == 0)
          val = ++val % size;

      e = list[val];
      if(e.u == 0 || e.v == (nbr_vertices - 1) || rand() % 2 == 1)
        flow_network.addArc(e.u,e.v,randMinMax(min_weight, max_weight));
      else
        flow_network.addArc(e.v,e.u,randMinMax(min_weight, max_weight));

      ++current_arc;
      list[val].v = 0;
    }
}



string
flowToString(const AbstractGraph& graph, const AbstractGraph& residualNetwork)
{
  stringstream s;
  weight_t flow, total_flow;
  list<neighbor_t>::iterator it;
  list<neighbor_t> successors;

  //Calcul de la valeur du flow
  successors = graph.getSuccessors(0);
  total_flow = 0;
  for (it = successors.begin(); it != successors.end(); it++)
    {
      flow = residualNetwork.getWeight(it->vertex, 0);
      if (flow > 0)
        total_flow += flow;
    }

  s << "Flow : " << total_flow << endl;

  for (vertex_t v = 0; v < graph.getNbrVertices(); ++v)
    {
      s << v << " : ";

      successors = graph.getSuccessors(v);
      for (it = successors.begin(); it != successors.end(); it++)
        {
          flow = residualNetwork.getWeight(it->vertex, v);
          if (flow < 0)
            flow = 0;

          s << it->vertex << "(" << flow << "/" << it->weight << ")" << ", ";
        }

      s << endl;
    }
  return s.str();
}


string
flowToDotString(const AbstractGraph& graph, const AbstractGraph& residualNetwork)
{
  stringstream s;
  weight_t flow, total_flow;
  list<neighbor_t>::iterator it;
  list<neighbor_t> successors;

  //Calcul de la valeur du flow
  successors = graph.getSuccessors(0);
  total_flow = 0;
  for (it = successors.begin(); it != successors.end(); it++)
    {
      flow = residualNetwork.getWeight(it->vertex, 0);
      if (flow > 0)
        total_flow += flow;
    }

  s << "digraph { " << "\"" << "Flot total : " << total_flow <<  "\"" << "[shape=box,color=lightblue2]"<< endl;

  for (vertex_t v = 0; v < graph.getNbrVertices(); ++v)
    {
      successors = graph.getSuccessors(v);
      for (it = successors.begin(); it != successors.end(); it++)
        {
          flow = residualNetwork.getWeight(it->vertex, v);
          if (flow < 0)
            flow = 0;

          if(v == 0)
            s << "s";
          else if(v == graph.getNbrVertices() - 1)
            s << "p";
          else
            s << v ;

           s << " -> " << it->vertex << "[label=\"" << flow << "/" << it->weight << "\"]" << endl;
        }

    }
  s << "}" << endl;
  return s.str();
}




