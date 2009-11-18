#include "solve.h"

int try_set(Graph* graph, int* vertices, int verts)
{
    Graph* copy = make_graph_copy(graph);
    int total = 0, i;

    for(i = 0; i < verts; i++)
        total += silent_find_chains_from(copy, vertices[i]);

    free_graph(&copy);
    return total;
}

int next_comb(int comb[], int k, int n)
{
    int i = k - 1;
    comb[i] += 1;
    while((i >= 0) && (comb[i] >= n - k + 1 + i))
    {
        i--;
        comb[i]++;
    }

    if(comb[0] > n - k)
        return 0;

    for (i = i + 1; i < k; ++i)
        comb[i] = comb[i - 1] + 1;

    return 1;
}

int solve(Graph* graph)
{
    Graph* copy = make_graph_copy(graph);
    int cover_size, total, i;

    int verts = graph->verts;
    int* vertices = (int*) malloc(sizeof(int) * verts);
    int solved = 0;

    total = silent_list_all_chains(graph);

    /*
     *If there are no simple chains then the minimum chain cover is 0
     */
    if(total == 0)
        return 0;

    /*
     *Try each subset now for a possible chain cover
     */
    for(cover_size = 1; cover_size <= verts; cover_size++)
    {
        for(i = 0; i < cover_size; i++)
            vertices[i] = i;

        printf("Trying subsets of size %d now\n", cover_size);
        do
        {
            /*
             *To print the subset being tested - usually not needed
             *printf("Trying set: {");
             *for (i = 0; i < cover_size; i++)
             *printf("%d, ", vertices[i]);
             *printf("\b\b}\n");
             */

            if(try_set(graph, vertices, cover_size) == total)
            {
            	if(!solved)
	            	printf("\nMinimum Chain Covers:\n");
                printf("Set: {");
                for (i = 0; i < cover_size; i++)
                    printf("%d%s", vertices[i], ((i < cover_size - 1) ? ", " : "}\n"));
                solved = 1;
            }
         }while(next_comb(vertices, cover_size, verts));
         if(solved)
		     return cover_size;

    }

    free_graph(&copy);

    //Execution should not reach here!
    return 0;
}
