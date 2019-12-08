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
#include <mpi.h>
typedef unsigned char cell_t;

#define TAG_READ 1
#define TAG_WRITE 2

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
	int *inmsg = (int *)malloc(3 * sizeof(int));
	int dest = 0;

	int i, j, a;

	/* for each cell, apply the rules of Life */
	for (i = 0; i < size; i++)
		for (j = rank; j < size; j += numtasks)
		{
			MPI_Send(inmsg, 3, MPI_INT, dest, TAG_READ, MPI_COMM_WORLD);

			a = adjacent_to(board, size, i, j);
			if (a == 2)
				newboard[i][j] = board[i][j];
			if (a == 3)
				newboard[i][j] = 1;
			if (a < 2)
				newboard[i][j] = 0;
			if (a > 3)
				newboard[i][j] = 0;
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

void syncro(cell_t **A, int size)
{
	for (int i = 0; i < size; i++)
	{
		MPI_Bcast(A[i], 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	}
}

int main(int argc, char **argv)
{
	double inicio, fim;
	int numtasks, rank;
	int *inmsg, *outmsg;

	int i, size, steps;
	cell_t **prev, **next, **tmp;

#ifdef DEBUG
	printf("Initial \n");
	print(prev, size);
	printf("----------\n");
#endif
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (numtasks < 2)
	{
		MPI_Abort(MPI_COMM_WORLD, MPI_ERR_SIZE);
	}

	if (rank == 0)
	{
		FILE *f = stdin;
		fscanf(f, "%d %d", &size, &steps);
		prev = allocate_board(size);
		read_file(f, prev, size);
		fclose(f);
		next = allocate_board(size);
		inicio = MPI_Wtime();
	}

	for (i = 0; i < steps; i++)
	{
		if (rank == 0)
		{
			// MPI_Recv();
		}
		else
		{
			play(prev, next, size, rank, numtasks);
		}
		/*
		 * Rank 0 precisa sincronizar as matrizes
		 * */
#ifdef DEBUG
		printf("%d ----------\n", i);
		print(next, size);
#endif
		if (rank == 0)
		{
			tmp = next;
			next = prev;
			prev = tmp;
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
