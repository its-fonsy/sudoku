#include "common.h"
#include "cell.h"

Cell*** init_cells() {
	int i,j;
	Cell*** cells = (Cell***) malloc( sizeof(Cell**) * 9 );
	for (i = 0; i < 9; i++) {
		cells[i] = (Cell**) malloc( sizeof(Cell*) * 9 );
		for (j = 0; j < 9; j++) {
			cells[i][j] = (Cell*) malloc( sizeof(Cell) * 9);

			cells[i][j]->x = j; 
			cells[i][j]->y = i; 
			cells[i][j]->number = 0;
			cells[i][j]->possible_entries = CELL_UNSOLVED;
			cells[i][j]->n_possible_entries = 9;
		}
	}
	return cells;
}

int check_cells(Sudoku* sudoku) {
	int i, j, k;

	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if( sudoku->cells[i][j]->n_possible_entries == 1) {

				// get the only number that can solve the cell
				for(k=0; k<9; k++)
					if(possible_entry(sudoku->cells[i][j]->possible_entries, k+1))
						break;

				if(DEBUG)
					printf("For cell (%d,%d) sol is %d\n", j+1, i+1, k+1);

				solve_cell(sudoku, sudoku->cells[i][j], k + 1);
				update_sudoku(sudoku, sudoku->cells[i][j]);
				return 1;
			}
	return 0;
}

void solve_cell(Sudoku* sudoku, Cell* cell, int number) {

	sudoku->cell_unsolved--;
	cell->n_possible_entries = 0;
	cell->number = number;
	cell->possible_entries = CELL_SOLVED;
	remove_entry(cell->box->possible, number);

}

void update_raw(Sudoku* sudoku, int raw, int number) {

	int i;
	Cell* cell;

	for (i = 0; i < 9; i++) {
		cell = sudoku->cells[raw][i];
		if( possible_entry(cell->possible_entries, number) ) {
			remove_entry(cell->possible_entries, number);
			cell->n_possible_entries--;
			if(DEBUG)
				printf("RAW: for cell (%d,%d) remove entry %d\n",
						i+1, cell->y+1, number);
		}
	}
}

void update_col(Sudoku* sudoku, int col, int number) {

	int i;
	Cell* cell;

	for (i = 0; i < 9; i++) {
		cell = sudoku->cells[i][col];
		if( possible_entry(cell->possible_entries, number) ) {
			remove_entry(cell->possible_entries, number);
			cell->n_possible_entries--;
			if(DEBUG)
				printf("COL: for cell (%d,%d) remove entry %d\n",
						i+1, cell->y+1, number);
		}
	}
}

int check_raw(Sudoku* sudoku) {
	int i, j, k;
	int count;
	Cell* cell;

	/* loop throught raws */
	for(i=0; i<9; i++) {

		/* loop throught numbers */
		for(j=0; j<9; j++) {
			count = 0;

			/* loop throught cells */
			for(k=0; k<9; k++)
				if(possible_entry(sudoku->cells[i][k]->possible_entries, j+1))
					count++;

			/* solve cell with one possible solution*/
			if(count == 1) {
				for(k=0; k<9; k++)
					if(possible_entry(sudoku->cells[i][k]->possible_entries, j+1))
						break;
				solve_cell(sudoku, sudoku->cells[i][k], j+1);
				update_sudoku(sudoku, sudoku->cells[i][k]);
				return 1;
			}
		}
	}

	return 0;
}

int check_col(Sudoku* sudoku) {

	int i, j, k;
	int count;

	/* loop throught cols */
	for(i=0; i<9; i++) {

		/* loop throught numbers */
		for(j=0; j<9; j++) {
			count = 0;

			/* loop throught cells */
			for(k=0; k<9; k++)
				if(possible_entry(sudoku->cells[k][i]->possible_entries, j+1))
					count++;

			/* solve cell with one possible solution*/
			if(count == 1) {
				for(k=0; k<9; k++)
					if(possible_entry(sudoku->cells[k][i]->possible_entries, j+1))
						break;
				solve_cell(sudoku, sudoku->cells[k][i], j+1);
				update_sudoku(sudoku, sudoku->cells[i][k]);
				return 1;
			}
		}
	}

	return 0;

}
