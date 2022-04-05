#ifndef BOX_H
#define BOX_H

#include "common.h"

Box** init_boxes();
void update_box(Box* box, int number);
void solve_box(Sudoku* sudoku, Box* box, int number);
int check_boxes(Sudoku* sudoku);

#endif
