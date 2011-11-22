module graph;

typedef uint weight_t ;
typedef uint vertex_id_t ;

struct neighbor_t
{
	weight_t weight;
	vertex_id vertex;
}

interface IGraph
{
	this(uint nbrVertices);
	
	bool addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1);
	bool rmArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1);
  
  uint getNbrVertices() const;
  neighbor_t[] getNeighbors(vertex_id_t idVertexSrc);
}


