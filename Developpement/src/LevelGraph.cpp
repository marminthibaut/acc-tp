/*
 * LevelGraph.cpp
 *
 *  Created on: 8 déc. 2011
 *      Author: clement
 */

#include "includes/LevelGraph.h"
#include <sstream>
#include <iostream>

LevelGraph::LevelGraph(uint nbr_vertices, uint nbr_level) :
    AdjacencyListGraph(nbr_vertices), nbr_level(nbr_level)
{
  this->levels = new list<vertex_t> [nbr_level];
}

LevelGraph::~LevelGraph()
{
  delete[] this->levels;
}

uint
LevelGraph::getNbrlevels()
{
  return this->nbr_level;
}

list<vertex_t>
LevelGraph::getLevel(uint level)
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
LevelGraph::toString()
{
  cout << "levelgraph toString" << endl;
  stringstream s;
  s << AdjacencyListGraph::toString();
  cout << "???" << endl;
  list<vertex_t>::iterator it;
  list<vertex_t> vertices;

  s << "-------------------------------" << endl;
  cout << "-------------------------------" << endl;
  for(uint i = 0; i < this->getNbrlevels(); ++i)
    {
      s << "Level " << i << " : " ;
      cout << "Level " << i << " : ";
      vertices = this->getLevel(i);
      for(it = vertices.begin(); it != vertices.end(); it++)
        s << *it << ", ";

      s << endl;
    }

  cout << "end levelgraph toString" << endl;

  return s.str();

}
