#include <stdio.h>
#include <omp.h>

#define N 5

void main(int argc, char **argv)
{
    int F[N];
    double inicio, fim, duracao;

    int i, j;
    int sum;

    F[0] = 1;
    F[1] = 1;
    sum = 0;

    inicio = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section private(i)
        {
            for(i = 2; i < N; i++)
            {
                F[i] = F[i - 2] + F[i - 1];
            }
        }
        #pragma omp section private(j)
        {
            #pragma parallel for reduction(+:sum)
            for(j = 0; j < N; j++)
            {
                sum += F[j];
            }
        }
    }
    fim = omp_get_wtime();
    duracao = fim - inicio;

    printf("%.5f\n", duracao);

}