/*
	Provide a gomoku board, and you can play as in real world.
	Function definitions go here.
*/

#ifndef PRAGMAONCE_GOMOKU.C #define PRAGMAONCE_GOMOKU.C
#include "gomoku.h"

char CheckWin(Board B) {
	int x = 1, y = 1, dx = 0, dy = 0;
	for (x = 1; x <= BOARDSIZE; x++) {
		for (y = 1; y <= BOARDSIZE; y++) {
			for (dx = -1; dx <= 1; dx++) {
				for (dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					if (x + 4 * dx > BOARDSIZE || x + 4 * dx < 1 || y + 4 * dy > BOARDSIZE || y + 4 * dy < 1) continue;
					if (B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'B' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'B' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'B' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'B' &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == 'B'
						)
						return 'B';
					if (B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'W' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'W' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'W' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'W' &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == 'W'
						)
						return 'W';
				}
			}
		}
	}
	return 'N';
}

void InitBoard(Board *B) {
	int x = 1, y = 1;
	for (x = 1; x <= BOARDSIZE; x++) {
		for (y = 1; y <= BOARDSIZE; y++) {
			B->BoardStatus[x][y] = 'N';
		}
	}
	B->Turn = 0;
}

void SetPiece(Board *B, int TagX, int TagY, char Side) {
	if (B->BoardStatus[TagX][TagY] != 'N') printf("Invalid Move.\n");
	B->BoardStatus[TagX][TagY] = Side;
	B->Turn++;
}

#endif