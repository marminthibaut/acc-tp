#ifndef VERTEXLISTGRAPH_H_
#define VERTEXLISTGRAPH_H_

#include <list>
#include "graph.h"

class AdjacencyListGraph : public AbstractGraph
{

public:
  //************************************************************************************************
  //      CONSTRUCTOR
  //************************************************************************************************

  AdjacencyListGraph(uint nbr_vertices);

  AdjacencyListGraph(const AbstractGraph& graph);
  AdjacencyListGraph(const AdjacencyListGraph& graph);


  virtual
  ~AdjacencyListGraph();

  virtual bool
  addArc(const arc_t &arc);

  virtual bool
  addArc(vertex_t src, vertex_t dest, weight_t w);

  virtual void
  rmArc(const arc_t &arc);

  virtual void
  rmArc(vertex_t src, vertex_t dest);

  virtual void
  updateArc(const arc_t &arc);

  virtual weight_t
  increaseWeight(vertex_t src, vertex_t dest, weight_t w);

  virtual uint
  getNbrVertices() const;

  virtual list<neighbor_t>
  getSuccessors(vertex_t vertex) const;

  virtual list<neighbor_t>
  getPredecessors(vertex_t vertex) const;

  virtual weight_t
  getWeight(vertex_t src, vertex_t dest) const;

private:
  list<neighbor_t> *successors, *predecessors;
  uint nbr_vertices;
};

#endif /* VERTEXLISTGRAPH_H_ */
