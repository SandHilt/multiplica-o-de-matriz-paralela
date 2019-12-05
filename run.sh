#!/bin/bash
echo "Script esta rodando...";

for p in 'matriz'
do
    echo "Projeto $p"
    for i in $(eval echo {1.."$1"})
    do
        printf '%s\n' --------------------;
        echo "Teste $i"
        echo "Rodando o serial";
        ./serial/$(eval echo $p)/serial.out >> ./$(eval echo $p)_serial.dat;
        
        for i in 2 4
        do
            echo "Rodando o MPI com $i CPUS";
            mpirun --use-hwthread-cpus -np $i ./mpi/$(eval echo $p)/$(eval echo $p).out >> ./$(eval echo $p)_mpi_$i.dat;
            echo "Rodando o OMP com $i CPUS";
            ./omp/$(eval echo $p)/$(eval echo $p).out $i >> ./$(eval echo $p)_omp_$i.dat
        done
    done
done
printf '%s\n' --------------------;
echo "🍺 Rodei todos os testes";

printf '%s\n' --------------------;
echo "Rodando estatisticas"
./env/bin/python stats.py $2