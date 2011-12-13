#ifndef MATRIXGRAPH_H_
#define MATRIXGRAPH_H_

#include "graph.h"

class MatrixGraph : public AbstractGraph
{

public:
  //************************************************************************************************
  //      CONSTRUCTOR
  //************************************************************************************************

  MatrixGraph(uint nbr_vertices);

  MatrixGraph(const AbstractGraph& graph);

  MatrixGraph(const MatrixGraph& graph);

  MatrixGraph &
  operator=(const AbstractGraph& graph);

  MatrixGraph &
  operator=(const MatrixGraph& graph);

  virtual
  ~MatrixGraph();

  virtual bool
  addArc(const arc_t &arc);

  virtual bool
  addArc(vertex_t src, vertex_t dest, weight_t w);

  virtual void
  rmArc(const arc_t &arc);

  virtual void
  rmArc(vertex_t src, vertex_t dest);

  virtual void
  rmAllArc();

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
  weight_t **matrix;
  uint nbr_vertices;

protected:
  void
  _clear();

  void
  _construct(int nbr_vertices);

  void
  _construct(const AbstractGraph& graph);

};

#endif /* MATRIXGRAPH_H_ */
