/*
 * flow.h
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#ifndef FLOW_H_
#define FLOW_H_

#include "graph.h"
#include "LevelGraph.h"

void
flowNetworkGenerator(AbstractGraph& graph, float rate, uint min_weight = 1,
    uint max_weight = 1);

void
updateResidualNetwork(AbstractGraph& residualNetwork, path_t p, uint k);

string
flowToString(const AbstractGraph& graph, const AbstractGraph& residualNetwork);

void
edmondsKarp(const AbstractGraph& graph, vertex_t src, vertex_t dest);

LevelGraph
generateLevelGraph(const AbstractGraph& residual_network, vertex_t src, vertex_t dest);

AdjacencyListGraph
blockingFlow(LevelGraph& level_graph, vertex_t src, vertex_t dest);

void
addFlow(AbstractGraph& graph, AbstractGraph& flow);

void
dinic(const AbstractGraph& graph, vertex_t src, vertex_t dest);

#endif /* FLOW_H_ */
