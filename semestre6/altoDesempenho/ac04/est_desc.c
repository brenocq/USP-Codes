//gcc est_desc.c -g -openmp -lm -o a && ./a < entrada.txt
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void)
{
	unsigned row, col, i, j;
	double *matrix;

	// Read rows and columns
	fscanf(stdin, "%u ", &row);
	fscanf(stdin, "%u\n", &col);

	// Read matrix
	matrix = (double*) malloc(row*col * sizeof(double)); //Aloca a matriz
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(stdin, "%lf ",&(matrix[i*col+j])); //Lê a matriz

	// XXX Print matrix
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
			printf("%lf ", matrix[i*col+j]);
		printf("\n");
	}

	free(matrix);
}
