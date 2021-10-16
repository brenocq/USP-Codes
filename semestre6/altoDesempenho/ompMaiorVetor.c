//g++ ompMaiorVetor.c -o a -fopenmp && ./a
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <climits>

#define PARALLEL// Comentar essa linha para executar o código sequencial
#define T 1
#define N 30000000

int main()
{
	int* vec;
	vec = (int*) malloc(N*sizeof(int)); //Aloca o vetor da dimensão lida

	for(int i=0; i<N; i++)
	{
		vec[i] = 1;
	}
	vec[N/2] = N/2;

    int num_threads;
	int maximum = INT_MIN;

    double wtime = omp_get_wtime();
#ifdef PARALLEL
	#pragma omp parallel num_threads(T) shared(maximum)
	{
		// determina o nr de threads
		num_threads = omp_get_num_threads();
		// determina o nr da thread
		int t = omp_get_thread_num();

		int start = t*N/T;
		int end = t<T-1 ? t*N/T+N/T : N;

		int maxLocal = vec[start];
		#pragma omp for
		for(int i = start; i < end; i++)
			if(vec[i] > maxLocal)
				maxLocal = vec[i];

		#pragma omp barrier
		if(maxLocal > maximum)
			maximum = maxLocal;
	}
#else
	num_threads = 1;
	for(int i = 0; i < N; i++)
		if(vec[i] > maximum)
			maximum = vec[i];
#endif
    wtime = omp_get_wtime() - wtime;
    printf("OMP Vet Maior Local: Tam=%d, Num_Threads=%d, maximum=%d, Elapsed wall clock time = %f \n", N, num_threads, maximum, wtime); //Imprime o vetor ordenado
    free(vec);

	//---------- Meus resultados ----------//
	// Ts -> 0.0435
	// 1 thread -> 0.042
	// 2 threads -> 0.011
	// 4 threads -> 0.0029
	// 16 threads -> 0.00062

	// Super-linear? why?
	// S2 = 3.86
	// S4 = 14.65
	// S16 = 68.54
	return 0;
}
