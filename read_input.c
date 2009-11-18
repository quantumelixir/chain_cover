#include "read_input.h"

Graph* read_input(FILE* input)
{
	char line[80], b1[80], b2[80];
	int verts, edges, u, v;
	Vertex* vertices = NULL;
	Graph* graph = NULL;

	fgets(line, 80, input);
	sscanf(line, "%s%s%d%d", b1, b2, &verts, &edges);
	vertices = build_vertices(verts, NULL);
	graph = build_empty_graph(&vertices, verts);

	printf("Graph Input: Vertices:%d Edges:%d\n", verts, edges);

	while(fgets(line, 80, input) != NULL)
	{
		sscanf(line, "%s%d%d", b1, &u, &v);
		add_edge(graph, u - 1, v - 1);
	}

	return graph;
}
