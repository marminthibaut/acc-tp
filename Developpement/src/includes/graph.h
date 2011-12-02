/*
 * graph.h
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <list>
#include "types.h"

using namespace std;

typedef int weight_t;
typedef uint vertex_t;

typedef struct
{
  vertex_t vertex_src;
  vertex_t vertex_dest;
  weight_t weight;
} arc_t;

typedef struct
{
  vertex_t vertex;
  weight_t weight;
} neighbor_t;

bool
operator==(const neighbor_t& n1, const neighbor_t& n2);

typedef list<vertex_t> path_t;

/**
 * Class IGraph
 */
class AbstractGraph
{
public:

  AbstractGraph();
  virtual
  ~AbstractGraph() = 0;

  virtual bool
  addArc(const arc_t &arc) = 0;

  virtual void
  rmArc(const arc_t &arc) = 0;

  virtual void
  updateArc(const arc_t &arc) = 0;

  virtual uint
  getNbrVertices() const = 0;

  virtual string
  toString() const;

  virtual list<neighbor_t>&
  getNeighbors(vertex_t vertex_src) const = 0;

  virtual weight_t
  getWeight(vertex_t src, vertex_t dest) const = 0;

};

#endif /* GRAPH_H_ */
