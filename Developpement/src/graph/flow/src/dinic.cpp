#include <list>

#include "../flow.h"

LevelGraph
generateLevelGraph(const AbstractGraph& residual_network, vertex_t src, vertex_t dest)
{
  bool already_view[residual_network.getNbrVertices()];
  list<vertex_t> file, next_level;
  list<neighbor_t> parent[residual_network.getNbrVertices()];
  int level[residual_network.getNbrVertices()];
  bool find_dest = false;

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

      for (it = parent[u].begin(); it != parent[u].end(); it++)
        {
          if (!already_view[it->vertex])
            {
              file.push_back(it->vertex);
              level_graph.addVertexToLevel(it->vertex, level[it->vertex]);
            }

          already_view[it->vertex] = true;

          arc.vertex_src = it->vertex;
          arc.weight = it->weight;
          level_graph.addArc(arc);
        }
    }

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

  do
    {
      v = dest;
      weight = -1;
      path.clear();
      path.push_front(v);

      while (v != src)
        {
          u = level_graph.getPredecessors(v).front().vertex;

          if (v == dest)
            weight = level_graph.getWeight(u, v);
          else
            weight = min(level_graph.getWeight(u, v), weight);

          path.push_front(u);
          v = u;
        }

      path_t::iterator it = path.begin();
      v = *it;

      while (++it != path.end())
        {
          u = v;
          v = *it;

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
                      level_graph.rmArc(*it_vertex, it_neighbor->vertex);
                    }
                }
            }

        }
    }
  while ((level_graph.getPredecessors(dest)).size() != 0);

  return flow;
}


AdjacencyListGraph
dinic(const AbstractGraph& graph, vertex_t src, vertex_t dest)
{
  //****************************************
  // residual network
  AdjacencyListGraph residual_network(graph);
  AdjacencyListGraph flow(0);
  LevelGraph level_graph = generateLevelGraph(residual_network, src, dest);

  while (level_graph.getLevel(0).size() != 0)
    {
      flow = blockingFlow(level_graph, src, dest);
      updateResidualNetwork(residual_network, flow);
      level_graph = generateLevelGraph(residual_network, src, dest);
    }

    return residual_network;
}

