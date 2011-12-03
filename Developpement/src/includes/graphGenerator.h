
#ifndef GRAPHGENERATOR_H_
#define GRAPHGENERATOR_H_

#include "VertexListGraph.h"

/**
 * Generates a random number in [min, max].
 * srand was had to initialize.
 * return
 */
uint
randMinMax(uint min, uint max);

void
graphGenerator(VertexListGraph& graph, uint min_weight = 1, uint max_weight = 1);

void
generateChemin(VertexListGraph& graph, uint min_weight, uint max_weight);

#endif /* GRAPHGENERATOR_H_ */
