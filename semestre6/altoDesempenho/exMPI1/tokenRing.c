// mpicc tokenRing.c -o tokenRing -Wall && mpirun -np 8 tokenRing
#include <stdio.h>
#include "mpi.h"

#define RING_SIZE 8

int main(int argc, char *argv[])  
{
	int numProc, procRank, source, destination, ret;
	int dataReceived, dataToSend;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    destination = (procRank+1)%RING_SIZE;
    source = (procRank-1+RING_SIZE)%RING_SIZE;

	if(procRank == 0) 
	{
		printf("I'm the master. Sending %d to process %d.\n", dataToSend, destination);
        dataToSend = 0;
		MPI_Send(&dataToSend, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
	}
	else 
    {
		MPI_Recv(&dataReceived, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
        dataToSend = dataReceived+1;
		printf("Process %d received %d, sending %d to process %d.\n", procRank, dataReceived, dataToSend, destination);
		MPI_Send(&dataToSend, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
	} 
	fflush(0);

	ret = MPI_Finalize();
	if (ret == MPI_SUCCESS)
		printf("MPI_Finalize success! \n");

    return 0;
}
