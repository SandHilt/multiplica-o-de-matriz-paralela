#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 4			/* Max Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void fill_matrix(int m[SIZE][SIZE])
{
  static int n=0;
  int i, j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  int i, j = 0;
  for (i=0; i<SIZE; i++) {
    printf("\n\t| ");
    for (j=0; j<SIZE; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
  int numtasks, rank, dest, source, tag = 1;
  int inmsg, outmsg;

  double start, end;

  MPI_Status State;

  FILE *saida = fopen('./saida.dat', 'w');

  fill_matrix(A);
  fill_matrix(B);

  for (int i=0; i<SIZE; i++) 
    for (int j=0; j<SIZE; j++) {
      MPI_Init(&argc, &argv);

      MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      if(rank == 0) {
        int sum = 0;
        
        source = MPI_ANY_SOURCE;
        tag = MPI_ANY_TAG;

        start = MPI_Wtime();
        for(int i = 0; i < numtasks - 1; i++){

        }
      } else {
        dest = 0;
        tag = rank;

        // TODO: loop de um inicio ate uma certa parte
        // for(int i = 0; i < SIZE; i++) {
        // }

        }
      }
      if(rank == 0){
        end = MPI_Wtime();
        fprintf(saida, "%.5f", end - start);
      }

      // for (int k=0; k<SIZE; k++)
	    //   sum += A[i][k]*B[k][j];

      // C[i][j]=sum;

      MPI_Finalize();
    }

  fclose(saida);
  print_matrix(C);

  return 0;
}
