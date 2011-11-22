
interface IGraph
{
	void setNbrVertices(uint nbrVertices);
	void addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1);
  
  uint getNbrVertices();
  neighbor_t[] getNeighbors(vertex_id_t idVertexSrc);
}
