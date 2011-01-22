#include <stdio.h>
#include <stdlib.h>

#include "vertex.h"

Vertex* build_vertices(int verts, char** labels)
{
	int i;
	Vertex* vertices = (Vertex*) malloc(sizeof(Vertex) * verts);
	for(i = 0; i < verts; i++)
	{
		vertices[i].id = i;
		vertices[i].label = labels == NULL ? NULL : labels[i];
		vertices[i].visited = FALSE;

		//Remove all other references to the label string
		if(labels)
			labels[i] = NULL;
	}

	return vertices;
}

Vertex* make_vertex_copy(Vertex* vertices, int verts)
{
	int i;
	Vertex* new = (Vertex*) malloc(sizeof(Vertex) * verts);

	for(i = 0; i < verts; i++)
	{
		new[i].id = vertices[i].id;
		new[i].label = vertices[i].label;	//Label copying isn't perfect
		new[i].visited = 0;
	}

	return new;
}

Vertex* make_exact_vertex_copy(Vertex* vertices, int verts)
{
	int i;
	Vertex* new = (Vertex*) malloc(sizeof(Vertex) * verts);

	for(i = 0; i < verts; i++)
	{
		new[i].id = vertices[i].id;
		new[i].label = vertices[i].label;
		new[i].visited = vertices[i].visited;
	}

	return new;
}

Node* find_lastnode(Node* start)
{
	Node *temp = start, *prev = NULL;
	if(start == NULL)
		return prev;
	while(1)
	{
		prev = temp;
		temp = temp->next;
		if(temp == NULL)
			break;
	}

	return prev;
}

void print_vertex(Vertex* vertex, char* end)
{
	printf("[%2d%s%s]%s", vertex->id, vertex->label ? ":" : "", vertex->label ? vertex->label : "", end ? end : " -> ");
}

void free_vertexlist(Vertex** vertices, int verts)
{
	int i;
	for(i = 0; i < verts; i++)
		free((*vertices)[i].label);
	free(*vertices);
	*vertices = NULL;
}

void free_nodelist(Node* start)
{
	if(start == NULL)	//Zero Length nodelist
		return;
	if(start->next)
		free_nodelist(start->next);
	free(start);
}

void print_vertex_list(Vertex* vlist, int verts)
{
	int i;
	printf("Vertex List:");
	for(i = 0; i < verts; i++)
		printf("[%d %d] ", vlist[i].id, vlist[i].visited);
	printf("\n");
}
