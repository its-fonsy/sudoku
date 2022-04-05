#ifndef COMMON_H
#define COMMON_H

/* How to check possible entry of a cell
 * 0000 0000 0000 0000   (uint16_t)
 * xxxx xxx9 8765 4321   (symbolic representation)
 *
 * A "0" means that is a possible entry
 * A "1" means that is NOT a possible entry
 *
 * Example: 
 * 1111 1111 1110 1110   (uint16_t)
 * xxxx xxx9 8765 4321   (symbolic representation)
 * In this case only 5 and 1 are valid solutions.
 *
 * */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0

#define CELL_SOLVED   0xFFFF	// 1111 1111 1111 1111
#define CELL_UNSOLVED 0xFE00	// 1111 1110 0000 0000

#define BOX_SOLVED   0xFFFF	// 1111 1111 1111 1111
#define BOX_UNSOLVED 0xFE00	// 1111 1110 0000 0000

#define remove_entry(p, n) p |= (1 << (n-1))
#define possible_entry(p, n) ~p & (1 << (n-1))

typedef struct Cell {
	int x;
	int y;
	int number;
	int n_possible_entries;
	uint16_t possible_entries;
	struct Box* box;
} Cell;

typedef struct Box {
	uint16_t possible;
	Cell** cells;
} Box;

typedef struct Sudoku {
	int cell_unsolved;
	Cell*** cells;
	Box** boxes;
} Sudoku;


#endif
