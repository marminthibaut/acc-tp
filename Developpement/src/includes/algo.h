/*
 * algo.h
 *
 *  Created on: 1 déc. 2011
 *      Author: clement
 */

#ifndef ALGO_H_
#define ALGO_H_

#include "graph.h"

path_t
leastArcsPath(AbstractGraph &g, vertex_t start, vertex_t end);

path_t
leastFirst(AbstractGraph &g, vertex_t start, vertex_t end);

weight_t lightestArc(AbstractGraph& g, path_t);

#endif /* ALGO_H_ */
