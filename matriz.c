#include <stdio.h>
#include <omp.h>

#define SIZE 2000 /* Max Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
double inicio, fim;

void fill_matrix(int m[SIZE][SIZE])
{
  static int n=0;

  for (int i=0; i<SIZE; i++)
    for (int j=0; j<SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  for (int i=0; i<SIZE; i++) {
    printf("\n\t| ");
    for (int j=0; j<SIZE; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
  const int T = 4;
  int i, j, k;

  fill_matrix(A);
  fill_matrix(B);

  inicio = omp_get_wtime();

  #pragma omp parallel for num_threads(T) private(i, j, k) schedule(dynamic, 1)
  for (i=0; i<SIZE; i++) 
    for (j=0; j<SIZE; j++) {
      C[i][j]=0;
      for (k=0; k<SIZE; k++)
	      C[i][j] += A[i][k]*B[k][j];
    }

  fim = omp_get_wtime();
  // print_matrix(C);
  
  printf("\nO tempo foi de %.5fs.\n", fim - inicio);

  return 0;
}
