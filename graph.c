#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

void add_edge(Graph* graph, int vid_1, int vid_2)
{
    Node *at_1, *at_2, *new_1, *new_2;

    //Find the last Nodes of the corresponding Node list
    at_1 = find_lastnode(graph->adj_list[vid_1].list);
    at_2 = find_lastnode(graph->adj_list[vid_2].list);

    //Allocate memory for new Nodes
    new_1 = (Node *) malloc(sizeof(Node));
    new_2 = (Node *) malloc(sizeof(Node));

    //Save the newly adjacent vertices
    new_1->vertex = &graph->vertex_list[vid_2];
    new_2->vertex = &graph->vertex_list[vid_1];

    //Setup the links. Handle differently if this is the first adjacent node.
    at_1 ? (at_1->next = new_1) : (graph->adj_list[vid_1].list = new_1);
    at_2 ? (at_2->next = new_2) : (graph->adj_list[vid_2].list = new_2);
    new_1->next = new_2->next = NULL;

    //Increment the number of edges
    graph->adj_list[vid_1].edges++;
    graph->adj_list[vid_2].edges++;
}

int create_random_edges(Graph* graph, double frac)
{
	int n = graph->verts, i, j, added = 0;
	double rnum;

	srand((unsigned int)time(NULL)); //Set the seed for the random number generator

	for(i = 0; i < n; i++)
		for(j = 0; j < i; j++)
		{
			rnum = rand() * 1.0 / RAND_MAX;
			if(rnum <= frac)
			{
				add_edge(graph, i, j);
				added++;
			}
		}

	//printf("Frac:%.2lf\tMaxEdges:%d\tTarget:%.2lf\tAddedEdges:%d\n", frac, n*(n-1)/2, (n*(n-1)/2)*frac, added);
	return added;
}

void free_adjlist(EdgeList** adj_list, int verts)
{
	int i;
	for(i = 0; i < verts; i++)
		free_nodelist((*adj_list)[i].list); //free the list of nodes that store adjacent vertices for this vertex
	free(*adj_list);
	*adj_list = NULL;
}

Node* make_list_copy(Node* list, Vertex* verts)
{
	Node *start = NULL, *cur = list, *cur_n = NULL, *prev_n = NULL;

	while(cur)
	{
		cur_n = (Node*) malloc(sizeof(Node));

		//if this is the first edge
		if(start == NULL)
			start = cur_n;
		else
			prev_n->next = cur_n;

		cur_n->next = NULL;
		cur_n->vertex = &verts[cur->vertex->id];

		prev_n = cur_n;
		cur_n = cur_n->next;
		cur = cur->next;
	}

	return start;
}

Graph* make_graph_copy(Graph* graph)
{
	int i;
	Graph* new = (Graph*) malloc(sizeof(Graph));
	Vertex* new_verts = make_vertex_copy(graph->vertex_list, graph->verts);
    EdgeList* new_adj_list = (EdgeList*) malloc(sizeof(EdgeList) * (graph->verts));

	//Creating the Adjacency List called "edges"
	for(i = 0; i < graph->verts; i++)
	{
		new_adj_list[i].edges = graph->adj_list[i].edges;
		new_adj_list[i].list = make_list_copy(graph->adj_list[i].list, new_verts);
	}

	//Plugging in
	new->verts = graph->verts;
	new->vertex_list = new_verts;
    new->adj_list = new_adj_list;

	return new;
}

Graph* build_empty_graph(Vertex** vertices, int verts)
{
	int i;
	Graph* graph = (Graph*) malloc(sizeof(Graph));

	//Plugging in the vertices
	graph->verts = verts;
	graph->vertex_list = *vertices;

	//Creating the Adjacency List called "edges"
	graph->adj_list = (EdgeList*) malloc(sizeof(EdgeList) * verts);
	for(i = 0; i < verts; i++)
	{
		graph->adj_list[i].edges = 0;
		graph->adj_list[i].list = NULL;
	}

	//Remove all other references to the vertex list
	*vertices = NULL;

	return graph;
}

void print_graph(Graph* graph)
{
	int i;
	Node* temp;

	for(i = 0; i < graph->verts; i++)
	{
		print_vertex(&graph->vertex_list[i], " :: ");
		temp = graph->adj_list[i].list;
		while(temp)
		{
			print_vertex(temp->vertex, " ");
			temp = temp->next;
		}
		printf("\n");
	}
}

void free_graph(Graph** graph)
{
//	Make sure the labels are not constant char pointers before free-ing them
//	free_vertexlist(&((*graph)->vertex_list), (*graph)->verts);
	free_adjlist(&((*graph)->adj_list), (*graph)->verts);
	*graph = NULL;
}
