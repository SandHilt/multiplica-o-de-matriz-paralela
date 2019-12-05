/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbours 
 * a cell dies of loneliness, if it has less than two neighbours 
 * a cell dies of overcrowding, if it has more than three neighbours 
 * a cell survives to the next generation, if it does not die of loneliness 
 * or overcrowding 
 *
 * In this version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
 * The game plays a number of steps (given by the input), printing to the screen each time.  'x' printed
 * means on, space means off.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
typedef unsigned char cell_t;

cell_t **allocate_board(int size)
{
	cell_t **board = (cell_t **)malloc(sizeof(cell_t *) * size);
	int i;
	for (i = 0; i < size; i++)
		board[i] = (cell_t *)malloc(sizeof(cell_t) * size);
	return board;
}

void free_board(cell_t **board, int size)
{
	int i;
	for (i = 0; i < size; i++)
		free(board[i]);
	free(board);
}

/* return the number of on cells adjacent to the i,j cell */
int adjacent_to(cell_t **board, int size, int i, int j)
{
	int k, l, count = 0;

	int sk = (i > 0) ? i - 1 : i;
	int ek = (i + 1 < size) ? i + 1 : i;
	int sl = (j > 0) ? j - 1 : j;
	int el = (j + 1 < size) ? j + 1 : j;

	/**
	 * Pior caso 3 * 3 = 9
	 * */
	for (k = sk; k <= ek; k++)
		for (l = sl; l <= el; l++)
			count += board[k][l];
	count -= board[i][j];

	return count;
}

void play(cell_t **board, cell_t **newboard, int size, int rank, int numtasks)
{
	int *inmsg, *outmsg;
	int dest, source, tag = 2;
	MPI_Status state;

	int i, j, k, a;

	if (rank == 0)
	{
		FILE *s = fopen("./debug.dat", "a");

		source = MPI_ANY_SOURCE;
		inmsg = (int *)malloc(3 * sizeof(int));

		/* for each cell, apply the rules of Life */
		for (k = 0; k < size * size * (numtasks - 1); k++)
		{
			MPI_Recv(inmsg, 3, MPI_INT, source, tag, MPI_COMM_WORLD, &state);

			a = inmsg[0];
			i = inmsg[1];
			j = inmsg[2];

			if (a == 2)
			{
				newboard[i][j] = board[i][j];
			}
			else if (a == 3)
			{
				newboard[i][j] = 1;
			}
			else if (a < 2 || a > 3)
			{
				newboard[i][j] = 0;
			}

			fprintf(s, "rank=%d, a=%d, i=%d, j=%d\n", state.MPI_SOURCE, a, i, j);
		}
		fclose(s);
		free(inmsg);
	}
	else
	{
		dest = 0;
		outmsg = (int *)malloc(3 * sizeof(int));

		for (i = 0; i < size; i++)
		{
			for (j = rank - 1; j < size; j += numtasks - 1)
			{
				outmsg[0] = adjacent_to(board, size, i, j);
				outmsg[1] = i;
				outmsg[2] = j;
				MPI_Send(outmsg, 3, MPI_INT, dest, tag, MPI_COMM_WORLD);
			}
		}
		free(outmsg);
	}
}

/* print the life board */
void print(cell_t **board, int size)
{
	int i, j;
	/* for each row */
	for (j = 0; j < size; j++)
	{
		/* print each column position... */
		for (i = 0; i < size; i++)
			printf("%c", board[i][j] ? 'x' : ' ');
		/* followed by a carriage return */
		printf("\n");
	}
}

/* read a file into the life board */
void read_file(FILE *f, cell_t **board, int size)
{
	int i, j;
	char *s = (char *)malloc(size + 10);
	char c;
	for (j = 0; j < size; j++)
	{
		/* get a string */
		fgets(s, size + 10, f);
		/* copy the string to the life board */
		for (i = 0; i < size; i++)
		{
			//c=fgetc(f);
			//putchar(c);
			board[i][j] = s[i] == 'x';
		}
		//fscanf(f,"\n");
	}
}

int main(int argc, char **argv)
{
	double inicio, fim;
	int source, dest, numtasks, rank, tag = 1;
	bool insmsg, outmsg;
	MPI_Status state;

	int size, steps;
	FILE *f;
	f = stdin;
	fscanf(f, "%d %d", &size, &steps);
	cell_t **prev = allocate_board(size);
	read_file(f, prev, size);
	fclose(f);
	cell_t **next = allocate_board(size);
	cell_t **tmp;
	int i, j;
#ifdef DEBUG
	printf("Initial \n");
	print(prev, size);
	printf("----------\n");
#endif
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (numtasks < 2)
	{
		MPI_Abort(MPI_COMM_WORLD, MPI_ERR_SIZE);
	}

	if (rank == 0)
	{
		inicio = MPI_Wtime();
		outmsg = true;

		for (i = 0; i < steps; i++)
		{
			play(prev, next, size, rank, numtasks);
#ifdef DEBUG
			printf("%d ----------\n", i);
			print(next, size);
#endif
			tmp = next;
			next = prev;
			prev = tmp;
		}
	}
	else
	{
		source = 0;

		for (i = 0; i < steps; i++)
		{
			play(prev, next, size, rank, numtasks);
			MPI_Recv(&insmsg, 1, MPI_C_BOOL, source, tag, MPI_COMM_WORLD, &state);
		}
	}
	if (rank == 0)
	{
		fim = MPI_Wtime();
		printf("%.5f", fim - inicio);
	}
	MPI_Finalize();
	// print(prev, size);
	free_board(prev, size);
	free_board(next, size);
}
