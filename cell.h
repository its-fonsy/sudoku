#ifndef CELL_H
#define CELL_H

#include "puzzle.h"

Cell*** init_cells();
void update_raw(Sudoku* sudoku, int raw, int number);
void update_col(Sudoku* sudoku, int col, int number);
void solve_cell(Sudoku* sudoku, Cell* cell, int number);
int check_cells(Sudoku* sudoku);
int check_raw(Sudoku* sudoku);
int check_col(Sudoku* sudoku);

#endif
