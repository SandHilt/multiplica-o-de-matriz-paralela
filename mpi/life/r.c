#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 10

int main(int argc, char *argv[])
{
    int rank, size, i;
    double *param, *sub_param;
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    param = (double *)malloc(size * SIZE * sizeof(double));
    if (rank == 0)
    {
        for (i = 0; i < size * SIZE; ++i)
        {
            param[i] = rand() % 2;
        }
    }
    else
    {
        sub_param = (double *)calloc(SIZE, sizeof(double));
    }

    MPI_Scatter(param, SIZE, MPI_DOUBLE, sub_param, SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("P:%d sub_param is: ", rank);
    for (i = 0; i < SIZE; i++)
        printf("%c ", sub_param[i] ? 'x' : '0');
    printf("\n");
    MPI_Finalize();
    return 0;
}
