#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "graph/AdjacencyListGraph.h"
#include "graph/LevelGraph.h"
#include "graph/MatrixGraph.h"

#include "includes/flow.h"


int
main(int argc, char** argv)
{

  if (argc < 4)
    {
      cout << "Erreur : parmètres manquant" << endl;
      return 1;
    }

  uint nbr_vertices = atoi(argv[1]);
  uint percent_arcs = atoi(argv[2]);
  uint nbr_exec = atoi(argv[3]);

  vertex_t src, dest;

  //Création du graph
  AdjacencyListGraph g(nbr_vertices);
  src = 0;
  dest = nbr_vertices - 1;

  uint seed = time(NULL);
  srand(seed);
  cout << "seed : " << seed << endl;



  for (int i = 0; i < nbr_exec; ++i)
    {
      printf("%d%%", i);
      fflush(stdout);

      flowNetworkGenerator(g, float(percent_arcs) / 100., 1, 20);
      cout << g.toString() << endl;

      //dinic(g, src, dest);
      //edmondsKarp(g, src, dest);

     printf("\10\10");
     for(int j = i; j >= 10; j /= 10)
        printf("\10");

    }

  //affichage du graph
  /* cout << "//****************************************" << endl;
   cout << "// Graph" << endl;
   cout << g.toString() << endl; */

  //cout << "Edmonds-Karp S = 0, P = 19" << endl;

  /*LevelGraph level_graph = levelGraph(residual_network, src, dest);
   cout << "********************" << endl;
   cout << "LEVEL GRAPH " << endl;
   cout << level_graph.toString() << endl;

   AdjacencyListGraph flow = blockingFlow(level_graph, src, dest);
   cout << "********************" << endl;
   cout << "BLOCKING FLOW" << endl;
   cout << flow.toString() << endl;*/

  return 0;
}
