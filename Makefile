CC = cc

LDFLAGS = 
CFLAGS  = 

SRC = puzzle.c sudoku.c cell.c box.c
OBJ = ${SRC:.c=.o}
INC = puzzle.h sudoku.h cell.h box.h common.h

all: sudoku

${OBJ}: ${INC}

sudoku: ${OBJ}
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

run: sudoku
	./sudoku

clean:
	rm -f sudoku ${OBJ}

.PHONY:  all run clean
