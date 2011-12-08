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
  LevelGraph(const LevelGraph& level_graph);

  virtual
  ~LevelGraph();

  virtual uint
  getNbrLevels() const;

  virtual list<vertex_t>
  getLevel(uint level) const;

  virtual void
  addVertexToLevel(vertex_t v, uint level);

  virtual void
  rmVertexToLevel(vertex_t v, uint level);

  virtual string
  toString() const;

private:
  list<vertex_t> *levels;
  uint nbr_level;
};

#endif /* LEVELGRAPH_H_ */
