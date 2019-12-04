#include <stdio.h>
#include <omp.h>

#define SIZE 1000 /* Max Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
double inicio, fim;

void fill_matrix(int m[SIZE][SIZE])
{
  static int n = 0;

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    printf("\n\t| ");
    for (int j = 0; j < SIZE; j++)
      printf("%5d ", m[i][j]);
    printf("|");
  }
}

int main(int argc, char *argv[])
{
  const int T = 2;

  int i, j, k, sum;

  fill_matrix(A);
  fill_matrix(B);

  inicio = omp_get_wtime();

  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
    {
      sum = 0;

      #pragma omp parallel for num_threads(T) reduction(+:sum)
      for (k = 0; k < SIZE; k++)
        sum += A[i][k] * B[k][j];

      C[i][j] = sum;
    }

  fim = omp_get_wtime();
  // print_matrix(C);

  printf("%.5f\n", fim - inicio);

  return 0;
}
