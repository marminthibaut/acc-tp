

typedef FlowNetwork IGraph ;

interface IFlowNetwork : IGraph
{
	void setFlow(vertex_id_t start , vertex_id_t end, weight_t charge);
}

