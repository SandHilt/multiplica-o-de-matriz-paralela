CC=gcc

FLAGS=

all: main

main: serial.c
	$(CC) $(FLAGS) serial.c -DSIZE=${SIZE} -o matriz.out

clean:
	rm -rf *.out