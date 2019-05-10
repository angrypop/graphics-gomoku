/*
	Provide a gomoku board, and you can play as in real world.
	Function prototypes and data structures go here.
*/

#ifndef PRAGMAONCE_GOMOKU_H
#define PRAGMAONCE_GOMOKU_H

#define BOARDSIZE 15

struct Board {
	unsigned int Turn;
	char BoardStatus[BOARDSIZE + 1][BOARDSIZE + 1];
	/*
		BoardStatue[x][y]: 'W' = White, 'B' = Black, 'N' = Neutral
		x and y is counted from bottom-left, ranging from 1 to 15
	*/
};
typedef struct Board Board;

/*
	If a function uses pointer to a board as its parameter, it will modify the board. 
	Otherwise it will visit only.
*/

char CheckWin(Board B);
/* 
	Check if any player wins.
	Arguments	: A board
	Return		: 'B' or 'W' or 'N'
*/

void InitBoard(Board *B);
/*
	Initialize a board, setting Turn as 0 and all positions as neutral.
	Arguments	: Address of a board
	Return		: void
*/

void SetPiece(Board *B, int TagX, int TagY, char Side);
/* 
	Set a piece.
	Arguments	: Address of a board, target coordinates, color of piece
	Return		: void
*/

#endif