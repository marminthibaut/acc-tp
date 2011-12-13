/*
 * flow.h
 *
 *  Created on: 2 déc. 2011
 *      Author: clement
 */

#ifndef FLOW_H_
#define FLOW_H_

#include "../graph/LevelGraph.h"


/*******************************************************************************
 * General
 ******************************************************************************/

/**
 * Cette procédure génère une chaîne de caractères représentant l'affichage
 * de la valeur total du flot sur le réseau de transport ainsi que la valeur
 * du flot sur chaque arc.
 * @param flow_network le réseau de transport
 * @param residual_network le graphe d'écart associé
 */
string
flowToString(const AbstractGraph& flow_network,
    const AbstractGraph& residual_network);



/*******************************************************************************
 * Edmonds-Karp
 ******************************************************************************/

/**
 * A random flow network generator
 * Attention si le graph passé en paramètre contient des arcs ceux-ci seront
 * supprimé.
 * @param graph une référence vers un graph initialiser avec un nombre de sommets
 * @param rate la proportion d'arcs à ajouter au graphe en pourcentage par rapport au graphe complet.
 * @param min_weight valuation minimal des arcs
 * @param max_weight valuation maximal des arcs
 */
void
flowNetworkGenerator(AbstractGraph& graph, float rate, uint min_weight = 1,
    uint max_weight = 1);

/**
 * Mise à jour du graphe d'écart depuis un chemin et la valeur du flot à ajouter
 * sur ce chemin
 * @param le graphe de couche
 * @param p le chemin
 * @param k la valeur du flot à ajouter
 */
void
updateResidualNetwork(AbstractGraph& residualNetwork, path_t p, uint k);

/**
 * algorithme d'Edmonds-Karp
 * @param flow_network le réseau de transport
 * @param src le sommet source
 * @param dest le puit
 * @return le graphe d'écart final
 */
AdjacencyListGraph
edmondsKarp(const AbstractGraph& flow_network, vertex_t src, vertex_t dest);


/*******************************************************************************
 * Dinic
 ******************************************************************************/

/**
 * Mise à jour du graphe d'écart depuis un flot
 * @param residual_network le graphe de couche
 * @param p le flot
 */
void
updateResidualNetwork(AbstractGraph& residual_network, AbstractGraph& flow);

/**
 * Génération du graphe de couche associé au réseau de transport
 * @param residual_network le graphe d'écart
 * @param src la source
 * @param dest le puit
 * @return le graphe de couche
 */
LevelGraph
generateLevelGraph(const AbstractGraph& residual_network, vertex_t src,
    vertex_t dest);

/**
 * Calcul du flot bloquant
 * @param level_graph le graphe de couche
 * @param src la source
 * @param dest le puit
 * @return un flot bloquant
 */
AdjacencyListGraph
blockingFlow(LevelGraph& level_graph, vertex_t src, vertex_t dest);


/**
 * algorithme de Dinic
 * @param flow_network le réseau de transport
 * @param src le sommet source
 * @param dest le puit
 * @return le graphe d'écart final
 */
AdjacencyListGraph
dinic(const AbstractGraph& graph, vertex_t src, vertex_t dest);

#endif /* FLOW_H_ */
