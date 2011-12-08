/*
 * LevelGraph.h
 *
 *  Created on: 8 déc. 2011
 *      Author: clement
 */

#ifndef LEVELGRAPH_H_
#define LEVELGRAPH_H_

#include "AdjacencyListGraph.h"

class LevelGraph : public AdjacencyListGraph
{
public:
  LevelGraph(uint nbr_vertices, uint nbr_level);

  virtual
  ~LevelGraph();

  virtual uint
  getNbrlevels();

  virtual list<vertex_t>
  getLevel(uint level);

  virtual void
  addVertexToLevel(vertex_t v, uint level);

  virtual void
  rmVertexToLevel(vertex_t v, uint level);

  virtual string
  toString();

private:
  list<vertex_t> *levels;
  uint nbr_level;
};

#endif /* LEVELGRAPH_H_ */
