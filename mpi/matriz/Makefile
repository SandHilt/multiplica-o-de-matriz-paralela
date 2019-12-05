CC=mpicc

FLAGS=

all: main

main: matriz.c
	$(CC) $(FLAGS) matriz.c -DSIZE=${SIZE} -o matriz.out

clean:
	rm -rf *.out