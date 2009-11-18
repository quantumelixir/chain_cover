#ifndef RANDOM_MATRIX_H
#define RANDOM_MATRIX_H

#include "boolean.h"

typedef struct
{
	int rows, cols;
	Bool** data;
}Matrix;

Matrix* binary_matrix(int r, int c, double p);
void free_matrix(Matrix** matrix);
void print_binary_matrix(Matrix* matrix, FILE* fout);
int count_vertices(Matrix* matrix);

#endif
