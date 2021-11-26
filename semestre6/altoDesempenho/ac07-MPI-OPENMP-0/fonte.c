// SSC0903 - Computação de Alto Desempenho
// Multiplicacao de matrizes quadradas com MPI e OPENMP
//
// Breno Cunha Queiroz
// Matheus Branco Borella
// Natan Bernardi Cerdeira

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define N 1000
#define NUMTHREADS 2

void printMatrices(int* A, int* B, int* C);

int main(int argc, char *argv[])
{
    srand(2021);
    int *A, *Asub;// A matrix
    int *Bt, *Btsub;// B matrix transposed (cache friendly multiplication)
    int *C, *Cres, *Csub;// C matrix

    int numProc, procRank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    //---------- Error checking ----------//
    // Check if number of processes is consistent
    if(numProc > N)
    {
        if(procRank == 0)
            printf("Should not have more processes than the matrix size. numSlaves=%d N=%d\n", numProc-1, N);
        MPI_Finalize();
        exit(0);
    }

    int perfectNumProc = floor(sqrt(numProc))*floor(sqrt(numProc));
    if(perfectNumProc != numProc)
    {
        if(procRank == 0)
            printf("The number of processes must be a perfect square. It is %d, you may use %d instead\n", numProc, perfectNumProc);
        MPI_Finalize();
        exit(0);
    }

    //---------- Initialization ----------//
    // Create and initialize matrices
    if(procRank == 0)
    {
        // If 0, create and initialize matrices
        A = (int*)malloc(N*N*sizeof(int));
        Bt = (int*)malloc(N*N*sizeof(int));
        C = (int*)malloc(N*N*sizeof(int));
        Cres = (int*)malloc(N*N*sizeof(int));

        for(unsigned i = 0; i < N; i++)
            for(unsigned j = 0; j < N; j++)
            {
                A[i*N+j] = rand()%199 - 99;// [-99, 99]
                Bt[i*N+j] = rand()%199 - 99;// [-99, 99]
                C[i*N+j] = 0;
            }
    }

    // Balance work across processes
    int eleSizesA[numProc];// Number of elements of A send to each process
    int eleSizesB[numProc];// Number of elements of B send to each process
    int eleSizesC[numProc];// Number of elements of B send to each process
    int eleOffsetsA[numProc];// Offsets for each process
    int eleOffsetsB[numProc];// Offsets for each process
    int eleOffsetsC[numProc];// Offsets to receive C result
    unsigned numRows = sqrt(numProc);
    unsigned sizeBlock = N/numRows;
    for(unsigned i = 0; i < numProc; i++)
    {
        unsigned sizeA = sizeBlock;
        unsigned sizeB = sizeBlock;
        unsigned blockRow = i/numRows;
        unsigned blockCol = i%numRows;

        // Add all remaining rows/cols to the last process
        if(blockRow == numRows-1)
            sizeA += N-(N/numRows)*numRows;
        if(blockCol == numRows-1)
            sizeB += N-(N/numRows)*numRows;

        // Define matrix data that each process will need to compute its block
        eleSizesA[i] = sizeA*N;
        eleSizesB[i] = sizeB*N;
        eleSizesC[i] = sizeA*sizeB;
        eleOffsetsA[i] = N*blockRow*sizeBlock;
        eleOffsetsB[i] = N*blockCol*sizeBlock;
        if(i > 0)
            eleOffsetsC[i] = eleOffsetsC[i-1]+sizeA*sizeB;
        else
            eleOffsetsC[i] = 0;
    }

    // Allocate sub matrix data
    Asub = (int*)malloc(eleSizesA[procRank]*sizeof(int));
    Btsub = (int*)malloc(eleSizesB[procRank]*sizeof(int));
    Csub = (int*)malloc(eleSizesC[procRank]*sizeof(int));
    //printf("[process %d of %d] -> block size:%dx%d\n", procRank, numProc, eleSizesA[procRank]/N, eleSizesB[procRank]/N);

    //---------- Communication scatter A and B ----------//
    // Send A submatrices
    MPI_Scatterv(A, eleSizesA, eleOffsetsA, MPI_INT, Asub, eleSizesA[procRank], MPI_INT, 0, MPI_COMM_WORLD);
    // Send B^T submatrices
    MPI_Scatterv(Bt, eleSizesB, eleOffsetsB, MPI_INT, Btsub, eleSizesB[procRank], MPI_INT, 0, MPI_COMM_WORLD);

    //---------- Calculations (TODO openmp) ----------//
    unsigned sizeA = eleSizesA[procRank]/N;
    unsigned sizeB = eleSizesB[procRank]/N;

    #pragma omp parallel for num_threads(NUMTHREADS)
    for(unsigned i = 0; i < sizeA; i++)
        for(unsigned j = 0; j < sizeB; j++)
        {
            int dot = 0;
            for(unsigned k = 0; k < N; k++)
                dot += Asub[i*N+k] * Btsub[j*N+k];
            Csub[i*sizeB+j] = dot;
            //Csub[i*sizeB+j] = procRank;// Good to see which process is computing which part of the C matrix
        }

    //---------- Communication gatter C ----------//
    MPI_Gatherv(Csub, eleSizesC[procRank], MPI_INT, Cres, eleSizesC, eleOffsetsC, MPI_INT, 0, MPI_COMM_WORLD);

    //---------- Build C from Cres ----------//
    // Reordering results
    if(procRank == 0)
    {
        #pragma omp parallel for num_threads(NUMTHREADS)
        for(unsigned p = 0; p < numProc; p++)
        {
            unsigned row = (p/numRows)*sizeBlock;
            unsigned col = (p%numRows)*sizeBlock;
            unsigned blockNumRows = eleSizesA[p]/N;
            unsigned blockNumCols = eleSizesB[p]/N;
            unsigned it = eleOffsetsC[p];
            for(unsigned i = row; i < row+blockNumRows; i++)
                for(unsigned j = col; j < col+blockNumCols; j++, it++)
                    C[i*N+j] = Cres[it];
        }
    }

    //---------- Result and finish ----------//
    // Print matrices
    if(procRank == 0)
    {
        printMatrices(A, Bt, C);
        free(A);
        free(Bt);
        free(Cres);
        free(C);
    }
    free(Asub);
    free(Btsub);
    free(Csub);

	if(MPI_Finalize() != MPI_SUCCESS)
    {
		printf("Failed finalize MPI!\n");
    }

    return 0;
}

void printMatrices(int* A, int* B, int* C)
{
    for(unsigned i = 0; i < N; i++)
    {
        for(unsigned k = 0; k < 5; k++)
        {
            for(unsigned j = 0; j < N; j++)
            {
                switch(k)
                {
                    case 0:
                        //printf("%3d ", A[i*N+j]);
                        break;
                    case 1:
                        //if(j == 0)
                        //    printf("%s", i==N/2?"* ":"  ");
                        break;
                    case 2:
                        //printf("%3d ", B[j*N+i]);
                        break;
                    case 3:
                        //if(j == 0)
                        //    printf("%s", i==N/2?"= ":"  ");
                        break;
                    case 4:
                        //printf("%3d%s", C[i*N+j], j==N-1?"\n":" ");
                }
            }
        }
    }
}
