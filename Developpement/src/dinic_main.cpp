

#include <stdio.h>
#include <cstdlib>

#include <fstream>

using namespace std;

#include "graph/flow/flow.h"

/**
 * usage :
 * dinic <nbr_sommets> <rate_arcs> [<seed>]
 */
int
main(int argc, char** argv)
{
  uint seed;
  uint nbr_vertices;
  vertex_t src, dest;
  float percent_arcs;

  //*************************************************
  // INITIALISATION

  if (argc < 3)
  {
   printf("Erreur : paramètres manquants");
   return 1;
  }

  nbr_vertices = atoi(argv[1]);
  percent_arcs = float(atoi(argv[2])) / 100.;
  src = 0;
  dest = nbr_vertices - 1;
  AdjacencyListGraph flow_network(nbr_vertices);
  AdjacencyListGraph residual_network(nbr_vertices);



  //random seed
  seed = time(NULL);
  if(argc > 3)
    seed = atoi(argv[3]);

  printf("Seed : %d\n", seed);
  srand(seed);

  //*************************************************

  flowNetworkGenerator(flow_network, percent_arcs, 1, 20);
  residual_network = dinic(flow_network, src, dest);

  ofstream fichier("dinic.dot", ios::out | ios::trunc);
  if(fichier)
    {
      fichier << flowToDotString(flow_network, residual_network) << endl;
      fichier.close();
    }

  printf(flowToString(flow_network, residual_network).c_str());





}




