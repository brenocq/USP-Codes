MPI_COMPILE_FLAGS = $(shell mpicc --showme:compile)
MPI_LINK_FLAGS = $(shell mpicc --showme:link)
CFLAGS=-fopenmp -O2 -g -rdynamic -Wall -Wextra -Werror

all: main.c
	$(CC) $(CFLAGS) $(MPI_COMPILE_FLAGS) main.c $(MPI_LINK_FLAGS) -o main

# 3 processes = 1 master + 2 workers, 6 threads per worker = ~12 cpu cores being used
run: all
	mpirun -np 3 --use-hwthread-cpus ./main
