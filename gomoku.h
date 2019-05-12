/*
	Provide a gomoku board, and you can play as in real world.
	Function prototypes and data structures go here.
*/

#ifndef PRAGMAONCE_GOMOKU_H
#define PRAGMAONCE_GOMOKU_H

#include "string.h"
#include "malloc.h"

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

struct Position {
	int x, y;
};
typedef struct Position Position;

struct LinkedListNode {
	Board Board;
	struct LinkedListNode * Pre;
	struct LinkedListNode * Next;
};
typedef struct LinkedListNode LinkedListNode;

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

LinkedListNode * NewLinkedList();
/*
	Create a new linked list, and return the pointer of its head node.
	Arguments	: void
	Return		: A pointer pointing to the head nod
*/

void InsertNode(LinkedListNode * Head, Board B);
/*
	Insert a node to the tail of a linked list.
	Arguments	: A linked list (pointer of its head node), a Board
	Return		: void
*/

void DeleteNode(LinkedListNode * Head);
/*
	Delete the tail node of a linked list.
	Arguments	: void
	Return		: void
*/
#endif