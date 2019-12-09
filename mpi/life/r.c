#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 10

void alloc(int **p, int size)
{
    p = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        p[i] = (int *)calloc(size, sizeof(int));
}

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
    sub_param = (int **)calloc(info, sizeof(int *));

    for (i = 0; i < SIZE; i++)
    {
        param[i] = (int *)calloc(SIZE, sizeof(int));
        sub_param[i] = (int *)calloc(SIZE, sizeof(int));
    }

    if (rank == 0)
    {
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
            {
                param[i][j] = i + j * SIZE;
            }
    }

    for (i = 0; i < info; i++)
        MPI_Scatter(param[i], info, MPI_INT, sub_param[i], info, MPI_INT, 0, MPI_COMM_WORLD);

    printf("P:%d sub_param is:", rank);
    for (i = 0; i < info; i++)
        for (j = 0; j < info; j++)
            printf(" %2d", sub_param[i][j]);
    printf("\n");
    MPI_Finalize();
    return 0;
}
