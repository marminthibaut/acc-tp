/*
 * flow.cpp
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#include "includes/flow.h"
#include "includes/algo.h"
#include "includes/VertexListGraph.h"
#include <sstream>
#include <iostream>

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
          if (flow < 0)
            flow = 0;
          s << it->vertex << "(" << flow << "/" << it->weight << ")" << ", ";
        }

      s << endl;
    }
  return s.str();
}

void
edmondsKarp(AbstractGraph& graph, vertex_t src, vertex_t dest)
{
  //****************************************
  // residual network
  VertexListGraph residual_network(graph);

  path_t path;
  while ((path = leastArcsPath(residual_network, src, dest)).size() != 0)
    {
      //****************************************
      //affichage du chemin
      path_t::iterator it;

      cout << "chaine améliorante : " << endl;
      for (it = path.begin(); it != path.end(); it++)
        cout << (*it) << " -> ";

      cout << endl;

      int k = lightestArc(residual_network, path);
      cout << "lightest arc : " << k << endl;

      //****************************************
      // mise à jour du residual network

      updateResidualNetwork(residual_network, path, k);
      cout << "//****************************************" << endl
          << "// Residual network" << endl;
      cout << residual_network.toString() << endl;

      cout << "//****************************************" << endl
          << "// nouveau flot" << endl;
      cout << flowToString(graph, residual_network) << endl;

    }

}

void
levelGraph(AbstractGraph& residual_network, AbstractGraph& level_graph,
    vertex_t src, vertex_t dest)
{
  bool already_view[residual_network.getNbrVertices()];
  list<vertex_t> file, next_level;
  list<neighbor_t> parent[residual_network.getNbrVertices()];

  //***************************************************************************
  // initialisation
  for (uint i = 0; i < residual_network.getNbrVertices(); ++i)
    already_view[i] = false;

  next_level.push_back(src);

  //***************************************************************************
  // Parcours
  vertex_t u, v;
  list<neighbor_t> neighbors;
  neighbor_t neighbor;
  list<neighbor_t>::iterator it;
  list<vertex_t>::iterator it_vertex;
  bool find_dest = false;

  while (!find_dest && next_level.size() != 0)
    {
      file.clear();
      for (it_vertex = next_level.begin(); it_vertex != next_level.end(); it_vertex++)
        {
          if(!already_view[*it_vertex])
            file.push_back(*it_vertex);

          already_view[*it_vertex] = true;

        }
      next_level.clear();

      while (file.size() != 0)
        {
          u = file.front();
          file.pop_front();

          neighbors = residual_network.getNeighbors(u);
          for (it = neighbors.begin(); it != neighbors.end(); it++)
            {
              v = it->vertex;
              if (!already_view[v])
                {
                  next_level.push_back(v);
                  neighbor.vertex = u;
                  neighbor.weight = it->weight;
                  parent[v].push_back(neighbor);
                  if (v == dest)
                    {
                      find_dest = true;
                      break;
                    }
                }
            }
        }
    }

  //***************************************************************************
  // Recupération du level_network

  for (uint i = 0; i < residual_network.getNbrVertices(); ++i)
     already_view[i] = false;

  file.clear();
  file.push_back(dest);
  already_view[dest] = true;
  arc_t arc;


  while( file.size() != 0 )
    {
      u = file.front();
      file.pop_front();
      arc.vertex_dest = u;

      cout << u << " ( ";

      for (it = parent[u].begin(); it != parent[u].end(); it++)
        {
          if(!already_view[it->vertex])
            file.push_back(it->vertex);

          cout << it->vertex <<  " - ";

          already_view[it->vertex] = true;

          arc.vertex_src = it->vertex;
          arc.weight = it->weight;
          level_graph.addArc(arc);
        }
      cout << " ) " << endl;
    }
  cout << endl;
}
