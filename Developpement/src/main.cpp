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

  cout << "Hello World" << endl; // prints !!!Hello World!!!

  VertexListGraph g(20);
  cout << "--" << endl;
  graphGenerator(g, 0 , 30);

  arc_t arc;
       arc.vertex_src = 1;
       arc.vertex_dest = 0;
       arc.weight = 1;
       g.addArc(arc);

  cout << g.toString() << endl;

  path_t path = leastArcsPath(g, 0, 19);

  path_t::iterator it;
  for(it = path.begin(); it != path.end(); it++)
    cout << (*it) << " -> ";

  cout << endl;
  int k = lightestArc(g, path);
  cout << "-->" << k << endl;

  updateResidualNetwork(g, path, k);

  cout << g.toString() << endl;


  return 0;
}
