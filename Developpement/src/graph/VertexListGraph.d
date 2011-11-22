module graph;

class VertexListGraph : IGraph
{
	this(uint nbrVertices)
	{
		vertexList.length = nbrVertices;
	}
	
	void addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1)
	{
		vertexList[idVertexSrc].weight = weight;
		vertexList[idVertexSrc].vertex = idVertexDest;
	}


	
	private neighbor_t[] vertexList;
}

