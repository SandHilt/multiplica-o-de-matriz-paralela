#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 10

int main(int argc, char *argv[])
{
    int rank, size, i, j;
    int param[SIZE][SIZE], *sub_param;
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                param[i][j] = 10 * i + j;
                printf("B[%d,%d]=%d\n", i, j, param[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        sub_param = (int *)calloc(SIZE, sizeof(int));
    }

    MPI_Scatter(param, SIZE, MPI_INT, sub_param, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    printf("P:%d sub_param is:", rank);
    for (i = 0; i < SIZE; i++)
        printf(" %2d", sub_param[i]);
    printf("\n");
    MPI_Finalize();
    return 0;
}
