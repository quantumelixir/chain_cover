#ifndef SOLVE_H
#define SOLVE_H

#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#include "chain.h"

//Return the number of chains accessible from the given set of vertices
int try_set(Graph* graph, int* vertices, int verts);

//Generates the next subset of size k
int next_comb(int comb[], int k, int n);

//Solve the minimum chain cover problem in O(2^n) time and return the size of the minimum chain cover
int solve(Graph* graph);

#endif

