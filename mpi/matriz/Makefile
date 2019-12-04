CC=mpicc

FLAGS=

all: clean main serial

main: matriz.c
	$(CC) $(FLAGS) matriz.c -o matriz.out

serial: serial.c
	gcc $(FLAGS) serial.c -o serial.out

clean:
	rm -rf *.out *.dat