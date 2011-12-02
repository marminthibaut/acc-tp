/*
 * VertexListGraph.cpp
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#include "includes/VertexListGraph.h"

#include <iostream>

VertexListGraph::VertexListGraph(uint nbr_vertices)
{
  vertex_list = new list<neighbor_t> [nbr_vertices];
  this->nbr_vertices = nbr_vertices;
}

VertexListGraph::~VertexListGraph()
{
  delete[] vertex_list;
}

//*****************************************************************************
//      METHODS
//*****************************************************************************

bool
VertexListGraph::addArc(const arc_t &arc)
{
  if (arc.vertex_src > this->getNbrVertices()
      || arc.vertex_dest > this->getNbrVertices())
    return false;

  neighbor_t neighbor;
  neighbor.vertex = arc.vertex_dest;
  neighbor.weight = arc.weight;

  vertex_list[arc.vertex_src].push_back(neighbor);
  return true;
}

void
VertexListGraph::rmArc(const arc_t &arc)
{
  neighbor_t neighbor;
  neighbor.vertex = arc.vertex_dest;
  neighbor.weight = arc.weight;

  vertex_list[arc.vertex_src].remove(neighbor);
}

void
VertexListGraph::updateArc(const arc_t &arc)
{
  list<neighbor_t> &neighbors = this->vertex_list[arc.vertex_src];
  list<neighbor_t>::iterator it;

  cout << "********" << endl;
  for (it = neighbors.begin(); it != neighbors.end(); it++)
    if (it->vertex == arc.vertex_dest)
        it->weight = arc.weight;

}

//************************************************************************************************
//      ACCESSOR METHODS
//************************************************************************************************

uint
VertexListGraph::getNbrVertices() const
{
  return this->nbr_vertices;
}

list<neighbor_t>&
VertexListGraph::getNeighbors(vertex_t vertex_src) const
{
  return this->vertex_list[vertex_src];
}

/**
 * @return le poids de l'arc src vers dest ou -1 si l'arc n'existe pas
 */
weight_t
VertexListGraph::getWeight(vertex_t src, vertex_t dest) const
{
  list<neighbor_t> &neighbors = this->getNeighbors(src);
  list<neighbor_t>::iterator it;

  for (it = neighbors.begin(); it != neighbors.end(); it++)
    if (it->vertex == dest)
      return it->weight;

  return -1;
}

