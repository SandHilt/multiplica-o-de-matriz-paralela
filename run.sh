#!/bin/bash
echo "Script esta rodando...";

for p in fibonacci matriz
do
    echo "Projeto $p"
    for i in $(eval echo {1.."$1"})
    do
        printf '%s\n' --------------------;
        echo "Teste $i"
        echo "Rodando o serial";
        ./serial/$(eval echo $p)/$(eval echo $p).out >> ./$(eval echo $p)_serial.dat;
        
        for i in 2 4
        do
            if [ "$p" != 'fibonacci' ]
            then
                echo "Rodando o MPI com $i CPUS";
                mpirun --use-hwthread-cpus -np $i ./mpi/$(eval echo $p)/$(eval echo $p).out >> ./$(eval echo $p)_mpi_$i.dat;
            fi
            echo "Rodando o OMP com $i CPUS";
            ./omp/$(eval echo $p)/$(eval echo $p).out $i >> ./$(eval echo $p)_omp_$i.dat
        done
    done
done

echo "Projeto Life"
for i in $(eval echo {1.."$1"})
do 
    printf '%s\n' --------------------;
    echo "Teste $i"
    for j in life judge
    do
        ./serial/life/life.out < ./serial/life/"$j".in >> ./life_"$j"_serial.dat;

        for k in omp
        do
            for p in 2 4
            do
                echo "Rodando o $k com $p CPUS";
                ./$(eval echo $k)/life/life.out $p < ./"$k"/life/"$j".in >> ./life_"$j"_$(eval echo $k).dat;
            done
        done
    done
done

printf '%s\n' --------------------;
echo "🍺 Rodei todos os testes";

printf '%s\n' --------------------;
echo "Rodando estatisticas"
./env/bin/python stats.py $2