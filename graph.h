#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"

//EdgeList :: List of all adjacent vertices to a particular vertex
//All EdgeLists taken together constitute the Adjacency List
typedef struct
{
	int edges;
	Node* list;
}EdgeList;

//A Graph with its Vertices & Edges
typedef struct
{
	int verts;
	Vertex* vertex_list;
	EdgeList* adj_list;
}Graph;

//Create and edge between two vertices with vertex ids vid_1 and vid_2
//DOES NOT CHECK FOR DUPLICACY
void add_edge(Graph* graph, int vid_1, int vid_2);

//Make random edges between vertices, of a new graph, with a given density
//Return the actual number of added edges
int create_random_edges(Graph* graph, double frac);
void free_adjlist(EdgeList** adj_list, int verts);

//Make a copy of the edge list corresponding to a single vertex
//Vertex pointers are chosen from the vertex list that is suppliec
Node* make_list_copy(Node* list, Vertex* verts);

Graph* make_graph_copy(Graph* graph);
Graph* build_empty_graph(Vertex** vertices, int verts);
void print_graph(Graph* graph);
void free_graph(Graph** graph);

#endif
