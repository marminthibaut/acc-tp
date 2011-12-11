
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "graph/AdjacencyListGraph.h"
#include "graph/LevelGraph.h"
#include "graph/MatrixGraph.h"

#include "includes/flow.h"


int
main()
{

  vertex_t src, dest;
  src = 0;
  dest = 19;

  //Création du graph
  AdjacencyListGraph g(50);
  uint seed = time(NULL);
  srand(seed);
  cout << "seed : " << seed << endl;
  flowNetworkGenerator(g, 0.5, 1, 30);

  //affichage du graph
  cout << "//****************************************" << endl;
  cout << "// Graph" << endl;
  cout << g.toString() << endl;


  dinic(g, src, dest);

  //cout << "Edmonds-Karp S = 0, P = 19" << endl;

  edmondsKarp(g, src, dest);


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
