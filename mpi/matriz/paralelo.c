#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define SIZE 4 /* Max Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void fill_matrix(int m[SIZE][SIZE])
{
  static int n = 0;
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  int i, j = 0;
  for (i = 0; i < SIZE; i++)
  {
    printf("\n\t| ");
    for (j = 0; j < SIZE; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}

int main(int argc, char *argv[])
{
  int numtasks, rank, dest, source, tag;
  int inmsg, outmsg;

  double start, end;

  FILE *saida = fopen("./saida.dat", "w");

  fill_matrix(A);
  fill_matrix(B);

  MPI_Status State;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0)
  {
    source = MPI_ANY_SOURCE;
    tag = MPI_ANY_TAG;

    start = MPI_Wtime();

    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        int sum = 0;
        for (int k = 0; k < SIZE; k++)
        {
          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &State);
          sum += inmsg;
          fprintf(saida, "Soma parcial %d com %d", sum, inmsg);
        }
        C[i][j] = sum;
      }
    }
  }
  else
  {
    dest = 0;
    source = 0;
    outmsg = 0;
    tag = rank;

    int part = (int)floor(SIZE / (numtasks - 1));

    int inicio_part = (rank - 1) * part;
    int fim_part = rank * part;

    for (int i = inicio_part; i < fim_part; i++)
    {
      for (int j = inicio_part; j < fim_part; j++)
      {

        for (int k = (rank - 1) * part; k < rank * part; k++)
        {
          outmsg = A[i][k] * B[k][j];
          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
        }

        MPI_Recv(&inmsg, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &State);
      }
    }
  }

  if (rank == 0)
  {
    end = MPI_Wtime();
    fprintf(saida, "%.5fs", end - start);
  }

  MPI_Finalize();
  fclose(saida);
  print_matrix(C);

  return 0;
}
