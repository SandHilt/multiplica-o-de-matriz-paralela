CC=gcc

FLAGS=-O3

all: main

main: serial.c
	$(CC) $(FLAGS) serial.c -DSIZE=${SIZE} -o serial.out

clean:
	rm -rf *.out