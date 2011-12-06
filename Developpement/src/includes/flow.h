/*
 * flow.h
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#ifndef FLOW_H_
#define FLOW_H_

#include "graph.h"

void
updateResidualNetwork(AbstractGraph& residualNetwork, path_t p, uint k);

string
flowToString(AbstractGraph& graph, AbstractGraph& residualNetwork);

void
edmondsKarp(AbstractGraph& graph, vertex_t src, vertex_t dest);

void
levelGraph(AbstractGraph& residual_network, AbstractGraph& level_graph,
    vertex_t src, vertex_t dest);

#endif /* FLOW_H_ */
