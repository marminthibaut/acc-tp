/*
 * VertexListGraph.cpp
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#include "includes/AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(uint nbr_vertices) :
    nbr_vertices(nbr_vertices)
{
  this->successors = new list<neighbor_t> [nbr_vertices];
  this->predecessors = new list<neighbor_t> [nbr_vertices];
}

AdjacencyListGraph::AdjacencyListGraph(const AbstractGraph& graph)
{
  list<neighbor_t> neighbors;
  this->nbr_vertices = graph.getNbrVertices();

  this->successors = new list<neighbor_t> [this->nbr_vertices];
  this->predecessors = new list<neighbor_t> [this->nbr_vertices];

  for (vertex_t v = 0; v < this->getNbrVertices(); ++v)
    {
      neighbors = graph.getSuccessors(v);
      this->successors[v].splice(this->successors[v].begin(), neighbors);
      neighbors = graph.getPredecessors(v);
      this->predecessors[v].splice(this->predecessors[v].begin(), neighbors);
    }

}

AdjacencyListGraph::~AdjacencyListGraph()
{
  delete[] successors;
  delete[] predecessors;
}

//*****************************************************************************
//      METHODS
//*****************************************************************************

bool
AdjacencyListGraph::addArc(const arc_t &arc)
{
  if (arc.vertex_src > this->getNbrVertices()
      || arc.vertex_dest > this->getNbrVertices())
    return false;

  neighbor_t neighbor;
  neighbor.vertex = arc.vertex_dest;
  neighbor.weight = arc.weight;

  this->successors[arc.vertex_src].push_back(neighbor);

  neighbor.vertex = arc.vertex_src;
  this->predecessors[arc.vertex_dest].push_back(neighbor);

  return true;
}

bool
AdjacencyListGraph::addArc(vertex_t src, vertex_t dest, weight_t w)
{
  arc_t arc;
  arc.vertex_src = src;
  arc.vertex_dest = dest;
  arc.weight = w;
  return this->addArc(arc);
}

void
AdjacencyListGraph::rmArc(const arc_t &arc)
{
  neighbor_t neighbor;
  neighbor.vertex = arc.vertex_dest;
  neighbor.weight = arc.weight;

  this->successors[arc.vertex_src].remove(neighbor);

  neighbor.vertex = arc.vertex_src;
  this->predecessors[arc.vertex_dest].remove(neighbor);
}

void
AdjacencyListGraph::rmArc(vertex_t src, vertex_t dest)
{
  list<neighbor_t>::iterator it;

  for (it = this->successors[src].begin(); it != this->successors[src].end();
      it++)
    {
      if (it->vertex == dest)
        {
          this->successors[src].erase(it);
          break;
        }
    }

  for (it = this->predecessors[dest].begin();
      it != this->predecessors[dest].end(); it++)
    {
      if (it->vertex == src)
        {
          this->successors[dest].erase(it);
          break;
        }
    }
}

void
AdjacencyListGraph::updateArc(const arc_t &arc)
{
  list<neighbor_t> &succ = this->successors[arc.vertex_src];
  list<neighbor_t> &pred = this->predecessors[arc.vertex_dest];
  list<neighbor_t>::iterator it;

  for (it = succ.begin(); it != succ.end(); it++)
    if (it->vertex == arc.vertex_dest)
      it->weight = arc.weight;

  for (it = pred.begin(); it != pred.end(); it++)
    if (it->vertex == arc.vertex_src)
      it->weight = arc.weight;

}

weight_t
AdjacencyListGraph::increaseWeight(vertex_t src, vertex_t dest, weight_t w)
{
  list<neighbor_t> &succ = this->successors[src];
  list<neighbor_t> &pred = this->predecessors[dest];
  list<neighbor_t>::iterator it;

  for (it = succ.begin(); it != succ.end(); it++)
    if (it->vertex == dest)
      {
        it->weight += w;
        break;
      }

  for (it = pred.begin(); it != pred.end(); it++)
    if (it->vertex == src)
      {
        it->weight += w;
        return it->weight;
      }

  return 0;
}

//************************************************************************************************
//      ACCESSOR METHODS
//************************************************************************************************

uint
AdjacencyListGraph::getNbrVertices() const
{
  return this->nbr_vertices;
}

list<neighbor_t>
AdjacencyListGraph::getSuccessors(vertex_t vertex) const
{
  return this->successors[vertex];
}

list<neighbor_t>
AdjacencyListGraph::getPredecessors(vertex_t vertex) const
{
  return this->predecessors[vertex];
}

/**
 * @return le poids de l'arc src vers dest ou -1 si l'arc n'existe pas
 */
weight_t
AdjacencyListGraph::getWeight(vertex_t src, vertex_t dest) const
{

  list<neighbor_t> neighbors = this->getSuccessors(src);
  list<neighbor_t>::iterator it;

  for (it = neighbors.begin(); it != neighbors.end(); it++)
    if (it->vertex == dest)
      return it->weight;

  return -1;
}

