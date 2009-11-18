#ifndef VERTEX_H
#define VERTEX_H

#include "boolean.h"

//Vertices have an id, visited flag and an optional string label
typedef struct
{
	int id;
	Bool visited;
	char* label;
}Vertex;

//Wrapper for a vertex pointer to be stored as an element in a singly linked list.
typedef struct Nd
{
	struct Nd* next; //Pointer to the a similar Node structure
	Vertex* vertex;  //Pointer to the associated vertex
}Node;

//Build a Vertex array of size verts with given string labels
Vertex* build_vertices(int verts, char** labels);

//Find the last node in a list of nodes beginning with the start Node.
Node* find_lastnode(Node* start);

void print_vertex(Vertex* vertex, char* end);
void print_vertex_list(Vertex* vlist, int verts);

//Make a copy of the vertices marking them unvisited
Vertex* make_vertex_copy(Vertex* vertices, int verts);

//For an exact copy of the vertex list
Vertex* make_exact_vertex_copy(Vertex* vertices, int verts);

void free_vertexlist(Vertex** vertices, int verts);
void free_nodelist(Node* start);

#endif
