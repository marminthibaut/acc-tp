#ifndef VERTEXLISTGRAPH_H_
#define VERTEXLISTGRAPH_H_

#include <list>
#include "graph.h"

class VertexListGraph : public AbstractGraph
{

public:
  //************************************************************************************************
  //      CONSTRUCTOR
  //************************************************************************************************

  VertexListGraph(uint nbr_vertices);

  virtual
  ~VertexListGraph();

  virtual bool
  addArc(const arc_t &arc);

  virtual void
  rmArc(const arc_t &arc);

  virtual void
  updateArc(const arc_t &arc);

  virtual uint
  getNbrVertices() const;

  virtual list<neighbor_t>&
  getNeighbors(vertex_t vertex_src) const;

  virtual weight_t
  getWeight(vertex_t src, vertex_t dest) const;

private:
  list<neighbor_t>* vertex_list; //@FIXME  list<neighbor_t*>*
  uint nbr_vertices;
};

#endif /* VERTEXLISTGRAPH_H_ */
