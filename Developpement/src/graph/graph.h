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

#include "../includes/types.h"

using namespace std;

typedef int weight_t;
typedef uint vertex_t;

typedef struct
{
  vertex_t u;
  vertex_t v;
} edge;

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

/*******************************************************************************
 * Functions
 ******************************************************************************/

class AbstractGraph;

path_t
leastArcsPath(AbstractGraph &g, vertex_t start, vertex_t end);

path_t
leastFirst(AbstractGraph &g, vertex_t start, vertex_t end);

weight_t
lightestArc(AbstractGraph& g, path_t);

string
pathToString(path_t path, const AbstractGraph& g);

/*******************************************************************************
 * Class AbstractGraph
 ******************************************************************************/
class AbstractGraph
{
public:

  AbstractGraph();
  virtual
  ~AbstractGraph() = 0;

  virtual bool
  addArc(const arc_t &arc) = 0;

  virtual bool
  addArc(vertex_t src, vertex_t dest, weight_t w) = 0;

  virtual void
  rmArc(const arc_t &arc) = 0;

  virtual void
  rmArc(vertex_t src, vertex_t dest) = 0;

  virtual void
  updateArc(const arc_t &arc) = 0;

  virtual weight_t
  increaseWeight(vertex_t src, vertex_t dest, weight_t w) = 0;

  virtual uint
  getNbrVertices() const = 0;

  virtual string
  toString() const;

  virtual list<neighbor_t>
  getSuccessors(vertex_t vertex) const = 0;

  virtual list<neighbor_t>
  getPredecessors(vertex_t vertex) const = 0;

  virtual weight_t
  getWeight(vertex_t src, vertex_t dest) const = 0;

};

#endif /* GRAPH_H_ */
