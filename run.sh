#!/bin/bash

for i in {1...30}
do
    ./serial/matriz/serial.out >> ./serial.dat;
    # mpirun -np 2 ./mpi/matriz/matriz.out 1> ./mpi_2.dat;
    # mpirun --use-hwthread-cpus -np 4 ./mpi/matriz/matriz.out 1> ./mpi_2.dat;
done