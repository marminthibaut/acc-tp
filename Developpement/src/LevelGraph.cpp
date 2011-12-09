/*
 * LevelGraph.cpp
 *
 *  Created on: 8 déc. 2011
 *      Author: clement
 */

#include "includes/LevelGraph.h"
#include <sstream>

LevelGraph::LevelGraph(uint nbr_vertices, uint nbr_level) :
    AdjacencyListGraph(nbr_vertices), nbr_level(nbr_level)
{
  this->levels = new list<vertex_t> [nbr_level];
}

LevelGraph::LevelGraph(const LevelGraph &level_graph) :
  AdjacencyListGraph(level_graph)
{
  this->_construct(level_graph);
}

LevelGraph &
LevelGraph::operator=(const LevelGraph& level_graph)
{
  if(this != &level_graph)
    {
      AdjacencyListGraph::_clear();
      this->_clear();
      AdjacencyListGraph::_construct(level_graph);
      this->_construct(level_graph);
    }
  return *this;
}

LevelGraph::~LevelGraph()
{
  this->_clear();
}

uint
LevelGraph::getNbrLevels() const
{
  return this->nbr_level;
}

list<vertex_t>
LevelGraph::getLevel(uint level) const
{
  return this->levels[level];
}

void
LevelGraph::addVertexToLevel(vertex_t v, uint level)
{
  this->levels[level].push_back(v);
}

void
LevelGraph::rmVertexToLevel(vertex_t v, uint level)
{
  this->levels[level].remove(v);
}

string
LevelGraph::toString() const
{
  stringstream s;
  s << AdjacencyListGraph::toString();
  list<vertex_t>::iterator it;
  list<vertex_t> vertices;

  s << "-------------------------------" << endl;
  for(uint i = 0; i < this->getNbrLevels(); ++i)
    {
      s << "Level " << i << " : " ;
      vertices = this->getLevel(i);

      for(it = vertices.begin(); it != vertices.end(); it++)
        s << *it << ", ";

      s << endl;
    }

  return s.str();

}


//************************************************************************************************
//      PROTECTED METHODS
//************************************************************************************************

void
LevelGraph::_construct(const LevelGraph &level_graph)
{
  this->nbr_level = level_graph.getNbrLevels();
  this->levels = new list<vertex_t>[this->nbr_level];

  for(uint i = 0; i < this->nbr_level; ++i)
    this->levels[i] = level_graph.getLevel(i);
}

void
LevelGraph::_clear()
{
  delete[] this->levels;
}
