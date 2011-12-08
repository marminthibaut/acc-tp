//============================================================================
// Name        : acc.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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

  AdjacencyListGraph g(20);
  cout << "------------------------------------------------------" << endl;
  graphGenerator(g, 1 , 30);
  cout << "------------------------------------------------------" << endl;
  cout << g.toString() << endl;
  cout << "------------------------------------------------------" << endl;
  dinic(g, src, dest);

  //cout << "Edmonds-Karp S = 0, P = 19" << endl;

  //edmondsKarp(g, 0, 19);

 /* LevelGraph level_graph = levelGraph(g, src, dest);
  cout << "********************" << endl;
  cout << "LEVEL GRAPH " << endl;
  cout << level_graph.toString() << endl;

  AdjacencyListGraph flow = blockingFlow(level_graph, src, dest);
  cout << "********************" << endl;
  cout << "BLOCKING FLOW" << endl;
  cout << flow.toString() << endl;

  cout << "********************" << endl;
   cout << "LEVEL GRAPH " << endl;
   cout << level_graph.toString() << endl; */






  return 0;
}
