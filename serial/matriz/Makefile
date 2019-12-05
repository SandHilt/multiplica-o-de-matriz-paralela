CC=gcc

FLAGS=

all: main

main: serial.c
	$(CC) $(FLAGS) serial.c -DSIZE=${SIZE} -o serial.out

clean:
	rm -rf *.out