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

cell_t **allocate_board(int size)
{
	cell_t **board = (cell_t **)calloc(size, sizeof(cell_t *));
	int i;
	for (i = 0; i < size; i++)
		board[i] = (cell_t *)calloc(size, sizeof(cell_t));
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

	for (k = sk; k <= ek; k++)
		for (l = sl; l <= el; l++)
			count += board[k][l];
	count -= board[i][j];

	return count;
}

void play(cell_t **board, cell_t **newboard, int size, int rank, int numtasks)
{
	int i, j, a;
	/* for each cell, apply the rules of Life */
	for (i = rank; i < size; i += numtasks)
		for (j = 0; j < size; j++)
		{
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

int main(int argc, char **argv)
{
	double inicio, fim;
	double duracao;
	int rank, numtasks, root = 0;

	int size, steps;
	cell_t **prev, **next, **tmp, *aux;
	int i, j, k, l;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == root)
	{
		FILE *f;
		f = stdin;
		fscanf(f, "%d %d", &size, &steps);
		prev = allocate_board(size);
		read_file(f, prev, size);
		fclose(f);
	}
#ifdef DEBUG
	printf("Initial \n");
	print(prev, size);
	printf("----------\n");
#endif

	MPI_Bcast(&size, 1, MPI_INT, root, MPI_COMM_WORLD);

	if (rank != root)
		prev = allocate_board(size);

	for (i = 0; i < size; i++)
		MPI_Bcast(prev[i], size, MPI_UNSIGNED_CHAR, root, MPI_COMM_WORLD);

	next = allocate_board(size);
	inicio = MPI_Wtime();
	for (i = 0; i < 1; i++)
	{

		play(prev, next, size, rank, numtasks);
#ifdef DEBUG
		printf("%d ----------\n", i);
		print(next, size);
#endif
		if (rank == 1)
			print(next, size);

		if (rank == root)
		{
			aux = (cell_t *)calloc(size, sizeof(cell_t));
			for (j = 0; j < size; j++)
			{
				MPI_Recv(aux, size, MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				printf("rank %d j=%d\n", status.MPI_SOURCE, status.MPI_TAG);

				if (status.MPI_TAG % numtasks == status.MPI_SOURCE)
					for (k = 0; k < size; k++)
					{
						next[status.MPI_TAG][k] = aux[k];
					}
			}
		}
		else
		{
			for (j = 0; j < size; j++)
			{
				printf("Enviando rank %d com j=%d\n", rank, j);
				MPI_Send(next[j], size, MPI_UNSIGNED_CHAR, 0, j, MPI_COMM_WORLD);
			}
		}

		MPI_Barrier(MPI_COMM_WORLD);
		if (rank == root)
			print(next, size);
		// 	tmp = next;
		// 	next = prev;
		// 	prev = tmp;
	}
	fim = MPI_Wtime();
	MPI_Finalize();
	duracao = fim - inicio;
	if (rank == root)
		printf("%.5f", duracao);
	// print(prev, size);
	free_board(prev, size);
	free_board(next, size);
}
