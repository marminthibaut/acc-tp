#ifndef GRAPHGENERATOR_H_
#define GRAPHGENERATOR_H_

#include "AdjacencyListGraph.h"

/**
 * Generates a random number in [min, max].
 * srand was had to initialize.
 * return
 */
uint
randMinMax(uint min, uint max);

void
graphGenerator(AdjacencyListGraph& graph, uint min_weight = 1, uint max_weight =
    1);

void
generateChemin(AdjacencyListGraph& graph, uint min_weight, uint max_weight);

#endif /* GRAPHGENERATOR_H_ */
