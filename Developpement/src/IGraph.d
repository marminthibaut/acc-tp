
typedef uint weight_t ;
typedef vertex_id[] path_t ;
typedef uint vertex_id_t ;
typedef FlowNetwork IGraph ;

struct neighbor_t
{
	weight_t weight;
	vertex_id vertex;
}

struct arc_t; //????

interface IGraph
{
	void setNbrVertices(uint nbrVertices);
	void addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1);
  
  uint getNbrVertices();
  neighbor_t[] getNeighbors(vertex_id_t idVertexSrc);
}

interface IFlowNetwork : IGraph
{
	void setFlow(vertex_id_t start , vertex_id_t end, weight_t charge);
}

path_t leastArcsPath(IGraph g, vertex_id_t start, vertex_id_t end);

weight_t lightestArc(path_t); //retourner un arc?

IGraph updateResidualNetwork(IGraph g, path_t p, weight_t k);


