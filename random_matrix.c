#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "random_matrix.h"

//Creates a r x c Binary Matrix
Matrix* binary_matrix(int r, int c, double p)
{
	Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
	int i,j;

	srand((unsigned int)time(NULL)); //Set the seed for the random number generator

	//Allocate Memory for the Matrix
	matrix->data = (Bool**) malloc(sizeof(Bool*) * r);
	for(i = 0; i < r; i++)
		matrix->data[i] = (Bool*) malloc(sizeof(Bool) * c);
	matrix->rows = r;
	matrix->cols = c;

	//Fill it with 1s and 0s
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			{
				double rnum = rand() * 1.0 / RAND_MAX; //Generate a random number in the range [1, 0]
				if(rnum <= p)
					matrix->data[i][j] = TRUE;
				else
					matrix->data[i][j] = FALSE;
			}

	return matrix;
}

//Prints the Binary Matrix to a specified file
void print_binary_matrix(Matrix* matrix, FILE* fout)
{
	int i, j;

	//Output the contents of matrix to the file
	for(i = 0; i < matrix->rows; i++)
		{
			for(j = 0; j < matrix->cols; j++)
				if(matrix->data[i][j])
					fprintf(fout, "%d\t", matrix->data[i][j]);
				else
					fprintf(fout, ".\t");
			fprintf(fout, "\n");
		}
}

void free_matrix(Matrix** matrix)
{
	int i;
	for(i = 0; i < (*matrix)->rows; i++)
		free((*matrix)->data[i]);
	free((*matrix)->data);
	*matrix = NULL;
}

int count_vertices(Matrix* matrix)
{
	int count = 0;
	int i, j;

	for(i = 0; i < matrix->rows; i++)
		for(j = 0; j < matrix->cols; j++)
			if(matrix->data[i][j])
				count++;

	return count;
}

