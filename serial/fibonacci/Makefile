CC=gcc

FLAGS=-DSIZE_F=${SIZE_F}

all: fibonacci

fibonacci: fibonacci.c
	$(CC) $(FLAGS) fibonacci.c -o fibonacci.out

clean:
	rm -rf *.out *.dat
