/*
	I. Minimum Chain Cover:
		A. Finds the minimum chain cover of a given graph using exact methods.
		B. Parameter based random graph generation
		C. Finding and listing all reachable simple chains from a given vertex
		D. Cycle Detection
		E. Non recursive k-subset generation
		F. List all k vertex sets that are also chain covers
        G. Specify graph as a text file for input

	II. Running the program
		A. USAGE: Specify <rows> <columns> <vertex density> <edge connectivity>. All are mandatory.

	III. General Naming Conventions:
		A. Only structures have capital first letter names
		B. All other identifiers have lowercase names with underscores for separators.
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "graph.h"
#include "chain.h"
#include "read_input.h"
#include "solve.h"
#include "random_matrix.h"

int main(int argc, char *argv[])
{
	Matrix* matrix;
	Vertex* vertices;
	Graph* graph;
	int r, c, verts, edges;
	float p, q;
	FILE *fout = fopen("a04_out_07_01.txt", "w");

	if(argc == 5)
	{
		r = atoi(argv[1]);
		c = atoi(argv[2]);
		p = atof(argv[3]);
		q = atof(argv[4]);
	}
	else
	{
		printf("USAGE: Specify <rows> <columns> <vertex density> <edge connectivity>. All are mandatory.\n");
		exit(0);
	}

	/*
	printf("Dimensions of the Binary Matrix: Rows<space>Columns: ");
	scanf("%d%d", &r, &c);
	printf("Density of 1s: Between 0 to 1: ");
	scanf("%f", &p);
	printf("Edge Connectivity: Between 0 to 1: ");
	scanf("%f", &q);
	*/

	printf("Rows: %d Columns: %d VertexDensity: %f EdgeConnectivity: %f\n\n", r, c, p, q);

	matrix = binary_matrix(r, c, p);

	printf("Generated Binary Matrix: \n");
	print_binary_matrix(matrix, stdout);
	print_binary_matrix(matrix, fout);
	printf("\n");

	verts = count_vertices(matrix);
	vertices = build_vertices(verts, NULL);
	graph = build_empty_graph(&vertices, verts);
	edges = create_random_edges(graph, q);

	printf("Adjacency List for the Random Graph G=(%d, %d):\n", verts, edges);
	print_graph(graph);
	printf("\n");

	printf("List of simple chains: ");
    printf("Total of %d simple chains\n\n", list_all_chains(graph));

	printf("The minimum chain cover for this graph is of size %d\n", solve(graph));

	free_graph(&graph);
	free_matrix(&matrix);

	fclose(fout);

	return 0;
}

//testing: 
//gcc -Wall main.c random_matrix.c chain.c graph.c vertex.c solve.c read_input.c
