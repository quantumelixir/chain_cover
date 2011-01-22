#include "chain.h"

int find_chains_from(Graph* graph, int start)
{
	Node *temp = graph->adj_list[start].list, *cur;
	EdgeList* edgelist = NULL;
	int chains = 0;

	//simple chains cannot begin from a degree two vertex
	if(graph->adj_list[start].edges == 2)
		return 0;

	//All simple chains from this vertex have been explored
	graph->vertex_list[start].visited = TRUE;


	//increment over the adjacent (nodes)vertices of the vertex with id "start"
	while(temp)
	{
		//if the adjacent vertex has not already been visited
		if(temp->vertex->visited == FALSE)
		{
			print_vertex(&graph->vertex_list[start], " -> ");
			//travel along the simple chain
			cur = temp;
			edgelist = &graph->adj_list[cur->vertex->id];
			while(1)
			{
				if(edgelist->edges == 2)
				{
					cur->vertex->visited = TRUE;
					print_vertex(cur->vertex, " -> ");

					//Out of the two adjaxcent vertices choose the unvisited one.
					//If both are visited then you are stuck in a cycle. Break out of it.
					if(edgelist->list->vertex->visited)
						if(edgelist->list->next->vertex->visited)
						{
							printf("<Detected a cycle!>\n");
							break;
						}
						else
							cur = edgelist->list->next;
					else
						cur = edgelist->list;
					edgelist = &graph->adj_list[cur->vertex->id];
				}
				else
				{
					print_vertex(cur->vertex, "");
					chains++;
					break;
				}
			}
			printf("\n");
		}

		temp = temp->next;
	}
	
	return chains;
}

int silent_find_chains_from(Graph* graph, int start)
{
	Node *temp = graph->adj_list[start].list, *cur;
	EdgeList* edgelist = NULL;
	int chains = 0;

	//simple chains cannot begin from a degree two vertex
	if(graph->adj_list[start].edges == 2)
		return 0;

	//All simple chains from this vertex have been explored
	graph->vertex_list[start].visited = TRUE;

	//increment over the adjacent (nodes)vertices of the vertex with id "start"
	while(temp)
	{
		//if the adjacent vertex has not already been visited
		if(temp->vertex->visited == FALSE)
		{
			//travel along the simple chain
			cur = temp;
			edgelist = &graph->adj_list[cur->vertex->id];
			while(1)
			{
				if(edgelist->edges == 2)
				{
					cur->vertex->visited = TRUE;

					//Out of the two adjaxcent vertices choose the unvisited one.
					//If both are visited then you are stuck in a cycle. Break out of it.
					if(edgelist->list->vertex->visited)
						if(edgelist->list->next->vertex->visited)
							break;
						else
							cur = edgelist->list->next;
					else
						cur = edgelist->list;
					edgelist = &graph->adj_list[cur->vertex->id];
				}
				else
				{
					chains++;
					break;
				}
			}
		}

		temp = temp->next;
	}
	
	return chains;
}

int list_all_chains(Graph* graph)
{
	int total = 0, i;
	Graph* copy = make_graph_copy(graph);

	for(i = 0; i < graph->verts; i++)
		total += find_chains_from(copy, copy->vertex_list[i].id);

	free_graph(&copy);

	return total;
}

int silent_list_all_chains(Graph* graph)
{
	int total = 0, i;
	Graph* copy = make_graph_copy(graph);

	for(i = 0; i < graph->verts; i++)
		total += silent_find_chains_from(copy, copy->vertex_list[i].id);

	free_graph(&copy);

	return total;
}
