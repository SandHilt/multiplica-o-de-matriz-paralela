#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 4

int main(int argc, char *argv[])
{
    int rank, numtasks, i, j, info;
    int **param, **sub_param;
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    info = SIZE / numtasks;

    param = (int **)calloc(SIZE, sizeof(int *));
    sub_param = (int **)calloc(SIZE, sizeof(int *));

    for (i = 0; i < SIZE; i++)
    {
        param[i] = (int *)calloc(SIZE, sizeof(int));
        sub_param[i] = (int *)calloc(SIZE, sizeof(int));

        if (rank == 0)
        {
            for (j = 0; j < SIZE; j++)
            {
                param[i][j] = j + i * SIZE;
                printf(" %2d", param[i][j]);
            }
            printf("\n");
        }
    }

    for (i = 0; i < SIZE; i++)
        MPI_Scatter(param[i], info, MPI_INT, sub_param[i], info, MPI_INT, 0, MPI_COMM_WORLD);

    printf("rank %d sub_param is:", rank);
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < info; j++)
            printf(" %2d", sub_param[i][j]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}
