#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#define SIZE 100			/* Max Size of matrices */

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
      printf("%5d ", m[i][j]);
    printf("|");
  }
}

int main(int argc, char *argv[])
{
  clock_t inicio, fim;
  double duracao;
  // FILE *saida;

  fill_matrix(A);
  fill_matrix(B);

  inicio = clock();
  for (int i=0; i<SIZE; i++){
    for (int j=0; j<SIZE; j++) {
      C[i][j]=0;
      for (int k=0; k<SIZE; k++)
	      C[i][j] += A[i][k]*B[k][j];
    }
  }
  fim = clock();

  // print_matrix(C);

  duracao = (double)(fim - inicio) / CLOCKS_PER_SEC;

  // saida = fopen("serial.dat", "a");
  // fprintf(saida, "%.5f\n", duracao);
  // fclose(saida);
  printf("%.5f\n", duracao);

  return 0;
}
