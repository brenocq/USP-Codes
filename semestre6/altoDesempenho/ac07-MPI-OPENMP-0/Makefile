all:
	mpicc fonte.c -lm -fopenmp -o multi -Wall

run: all
	mpirun -np 9 --oversubscribe multi
