#include "box.h"
#include "cell.h"
#include "puzzle.h"

Box** init_boxes() {
	int i,j;
	Box** boxes;
	boxes = (Box**) malloc( sizeof(Box*)*9 );
	for (i = 0; i < 9; i++) {
		boxes[i] = (Box*) malloc( sizeof(Box) );
		boxes[i]->possible = BOX_UNSOLVED;
		boxes[i]->cells = (Cell**) malloc( sizeof(Cell*)*9 );
	}
	return boxes;
}

void update_box(Box* box, int number) {
	int i;
	Cell* cell;

	remove_entry(box->possible, number);

	for (i = 0; i < 9; i++) {
		cell = box->cells[i];
		if( possible_entry(cell->possible_entries, number) ) {
			remove_entry(cell->possible_entries, number);
			cell->n_possible_entries--;
			if(DEBUG)
				printf("BOX: for cell (%d,%d) remove entry %d\n",
						cell->x+1, cell->y+1, number);
		}
	}
}

int check_boxes(Sudoku* sudoku) {
	int i,j,k;
	int count;
	Box** boxes = sudoku->boxes;

	/* loop throught boxes */
	for(i=0; i<9; i++) {

		/* loop throught numbers */
		for(j=0; j<9; j++) {
			count = 0;

			/* if(i == 7 && j == 1) */
			/* 	printf("This box has %x possible\n", boxes[i]->possible); */

			/* skip already solved numbers */ 
			if( !(possible_entry(boxes[i]->possible, j+1)) )
				continue;


			/* loop throught cells */
			for(k=0; k<9; k++)
				if(possible_entry(boxes[i]->cells[k]->possible_entries, j+1))
					count++;


			/* solve cell with one possible solution*/
			if(count == 1) {
				solve_box(sudoku, boxes[i], j+1);
				return 1;
			}
		}
	}

	return 0;
}

void solve_box(Sudoku* sudoku, Box* box, int number) {
	int i;

	/* loop throught cells */
	for(i=0; i<9; i++)
		if( possible_entry(box->cells[i]->possible_entries, number) ) {
			solve_cell(sudoku, box->cells[i], number);
			update_sudoku(sudoku, box->cells[i]);
			break;
		}
}
