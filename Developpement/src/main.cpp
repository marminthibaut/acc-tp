

#include <iostream>
using namespace std;

#include "includes/AdjacencyListGraph.h"
#include "includes/graphGenerator.h"
#include "includes/algo.h"
#include "includes/flow.h"
#include "includes/LevelGraph.h"


int
main()
{


  vertex_t src, dest;
  src = 0;
  dest = 19;

  //Création du graph
  AdjacencyListGraph g(20);
  graphGenerator(g, 1 , 30);

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
