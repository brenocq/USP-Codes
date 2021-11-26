// SSC0903 - Computação de Alto Desempenho
// AC09 - Valor minimo de matrizes quadradas com CUDA
//
// Breno Cunha Queiroz
// Matheus Branco Borella
// Natan Bernardi Cerdeira

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Kernel to find the minimum
__global__ void findMinimum(int *mat, unsigned L, unsigned C, int* res)
{
    // Threads on the same block find the minimum using the shared memory
    extern __shared__ int shd[];
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    // Calculate how many value to minimize in this block
    int blockSize = blockDim.x;
    if(blockIdx.x == gridDim.x-1);
        blockSize = (L*C) % blockDim.x;
 
    if(idx < L*C)
    {
        // Load from global memory to shared memory;
        shd[threadIdx.x] = mat[idx];
        __syncthreads();

        // Similar to merge sort, every iteration reduce by half the number of elements to find the minimum
        for(int it = 1; blockSize/it > 0; it*=2)
        {
            if(threadIdx.x < ceil(blockSize/float(it)))
            {
                // Calculate partial minimum
                if(threadIdx.x*it*2 + it < blockSize)
                    shd[threadIdx.x*it*2] = min(shd[threadIdx.x*it*2], shd[threadIdx.x*it*2 + it]);
            }

            // Wait all threads finish their work
            __syncthreads();
        }

        // Thread 0 updates the global result
        if(threadIdx.x == 0)
            atomicMin(res, shd[0]);
    }
}


int main()
{
    // Declarations
    int *A_h, *B_h, *A_d, *B_d, *resA_d, *resB_d;
    int resA_h = INT_MAX, resB_h = INT_MAX;
    unsigned L1, C1, L2, C2, i, j; 
    cudaStream_t stream1, stream2;

    // Read matrix dimensions
    fscanf(stdin,"%d %d\n%d %d", &L1, &C1, &L2, &C2); 

    // Allocate matrices
    A_h = (int*)malloc(L1*C1*sizeof(int));
    B_h = (int*)malloc(L2*C2*sizeof(int));
    cudaMalloc(&A_d, L2*C2*sizeof(int));
    cudaMalloc(&B_d, L2*C2*sizeof(int));
    cudaMalloc(&resA_d, sizeof(int));
    cudaMalloc(&resB_d, sizeof(int));

    // Read matrices
    for(i = 0; i < L1; i++)
        for(j = 0; j < C1; j++)
            fscanf(stdin, "%d", &A_h[i*C1+j]);
    for(i = 0; i < L2; i++)
        for(j = 0; j < C2; j++)
            fscanf(stdin, "%d", &B_h[i*C2+j]);

    // Create streams
    cudaStreamCreate(&stream1);
    cudaStreamCreate(&stream2);

    //----- Run kernels -----//
    // Copy from CPU to GPU
    cudaMemcpyAsync(resA_d, &resA_h, sizeof(int), cudaMemcpyHostToDevice, stream1);
    cudaMemcpyAsync(A_d, A_h, L1*C1*sizeof(int), cudaMemcpyHostToDevice, stream1);
    cudaMemcpyAsync(resB_d, &resB_h, sizeof(int), cudaMemcpyHostToDevice, stream2);
    cudaMemcpyAsync(B_d, B_h, L2*C2*sizeof(int), cudaMemcpyHostToDevice, stream2);

    // Run kernels
    findMinimum<<<(L1*C1+511)/512, 512, 512*sizeof(int), stream1>>>(A_d, L1, C1, resA_d);
    findMinimum<<<(L2*C2+511)/512, 512, 512*sizeof(int), stream2>>>(B_d, L2, C2, resB_d);

    // Synchronize
    cudaStreamSynchronize(stream1);
    cudaStreamSynchronize(stream2);

    // Copy result from GPU to CPU
    cudaMemcpyAsync(&resA_h, resA_d, sizeof(int), cudaMemcpyDeviceToHost, stream1);
    cudaMemcpyAsync(&resB_h, resB_d, sizeof(int), cudaMemcpyDeviceToHost, stream2);

    // Print result
    fprintf(stdout, "%d\n%d", resA_h, resB_h);

    // Deallocate
    free(A_h);
    free(B_h);
    cudaFree(A_d);
    cudaFree(B_d);
    cudaFree(resA_d);
    cudaFree(resB_d);
    cudaStreamDestroy(stream1);
    cudaStreamDestroy(stream2);

    return 0;
}
