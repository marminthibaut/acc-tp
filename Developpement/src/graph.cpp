/*
 * graph.cpp
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#include "includes/graph.h"
#include <sstream>
#include <iostream>

bool
operator==(const neighbor_t& n1, const neighbor_t& n2)
{
  return n1.vertex == n2.vertex;
}

AbstractGraph::AbstractGraph()
{
}

AbstractGraph::~AbstractGraph()
{
}

string
AbstractGraph::toString() const
{
  stringstream s;

  for (vertex_t v = 0; v < this->getNbrVertices(); ++v)
    {
      s << v << " : ";

      list<neighbor_t>::iterator it;
      for (it = this->getNeighbors(v).begin();
          it != this->getNeighbors(v).end(); it++)
        {
          s << it->vertex << "(" << it->weight << ")" << ", ";
        }

      s << endl;
    }
  return s.str();
}

