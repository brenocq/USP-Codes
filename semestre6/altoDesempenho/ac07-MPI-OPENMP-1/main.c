#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// Breno Cunha Queiroz     - 11218991
// Matheus Branco Borella  - 11218897
// Natan Bernardi Cerdeira - 11218984

#define N          (5)
#define NUMTHREADS (6)

#define TO_MASTER 0x11111111
#define TO_WORKER 0x22222222

void* alloc(size_t size) {
    void* v = calloc(1, size);
    if(!v) {
        fprintf(stderr, "Failed to allocate %zu bytes\n", size);
        abort();
    }
    return v;
}

void master(int worker_count) {
    int* matrix_a = alloc(sizeof(*matrix_a) * N * N);
    int* matrix_b = alloc(sizeof(*matrix_b) * N * N);

    srand(2021);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            matrix_a[i * N + j] = rand() % 10;
            matrix_b[i * N + j] = rand() % 10;
        }
    }

    double start = MPI_Wtime();

    //send matrix b to workers
    MPI_Bcast(matrix_b, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    free(matrix_b);

    int rows_per_worker = N / worker_count;
    int extra = N % worker_count;
    int* counts = alloc(sizeof(*counts) * (worker_count + 1));
    int* disps = alloc(sizeof(*counts) * (worker_count + 1));
    for(int i = 0; i <= worker_count; i++) {
        if(i == 0) {
            counts[i] = disps[i] = 0;
            continue;
        }
        int rows = rows_per_worker;
        if(i <= extra) rows++;
        counts[i] = rows * N;
        disps[i] = disps[i - 1] + counts[i - 1];
        MPI_Send(&rows, 1, MPI_INT, i, TO_WORKER, MPI_COMM_WORLD);
        //MPI_Send(&counts[i], 1, MPI_INT, i, TO_WORKER, MPI_COMM_WORLD);
    }

    MPI_Scatterv(matrix_a, counts, disps, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    free(matrix_a);

    int* matrix_c = alloc(sizeof(*matrix_c) * N * N);
    MPI_Gatherv(NULL, 0, MPI_INT, matrix_c, counts, disps, MPI_INT, 0, MPI_COMM_WORLD);
    
    free(counts);
    free(disps);

    double elapsed = MPI_Wtime() - start;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf(" %d", matrix_c[i * N + j]);
        }
        printf("\n");
    }
    fprintf(stderr, "Took %.3f seconds\n", elapsed);

    free(matrix_c);
}

void worker(int task_id) {
    (void)task_id;

    int* matrix_b = alloc(sizeof(*matrix_b) * N * N);
    MPI_Bcast(matrix_b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    int row_count;
    MPI_Status status;
    MPI_Recv(&row_count, 1, MPI_INT, 0, TO_WORKER, MPI_COMM_WORLD, &status);

    int* rows = alloc(sizeof(*rows) * N * row_count);

    MPI_Scatterv(NULL, NULL, NULL, MPI_INT, rows, N * row_count, MPI_INT, 0, MPI_COMM_WORLD);

    int* result = alloc(sizeof(*result) * N * row_count);
    #pragma omp parallel for shared(result, rows, matrix_b) num_threads(NUMTHREADS)
    for(int i = 0; i < row_count; i++) {
        for(int k = 0; k < N; k++) {
            int res = 0;
            for(int j = 0; j < N; j++) {
                res += rows[i * N + j] * matrix_b[j * N + k];
            }
            result[i * N + k] = res;
        }
    }
    free(rows);
    free(matrix_b);

    MPI_Gatherv(result, N * row_count, MPI_INT, NULL, NULL, NULL, MPI_INT, 0, MPI_COMM_WORLD);

    free(result);
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc,&argv);

    int task_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    int task_count;
    MPI_Comm_size(MPI_COMM_WORLD, &task_count);

    if(task_count < 2) {
        fprintf(stderr, "Needs at least 2 tasks\n");
        abort();
    }

    if(task_id == 0) {
        master(task_count - 1);
    } else {
        worker(task_id);
    }

    MPI_Finalize();
}

