

import std.stdio;
import graph.VertexListGraph;
import graph.IGraph;

void main()
{

	
	writeln("TEST");
	
	VertexListGraph g = new VertexListGraph(4);
	writeln(g);
	
	g.addArc(0,1);
	g.addArc(1,2);
	g.addArc(2,3);
	g.addArc(3,0);
	g.rmArc(0,0);
	
	writeln(g);


	
	
}