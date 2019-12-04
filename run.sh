#!/bin/bash
echo "Script esta rodando...";
for i in {1..30}
do
    printf '%s\n' --------------------;
    echo "Teste $i"
    echo "Rodando o serial";
    ./serial/matriz/serial.out >> ./serial.dat;
    echo "Rodando o MPI com 2 CPUS";
    mpirun -np 2 ./mpi/matriz/matriz.out >> ./mpi_2.dat;
    echo "Rodando o MPI com 4 CPUS";
    mpirun --use-hwthread-cpus -np 4 ./mpi/matriz/matriz.out >> ./mpi_4.dat;
done
printf '%s\n' --------------------;
echo "🍺 Rodei todos os testes";