module graph;

class MatrixGraph : IGraph
{
	/// ATTRIBUTES
	private weight_t** vertexMatrix;

	/// METHODS
	this(uint nbrVertices)
	{
		// create the matrix
		vertexMatrix = new weight_t[nbrVertices][nbrVertices];
		
		// set all weights to 0 (edge doesn't not exist)
		// @todo : new may already set to zero
		for(int line = 0; line < nbrVertices; line++)
			for(int col = 0; col < nbrVertcies; col++)
				vertexMatrix[line][col] = 0;
				
	}
	
	void addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, 
		weight_t weight = 1)
	{
		// set the weight in the adjacency matrix to "create" the arc
		vertexMatrix[idVertexSrc][idVertexDest] = weight;
	}
}
