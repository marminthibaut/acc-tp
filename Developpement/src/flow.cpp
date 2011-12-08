/*
 * flow.cpp
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#include "includes/flow.h"
#include "includes/algo.h"
#include "includes/AdjacencyListGraph.h"
#include "includes/utils.h"
#include "includes/LevelGraph.h"
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

string
flowToString(const AbstractGraph& graph, const AbstractGraph& residualNetwork)
{
  stringstream s;
  weight_t flow;

  for (vertex_t v = 0; v < graph.getNbrVertices(); ++v)
    {
      s << v << " : ";

      list<neighbor_t>::iterator it;
      for (it = graph.getSuccessors(v).begin();
          it != graph.getSuccessors(v).end(); it++)
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
edmondsKarp(const AbstractGraph& graph, vertex_t src, vertex_t dest)
{
  //****************************************
  // residual network
  AdjacencyListGraph residual_network(graph);

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

LevelGraph
generateLevelGraph(const AbstractGraph& residual_network, vertex_t src, vertex_t dest)
{
  bool already_view[residual_network.getNbrVertices()];
  list<vertex_t> file, next_level;
  list<neighbor_t> parent[residual_network.getNbrVertices()];
  int level[residual_network.getNbrVertices()];
  bool find_dest = false;

  cout << "calcul level graph" << endl;

  //***************************************************************************
  // initialisation
  for (uint i = 0; i < residual_network.getNbrVertices(); ++i)
    {
      already_view[i] = false;
      level[i] = -1;
    }

  next_level.push_back(src);

  //***************************************************************************
  // Parcours (breadth first)
  vertex_t u, v;
  uint current_level = 0;

  list<neighbor_t> neighbors;
  neighbor_t neighbor;
  list<neighbor_t>::iterator it;
  list<vertex_t>::iterator it_vertex;

  while (!find_dest && next_level.size() != 0)
    {
      file.clear();
      for (it_vertex = next_level.begin(); it_vertex != next_level.end();
          it_vertex++)
        {
          if (!already_view[*it_vertex])
            {
              file.push_back(*it_vertex);
              level[*it_vertex] = current_level;
            }

          already_view[*it_vertex] = true;

        }
      next_level.clear();
      ++current_level;

      while (file.size() != 0)
        {
          u = file.front();
          file.pop_front();

          neighbors = residual_network.getSuccessors(u);
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
  level[dest] = current_level;

  //***************************************************************************
  // Recupération du level_network

  LevelGraph level_graph(residual_network.getNbrVertices(), level[dest] + 1);

  for (uint i = 0; i < residual_network.getNbrVertices(); ++i)
    already_view[i] = false;

  file.clear();
  file.push_back(dest);
  level_graph.addVertexToLevel(dest, level[dest]);

  already_view[dest] = true;
  arc_t arc;

  while (file.size() != 0)
    {
      u = file.front();
      file.pop_front();
      arc.vertex_dest = u;

      cout << u << " ( ";

      for (it = parent[u].begin(); it != parent[u].end(); it++)
        {
          if (!already_view[it->vertex])
            {
              file.push_back(it->vertex);
              level_graph.addVertexToLevel(it->vertex, level[it->vertex]);
            }

          cout << it->vertex << " - ";

          already_view[it->vertex] = true;

          arc.vertex_src = it->vertex;
          arc.weight = it->weight;
          level_graph.addArc(arc);
        }
      cout << " ) " << endl;
    }
  cout << endl;

  cout << "end level graph" << endl;


  return level_graph;
}

AdjacencyListGraph
blockingFlow(LevelGraph& level_graph, vertex_t src, vertex_t dest)
{
  AdjacencyListGraph flow(level_graph.getNbrVertices());
  vertex_t v, u;
  weight_t weight;
  int val;
  path_t path;

  cout << "********************" << endl;
  cout << "création du flot bloquant" << endl;

  do
    {
      v = dest;
      weight = -1;
      path.clear();
      path.push_front(v);

      cout << "parcours du graphe de couche" << endl;
      while (v != src)
        {
          cout << v << " - ";
          u = level_graph.getPredecessors(v).front().vertex;

          if (v == dest)
            weight = level_graph.getWeight(u, v);
          else
            weight = min(level_graph.getWeight(u, v), weight);

          path.push_front(u);
          v = u;
        }
      cout << v << endl;
      cout << "weight : " << weight << endl;

      path_t::iterator it = path.begin();
      v = *it;

      while (++it != path.end())
        {
          u = v;
          v = *it;

          cout << u << " <-> " << v << endl;
          if (flow.getWeight(u, v) == -1)
            flow.addArc(u, v, weight);
          else
            flow.increaseWeight(u, v, weight);

          val = level_graph.increaseWeight(u, v, -weight);
          if (val == 0)
            {
              level_graph.rmArc(u, v);
            }
        }

      //On supprime les arcs qui n'ont pas de prédecesseur
      list<vertex_t> file;
      list<vertex_t>::iterator it_vertex;
      list<neighbor_t> neighbors;
      list<neighbor_t>::iterator it_neighbor;
      file.push_back(dest);

      cout << "mise a jour du graphe de couche" << endl;

      for (uint level = 1; level < level_graph.getNbrLevels(); ++level)
        {
          file = level_graph.getLevel(level);
          for (it_vertex = file.begin(); it_vertex != file.end(); it_vertex++)
            {
              if (level_graph.getPredecessors(*it_vertex).size() == 0)
                {
                  neighbors = level_graph.getSuccessors(*it_vertex);
                  for (it_neighbor = neighbors.begin();
                      it_neighbor != neighbors.end(); it_neighbor++)
                    {
                      level_graph.rmVertexToLevel(*it_vertex, level);
                      cout << "rm " << *it_vertex << " - "
                          << it_neighbor->vertex << endl;
                      level_graph.rmArc(*it_vertex, it_neighbor->vertex);
                    }
                }
            }

        }

    }
  while ((level_graph.getPredecessors(dest)).size() != 0);

  return flow;
}


void
dinic(const AbstractGraph& graph, vertex_t src, vertex_t dest)
{
  //****************************************
  // residual network
  AdjacencyListGraph residual_network(graph);
  AdjacencyListGraph flow(0);

  cout << "Dinic" << endl;

  LevelGraph level_graph = generateLevelGraph(residual_network, src, dest);

  while (level_graph.getLevel(0).size() != 0)
    {
      //****************************************
      // level graph printing
      cout << "***" << endl;
      cout << level_graph.toString() << endl;

      //****************************************
      // mise à jour du residual network
      flow = blockingFlow(level_graph, src, dest);

      updateResidualNetwork(residual_network, flow);
      cout << "//****************************************" << endl
          << "// Residual network" << endl;
      cout << residual_network.toString() << endl;

      cout << "//****************************************" << endl
          << "// nouveau flot" << endl;
      cout << flowToString(graph, residual_network) << endl;

      level_graph = generateLevelGraph(residual_network, src, dest);


    }

}

