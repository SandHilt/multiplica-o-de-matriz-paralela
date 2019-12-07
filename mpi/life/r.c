#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 3

void main(int argc, char **argv)
{
    int source, dest, tag;
    int *inmsg, *outmsg;

    int i, j, rank, numtasks;
    int **buffer;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks < 2)
        MPI_Abort(MPI_COMM_WORLD, MPI_ERR_UNKNOWN);

    if (rank == 0)
    {
        MPI_Status status;
        inmsg = (int *)malloc(SIZE * sizeof(int));
        buffer = (int **)malloc(SIZE * sizeof(int));

        for (i = 0; i < SIZE; i++)
            buffer[i] = (int *)malloc(SIZE * sizeof(int));

        for (i = 0; i < SIZE * (numtasks - 1); i++)
        {
            MPI_Recv(inmsg, 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            buffer[inmsg[1]][inmsg[2]] = inmsg[0];
        }
        free(inmsg);
    }
    else
    {
        tag = rank;
        dest = 0;
        outmsg = (int *)malloc(3 * sizeof(3));

        for (i = 0; i < SIZE; i++)
            for (j = rank - 1; j < SIZE; j += numtasks - 1)
            {
            //    buffer[i][j] = i + j;
                outmsg[0] = i + j;
                outmsg[1] = i;
                outmsg[2] = j;
                MPI_Send(outmsg, 3, MPI_INT, dest, tag, MPI_COMM_WORLD);
            }

        free(outmsg);
    }

    if (rank == 0)
    {
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                printf("B[%d,%d]=%d\n", i, j, buffer[i][j]);
    }

    MPI_Finalize();
}
