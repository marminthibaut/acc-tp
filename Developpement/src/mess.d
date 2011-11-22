typedef vertex_id[] path_t ;



struct arc_t; //????




path_t leastArcsPath(IGraph g, vertex_id_t start, vertex_id_t end);

weight_t lightestArc(path_t); //retourner un arc?

IGraph updateResidualNetwork(IGraph g, path_t p, weight_t k);


