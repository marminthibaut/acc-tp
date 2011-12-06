//============================================================================
// Name        : acc.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "includes/VertexListGraph.h"
#include "includes/graphGenerator.h"
#include "includes/algo.h"
#include "includes/flow.h"


int
main()
{

  VertexListGraph g(20);
  VertexListGraph level_graph(20);
  cout << "------------------------------------------------------" << endl;
  graphGenerator(g, 0 , 30);
  cout << g.toString() << endl;

  //cout << "Edmonds-Karp S = 0, P = 19" << endl;

  //edmondsKarp(g, 0, 19);

  levelGraph(g, level_graph, 0, 19);

  cout << "********************" << endl;
  cout << level_graph.toString()<< endl;





  return 0;
}
