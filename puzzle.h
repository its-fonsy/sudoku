#ifndef PUZZLE_H
#define PUZZLE_H

#include "common.h"
#include "box.h"
#include "cell.h"


int** generate_puzzle();
Sudoku* init_sudoku(int** puzzle);
void print_sudoku(Sudoku* sudoku);
void update_sudoku(Sudoku* sudoku, Cell* cell);
int check_solvable(Sudoku* sudoku);

#endif
