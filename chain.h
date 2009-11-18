#ifndef CHAIN_H
#define CHAIN_H

#include "graph.h"
#include "vertex.h"

//Lists all the unexplored simple chains beginning from  the given start vertex.
//Returns the number of such simple chains. Operates on the original graph itself.
int find_chains_from(Graph* graph, int start);

//Same as find_chains_from except it doesn't produce output.
int silent_find_chains_from(Graph* graph, int start);

//List all simple chains for the given graph. Does not affect the original graph.
int list_all_chains(Graph* graph);

//Same as list_all_chains except doesn't it produce output
int silent_list_all_chains(Graph* graph);

#endif
