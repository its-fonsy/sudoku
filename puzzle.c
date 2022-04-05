#include <stdlib.h>
#include <stdio.h>

#include "puzzle.h"

int**
generate_puzzle() {

	int dummy_puzzle[9][9] = {
		{0, 0, 5,	0, 0, 0,	0, 0, 0},
		{0, 0, 2,	4, 0, 1,	0, 7, 0},
		{3, 0, 4,	0, 0, 0,	5, 6, 0},

		{0, 0, 0,	0, 0, 0,	0, 0, 0},
		{0, 0, 0,	0, 0, 7,	9, 8, 4},
		{8, 0, 0,	0, 9, 0,	0, 1, 0},

		{0, 0, 0,	2, 0, 0,	1, 0, 0},
		{0, 9, 0,	0, 7, 0,	0, 0, 2},
		{0, 1, 8,	3, 0, 0,	0, 4, 0}
	};

	int **puzzle;
	puzzle = (int**) malloc( sizeof(int*) * 9 );

	for(int i=0; i < 9; i++) {
		puzzle[i] = (int*) malloc( sizeof(int) * 9 );

		for (int j = 0; j < 9; j++)
			puzzle[i][j] = dummy_puzzle[i][j];
	}

	return puzzle;
}

void print_sudoku(Sudoku* sudoku) {

	int n;

	printf("+---------+---------+---------+\n");
	for (int i = 0; i < 9; i++) {
		printf("|");

		for (int j = 0; j < 9; j++) {
			n = sudoku->cells[i][j]->number;
			printf(" %c ", (n == 0) ? '-' : n+48);

			if( ((j+1) % 3) == 0 )
				printf("|");
		}

		if( ((i+1) % 3) == 0 )
			printf("\n+---------+---------+---------+\n");
		else
			printf("\n");
	}
}

Sudoku* init_sudoku(int** puzzle) {
	int i, j;
	int current_box = 0;
	int current_box_cell = 0;

	Sudoku* sudoku = (Sudoku*) malloc(sizeof(Sudoku));

	Cell*** cells = init_cells();
	Box** boxes = init_boxes();

	sudoku->cell_unsolved = 81;
	sudoku->cells = cells;
	sudoku->boxes = boxes;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {

			cells[i][j]->number = puzzle[i][j]; 
			cells[i][j]->box = boxes[current_box]; 

			boxes[current_box]->cells[current_box_cell] = cells[i][j];
			current_box_cell++;

			if( puzzle[i][j] != 0 ) {
				cells[i][j]->possible_entries = CELL_SOLVED;
				cells[i][j]->n_possible_entries = 0;
				sudoku->cell_unsolved--;
			}

			if(j == 2 || j == 5) {
				current_box++;
				current_box_cell -= 3;
			}
		}

		current_box -= 2;
		if(i == 2 || i == 5) {
			current_box_cell = 0;
			current_box += 3;
		}
	}

	for(i=0; i<9; i++)
		for(j=0; j<9; j++)
			if(cells[i][j]->number != 0)
				update_sudoku(sudoku, cells[i][j]);

	return sudoku;
}

void update_sudoku(Sudoku* sudoku, Cell* cell) {

	update_raw(sudoku, cell->y, cell->number);
	update_col(sudoku, cell->x, cell->number);
	update_box(cell->box, cell->number);

}

int check_solvable(Sudoku* sudoku) {

	if( check_cells(sudoku) )
		return 1;

	if( check_boxes(sudoku) )
		return 1;

	if( check_raw(sudoku) )
		return 1;

	if( check_col(sudoku) )
		return 1;

	return 0;
}
