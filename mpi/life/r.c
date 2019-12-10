#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 5

int main(int argc, char *argv[])
{
    int rank, numtasks, i, j, info, rest;
    int **param, **sub_param, *send;
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

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

    info = SIZE / numtasks;
    rest = 0;
    // send = (int *)calloc(numtasks, sizeof(int));

    // if (rank == 0)
    // {
    //     rest = SIZE % numtasks;

    //     for (i = 0; i < numtasks; i++)
    //         send[i] = info;

    //     if (rest)
    //         send[0] += rest;
    // }

    MPI_Bcast(send, numtasks, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < SIZE; i++)
        MPI_Scatter(param[i], info, MPI_INT, sub_param[i], info, MPI_INT, 0, MPI_COMM_WORLD);

    printf("rank %d sub_param is:", rank);
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < info + rest; j++)
            printf(" %2d", sub_param[i][j]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}
