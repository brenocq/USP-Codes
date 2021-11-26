// SSC0903 - Computação de Alto Desempenho
// AC08 - Multiplicacao de matrizes quadradas com CUDA
//
// Breno Cunha Queiroz
// Matheus Branco Borella
// Natan Bernardi Cerdeira

#include <stdio.h>
#include <stdlib.h>

__global__ 
void multiFast(double *A, double* B, double *C, int N, int blockSize)
{
    extern __shared__ double shd[];
    double* dataA = shd;
    double* dataB = shd + N*blockSize;

    int row = blockIdx.y*blockDim.y + threadIdx.y;
    int col = blockIdx.x*blockDim.x + threadIdx.x;

    //----- Load -----//
    int numToLoad = N/blockSize;

    // Load A
    int startCol = numToLoad*threadIdx.x;
    int endCol = startCol + numToLoad;
    if(threadIdx.x == blockSize-1)
        endCol = N;
    for(unsigned i = startCol; i < endCol; i++)
        dataA[threadIdx.y*N+i] = A[row*N + i];

    // Load B
    startCol = numToLoad*threadIdx.y;
    endCol = startCol + numToLoad;
    if(threadIdx.y == blockSize-1)
        endCol = N;
    for(unsigned i = startCol; i < endCol; i++)
        dataB[threadIdx.x*N+i] = B[col*N + i];
    __syncthreads();

    //----- Calculate partial result -----//
    if(row < N && col < N)
    {
        double dot = 0;
        for(unsigned i = 0; i < N; i++)
            dot += dataA[threadIdx.y*N + i] * dataB[threadIdx.x*N + i];
        C[row*N + col] = dot;
    }
}

__global__ 
void multiSlow(double *A, double* B, double *C, int N, int blockSize)
{
    int row = blockIdx.y*blockDim.y + threadIdx.y;
    int col = blockIdx.x*blockDim.x + threadIdx.x;

    //----- Calculate partial result -----//
    if(row < N && col < N)
    {
        double dot = 0;
        for(unsigned i = 0; i < N; i++)
            dot += A[row*N + i] * B[col*N + i];
        C[row*N + col] = dot;
    }
}

int main(int argc, char **argv)
{
    // Declare matrices
    double *mA_h, *mBt_h, *mC_h, *mA_d, *mBt_d, *mC_d; 
    unsigned N, i, j; 

    // Read matrix dimensions
    fscanf(stdin,"%d\n",&N); 

    // Allocate matrices
    mA_h = (double*)malloc(N*N*sizeof(double));
    mBt_h = (double*)malloc(N*N*sizeof(double));// B transposed
    mC_h = (double*)malloc(N*N*sizeof(double));
    cudaMalloc(&mA_d, N*N*sizeof(double));
    cudaMalloc(&mBt_d, N*N*sizeof(double));
    cudaMalloc(&mC_d, N*N*sizeof(double));

    // Read matrices
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            fscanf(stdin, "%lf ", &mA_h[i*N + j]);
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            fscanf(stdin, "%lf ", &mBt_h[j*N + i]);

    // Copy to GPU
    cudaMemcpy(mA_d, mA_h, N*N*sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(mBt_d, mBt_h, N*N*sizeof(double), cudaMemcpyHostToDevice);

    // Calculate block size
    cudaDeviceProp prop;
    int device;
    cudaGetDevice(&device);
    cudaGetDeviceProperties(&prop, device);

    // Solve C=A*B
    // Calculate block size, should not be greater than 16x16 (256 threads)
    // If N is less than 16, use N
    // If maximum shared mememory per block is not enough, use maximum block size possible
    int blockSize = min(
            unsigned(min(16, N)),
            unsigned(prop.sharedMemPerBlock/(N*2*sizeof(double))));

    if(blockSize > 0)
    {
        // Multiply using shared memory to cache block values
        dim3 gridDim = dim3((N+blockSize-1)/blockSize, (N+blockSize-1)/blockSize, 1);
        dim3 blockDim = dim3(blockSize, blockSize, 1);
        multiFast<<<gridDim, blockDim, blockSize*N*2*sizeof(double)>>>(mA_d, mBt_d, mC_d, N, blockSize);
    }
    else
    {
        // Multiply without using shared memory if the matrix is too big
        dim3 gridDim = dim3((N+15)/16, (N+15)/16, 1);
        dim3 blockDim = dim3(16, 16, 1);
        multiSlow<<<gridDim, blockDim>>>(mA_d, mBt_d, mC_d, N, 16);
    }

    cudaMemcpy(mC_h, mC_d, N*N*sizeof(double), cudaMemcpyDeviceToHost);

    // Show result
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            printf("%.1lf ", mC_h[i*N+j]);
        printf("\n");
    }

    // Deallocate matrices
    free(mA_h);
    free(mBt_h);
    free(mC_h);
    cudaFree(mA_d);
    cudaFree(mBt_d);
    cudaFree(mC_d);

    return 0;
}
