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
  cout << "AbstractGraph::toString" << endl;

  stringstream s;
  list<neighbor_t>::iterator it;
  list<neighbor_t> successors;

  for (vertex_t v = 0; v < this->getNbrVertices(); ++v)
    {
      s << v << " : ";
      cout << v << " : " << endl;
      successors = this->getSuccessors(v);

      for (it = successors.begin(); it != successors.end(); it++)
        {
          cout << "--" << it->vertex << endl;
          s << it->vertex << "(" << it->weight << ")" << ", ";
        }

      cout << "__" << endl;
      s << endl;
    }

  cout << "end AbstractGraph::toString" << endl;


  return s.str();
}

