import graph.IGraph;
import std.conv;

class VertexListGraph : IGraph
{
	
	//************************************************************************************************
	//	CONSTRUCTOR
	//************************************************************************************************
	
	public this(uint nbrVertices)
	{
		this.vertexList.length = nbrVertices;
	}
	
	//************************************************************************************************
	//	METHODS
	//************************************************************************************************
	
	public bool addArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1)
	{
		if(idVertexSrc > vertexList[idVertexSrc].length || idVertexDest > vertexList[idVertexSrc].length)
			return false;
			
		vertexList[idVertexSrc].length += 1;
		vertexList[idVertexSrc][$ - 1].weight = weight;
		vertexList[idVertexSrc][$ - 1].vertex = idVertexDest;
		return true;
	}
	
	public bool rmArc(vertex_id_t idVertexSrc, vertex_id_t idVertexDest, weight_t weight = 1)
	{
		throw new Exception("not implemented method");
		return true;
	}
	
	//************************************************************************************************
	//	ACCESSOR METHODS
	//************************************************************************************************
	
	public uint getNbrVertices() const
	{
		return cast(uint)vertexList.length;
	}
	
	public neighbor_t[] getNeighbors(vertex_id_t idVertexSrc)
	{
		neighbor_t[] a = vertexList[idVertexSrc];
		return a;
	}

	//************************************************************************************************
	//	PRINT METHODS
	//************************************************************************************************

	public string toString() const
  {
  	string s;
  	foreach(uint i, const neighbor_t[] successors; this.vertexList)
  	{
  		s = text(s, i, " : ");
  		foreach(neighbor_t neighbor; successors)
  		{
  			s = text(s , cast(uint)(neighbor.vertex), ", ");
  		}
  		s = text( s, "\n");
		}
  	return s;
  }

  //************************************************************************************************
	//	ATTRIBUTS
	//************************************************************************************************
	
	private neighbor_t[][] vertexList;
}

