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

#endif /* FLOW_H_ */
