#!/bin/bash
echo "Script esta rodando...";
for i in $(eval echo {1.."$1"})
do
    printf '%s\n' --------------------;
    echo "Teste $i"
    echo "Rodando o serial";
    ./serial/matriz/serial.out >> ./matriz_serial.dat;
    
    for i in 2 4
    do
        echo "Rodando o MPI com $i CPUS";
        mpirun --use-hwthread-cpus -np $i ./mpi/matriz/matriz.out >> ./matriz_mpi_$i.dat;
        echo "Rodando o OMP com $i CPUS";
        ./omp/matriz/matriz.out $i >> ./matriz_omp_$i.dat
    done
done
printf '%s\n' --------------------;
echo "🍺 Rodei todos os testes";

printf '%s\n' --------------------;
echo "Rodando estatisticas"
./env/bin/python stats.py $2