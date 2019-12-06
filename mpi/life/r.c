#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 3

void main(int argc, char **argv)
{
    int i, j, rank;
    int **buffer = (int **)malloc(SIZE * sizeof(int));

    for (i = 0; i < SIZE; i++)
    {
        buffer[i] = (int *)malloc(SIZE * sizeof(int));
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                buffer[i][j] = i + j;
    }

    MPI_Bcast(&buffer, SIZE, MPI_INT, 0, MPI_COMM_WORLD);


    if (rank == 1)
    {
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                printf("B[%d,%d]=%d\n", i, j, buffer[i][j]);
    }

    MPI_Finalize();
}