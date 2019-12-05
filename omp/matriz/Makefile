CC=gcc

FLAGS=-fopenmp -O3

all: matriz

matriz: matriz.c
	$(CC) $(FLAGS) matriz.c -DSIZE=${SIZE} -o matriz.out

clean:
	rm -rf *.out
