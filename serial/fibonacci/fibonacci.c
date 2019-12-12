#include <stdio.h>
#include <time.h>

#ifndef SIZE
#define SIZE 2000
#endif

void main(int argc, char **argv)
{
    int F[SIZE];
    clock_t inicio, fim;
    double duracao;

    int i, j;
    int sum;

    F[0] = 1;
    F[1] = 1;
    sum = 0;

    inicio = clock();

    for (i = 2; i < SIZE; i++)
    {
        F[i] = F[i - 2] + F[i - 1];
    }
    for (j = 0; j < SIZE; j++)
    {
        sum += F[j];
    }
    fim = clock();
    duracao = (double)(fim - inicio) / CLOCKS_PER_SEC;

#ifdef DEBUG
    printf("Soma dos %d termos de fibonacci eh %d\n", N, sum);
#endif
    printf("%.5f\n", duracao);
}