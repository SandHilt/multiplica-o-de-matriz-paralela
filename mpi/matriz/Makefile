CC=mpicc

FLAGS=

all: clean main serial

main: paralelo.c
	$(CC) $(FLAGS) paralelo.c -o paralelo.out

serial: serial.c
	gcc $(FLAGS) serial.c -o serial.out

clean:
	rm -rf *.out *.dat