#include "sudoku.h"

int main()
{

	printf("\n.dP\"Y8 88   88 8888b.   dP\"Yb  88  dP 88   88  \n");
	printf("`Ybo.\" 88   88  8I  Yb dP   Yb 88odP  88   88   \n");
	printf("o.`Y8b Y8   8P  8I  dY Yb   dP 88\"Yb  Y8   8P   \n");
	printf("8bodP' `YbodP' 8888Y\"   YbodP  88  Yb `YbodP'   \n");
	printf(".dP\"Y8  dP\"Yb  88     Yb    dP 888888 88\"\"Yb \n");
	printf("`Ybo.\" dP   Yb 88      Yb  dP  88__   88__dP    \n");
	printf("o.`Y8b Yb   dP 88  .o   YbdP   88\"\"   88\"Yb   \n");
	printf("8bodP'  YbodP  88ood8    YP    888888 88  Yb     \n\n");

	int** puzzle;
	int progress = 1;
	puzzle = generate_puzzle();
	Sudoku* sudoku;
	sudoku = init_sudoku(puzzle);

	print_sudoku(sudoku);
	while(progress){
		progress = check_solvable(sudoku);
	}

	if(sudoku->cell_unsolved != 0)
		printf("\nCan't solve this sudoku :(\n");
	else
		printf("\nYay solved :D\n");

	print_sudoku(sudoku);

	return 0;
}
