/*
 * MatrixGraph.cpp
 *
 *  Created on: 9 déc. 2011
 *      Author: clement
 */

#include "includes/MatrixGraph.h"

MatrixGraph::MatrixGraph(uint nbr_vertices)
{
  this->_construct(nbr_vertices);
}

MatrixGraph::MatrixGraph(const AbstractGraph& graph)
{
  this->_construct(graph);
}

MatrixGraph::MatrixGraph(const MatrixGraph& graph)
{
  this->_construct(graph);
}


MatrixGraph &
MatrixGraph::operator=(const AbstractGraph& graph)
{
  if(this != &graph)
    {
      this->_clear();
      this->_construct(graph);
    }
  return *this;
}

MatrixGraph &
MatrixGraph::operator=(const MatrixGraph& graph)
{
  if(this != &graph)
     {
       this->_clear();
       this->_construct(graph);
     }
  return *this;
}

MatrixGraph::~MatrixGraph()
{
  this->_clear();
}

//*****************************************************************************
//      METHODS
//*****************************************************************************

bool
MatrixGraph::addArc(const arc_t &arc)
{
  if (arc.vertex_src >= this->getNbrVertices()
      || arc.vertex_dest >= this->getNbrVertices())
    return false;

  this->matrix[arc.vertex_src][arc.vertex_dest] = arc.weight;

  return true;
}

bool
MatrixGraph::addArc(vertex_t src, vertex_t dest, weight_t w)
{
  if (src >= this->getNbrVertices()
      || dest >= this->getNbrVertices())
    return false;

  this->matrix[src][dest] = w;

  return true;
}

void
MatrixGraph::rmArc(const arc_t &arc)
{
  this->matrix[arc.vertex_src][arc.vertex_dest] = -1;
}

void
MatrixGraph::rmArc(vertex_t src, vertex_t dest)
{
  this->matrix[src][dest] = -1;
}

void
MatrixGraph::updateArc(const arc_t &arc)
{
  this->matrix[arc.vertex_src][arc.vertex_dest] = arc.weight;
}

weight_t
MatrixGraph::increaseWeight(vertex_t src, vertex_t dest, weight_t w)
{
  this->matrix[src][dest] += w;
  return this->matrix[src][dest];
}

//************************************************************************************************
//      ACCESSOR METHODS
//************************************************************************************************

uint
MatrixGraph::getNbrVertices() const
{
  return this->nbr_vertices;
}

list<neighbor_t>
MatrixGraph::getSuccessors(vertex_t vertex) const
{
  list<neighbor_t> successors;
  neighbor_t neighbor;

  for(int i = 0; i < this->nbr_vertices; ++i)
    if(this->matrix[vertex][i] >= 0)
      {
        neighbor.vertex = i;
        neighbor.weight = this->matrix[vertex][i];
        successors.push_back(neighbor);
      }

  return successors;
}

list<neighbor_t>
MatrixGraph::getPredecessors(vertex_t vertex) const
{
  list<neighbor_t> predecessors;
  neighbor_t neighbor;

  for(int i = 0; i < this->nbr_vertices; ++i)
    if(this->matrix[i][vertex] >= 0)
      {
        neighbor.vertex = i;
        neighbor.weight = this->matrix[i][vertex];
        predecessors.push_back(neighbor);
      }

  return predecessors;
}

/**
 * @return le poids de l'arc src vers dest ou -1 si l'arc n'existe pas
 */
weight_t
MatrixGraph::getWeight(vertex_t src, vertex_t dest) const
{
  return this->matrix[src][dest];
}


//************************************************************************************************
//      PROTECTED METHODS
//************************************************************************************************

void
MatrixGraph::_clear()
{
  for(int i = 0; i < this->nbr_vertices; ++i)
    delete[] this->matrix[i];

  delete[] this->matrix;
}

void
MatrixGraph::_construct(int nbr_vertices)
{
  this->nbr_vertices = nbr_vertices;

  this->matrix = new weight_t*[nbr_vertices];

  for (int i = 0; i < this->nbr_vertices; ++i)
    {
      this->matrix[i] = new weight_t[this->nbr_vertices];
      for (int j = 0; j < this->nbr_vertices; ++j)
        this->matrix[i][j] = -1;
    }
}

void
MatrixGraph::_construct(const AbstractGraph& graph)
{
  this->_construct(graph.getNbrVertices());

  list<neighbor_t> successors;
  list<neighbor_t>::iterator it;
  for (vertex_t v = 0; v < this->getNbrVertices(); ++v)
    {
      successors = graph.getSuccessors(v);
      for(it = successors.begin(); it != successors.end(); it++)
        this->matrix[v][it->vertex] = it->weight;
    }
}




