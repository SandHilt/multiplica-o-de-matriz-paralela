#include <stdio.h>
#include <time.h>

#define N 2000

void main(int argc, char **argv)
{
    int F[N];
    clock_t inicio, fim;
    double duracao;

    int i, j;
    int sum;

    F[0] = 1;
    F[1] = 1;
    sum = 0;

    inicio = clock();

    for (i = 2; i < N; i++)
    {
        F[i] = F[i - 2] + F[i - 1];
    }
    for (j = 0; j < N; j++)
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