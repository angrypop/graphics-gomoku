/*
	A simple Gomoku AI.
	Function prototypes and data structures go here.
*/
#ifndef PRAGMAONCE_SIMPLEAI_H
#define PRAGMAONCE_SIMPLEAI_H
#include "gomoku.h"
#include "stdio.h"

#define DIMENSION 13
#define DETECTDISTANCE 1
#define HUMANSIDE 'W'
#define AISIDE 'B'
#define ATTACK 1.0
#define DEFENSE 1.5
#define HASHDIGITS 15 /* 2^48 ~= 10^15 */
#define HSTHERESHOLD 30
#define SEARCHDEPTH 4

/* 
	(Below denote A for friendly pieces, ? for blank positions)
	TERM	SHAPE		NO.
	"GMK"	AAAAA		0
	"Huo 4"	?AAAA?		1
	"Si 4"	?AAAA		2
			A?AAA		3
			AA?AA		4
	"Huo 3"	??AAA??		5
	"Si 3"	??AAA		6
			?A?AA?		7
			A??AA		8
			A?A?A		9
	"Huo 2"	???AA???	10
	"Si 2"	???AA		11
			??A?A??		12
			?A??A?		13
*/


void ReadWeights();
/*
	Read ShapeWeight[] from "weight.txt".
	Arguments: void
	Return: void
*/

double Evaluate(Board B, char Side);
/*
	Evaluate the board based on ShapeWeight[].
	Arguments: A Board, the Side to be friendly
	Return: Evaluation score
*/

Position GetBestMove(Board B, char Side);
/*
	Get best move.
	Arguments: A Board, the Side to be friendly
	Return: Best move, in the form of 1000*x+y.
	Note: Only call this function once, or else the position will be calculated twice!
	Example:
		Position BestMove = GetBestMove(B, 'W');
		SetPiece(&B, BestMove.x, BestMove.y, 'W');
*/

void InitAI();
#endif