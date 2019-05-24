/*
	A simple Gomoku AI.
	Function definitions go here.
*/

#ifndef PRAGMAONCE_SIMPLEAI_C
#define PRAGMAONCE_SIMPLEAI_C

#include "gomoku.h"
#include "simpleai.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

int EvaluationCount;
double ShapeWeight[DIMENSION + 1] = { 5000000,1000000,250,300,260,300,60,80,60,55,65,15,55,40 };
unsigned long long ZobristHash[BOARDSIZE + 1][BOARDSIZE + 1][3];

static double EvaluatePosition(Board B, char Side, int TagX, int TagY);
static Position DFS(int Layor, Board *Board, double Alpha, double Beta, char Side, int IsMaxMin);
static int	CMP(const void *A, const void *B);

double EvaluatePosition(Board B, char Side, int TagX, int TagY) {
	int x, y, dx, dy; double Score = 0;
	for (x = TagX-2; x <= TagX+2; x++)
	for (y = TagY-2; y <= TagY+2; y++)
	for (dx = -1; dx <= 1; dx++) {
		for (dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0) continue;
			if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Gomoku */
				Score += ShapeWeight[1];
			if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N'
				)/* Huo 4 */
				Score += ShapeWeight[1];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 4 */
				Score += ShapeWeight[2];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 4 */
				Score += ShapeWeight[3];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 4 */
				Score += ShapeWeight[4];
			else if (x + 6 * dx <= BOARDSIZE && x + 6 * dx >= 1 && y + 6 * dy <= BOARDSIZE && y + 6 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
				B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N'
				)/* Huo 3 */
				Score += ShapeWeight[5];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 3, ??AAA */
				Score += ShapeWeight[6];
			else if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 5 * dy] == Side
				)/* Si 3, ?A?AA? */
				Score += ShapeWeight[7];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 3, A??AA */
				Score += ShapeWeight[8];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 3, A?A?A */
				Score += ShapeWeight[9];
			else if (x + 7 * dx <= BOARDSIZE && x + 7 * dx >= 1 && y + 7 * dy <= BOARDSIZE && y + 7 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
				B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N' &&
				B.BoardStatus[x + 7 * dx][y + 7 * dy] == 'N'
				)/* Huo 2, ???AA??? */
				Score += ShapeWeight[10];
			else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
				)/* Si 2, ???AA */
				Score += ShapeWeight[11];
			else if (x + 6 * dx <= BOARDSIZE && x + 6 * dx >= 1 && y + 6 * dy <= BOARDSIZE && y + 6 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
				B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N'
				)/* Huo 2, ??A?A?? */
				Score += ShapeWeight[12];
			else if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
				B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
				B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
				B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
				B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
				B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
				B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N'
				)/* Huo 2, ?A??A? */
				Score += ShapeWeight[13];
		}
	}
	return Score;
}

double Evaluate(Board B, char Side) {
	EvaluationCount++;
	double Score = 0;
	int x = 1, y = 1, dx = 0, dy = 0;
	int L = B.Xmin - 3, R = B.Xmax + 3, D = B.Ymin - 3, U = B.Ymax + 3;
	if (L < 1) L = 1;
	if (R > BOARDSIZE) R = BOARDSIZE;
	if (D < 1) D = 1;
	if (U > BOARDSIZE) U = BOARDSIZE;
	for (x = L; x <= R; x++) {
		for (y = D; y <= U; y++) {
			for (dx = 0; dx <= 1; dx++) {
				for (dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Gomoku */
						Score += ShapeWeight[1];
					if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N'
						)/* Huo 4 */
						Score += ShapeWeight[1];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 4 */
						Score += ShapeWeight[2];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 4 */
						Score += ShapeWeight[3];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 4 */
						Score += ShapeWeight[4];
					else if (x + 6 * dx <= BOARDSIZE && x + 6 * dx >= 1 && y + 6 * dy <= BOARDSIZE && y + 6 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
						B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N'
						)/* Huo 3 */
						Score += ShapeWeight[5];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 3, ??AAA */
						Score += ShapeWeight[6];
					else if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 5 * dy] == Side
						)/* Si 3, ?A?AA? */
						Score += ShapeWeight[7];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 3, A??AA */
						Score += ShapeWeight[8];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == Side &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 3, A?A?A */
						Score += ShapeWeight[9];
					else if (x + 7 * dx <= BOARDSIZE && x + 7 * dx >= 1 && y + 7 * dy <= BOARDSIZE && y + 7 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
						B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N' &&
						B.BoardStatus[x + 7 * dx][y + 7 * dy] == 'N'
						)/* Huo 2, ???AA??? */
						Score += ShapeWeight[10];
					else if (x + 4 * dx <= BOARDSIZE && x + 4 * dx >= 1 && y + 4 * dy <= BOARDSIZE && y + 4 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == Side &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side
						)/* Si 2, ???AA */
						Score += ShapeWeight[11];
					else if (x + 6 * dx <= BOARDSIZE && x + 6 * dx >= 1 && y + 6 * dy <= BOARDSIZE && y + 6 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == 'N' &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == Side &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N' &&
						B.BoardStatus[x + 6 * dx][y + 6 * dy] == 'N'
						)/* Huo 2, ??A?A?? */
						Score += ShapeWeight[12];
					else if (x + 5 * dx <= BOARDSIZE && x + 5 * dx >= 1 && y + 5 * dy <= BOARDSIZE && y + 5 * dy >= 1 &&
						B.BoardStatus[x + 0 * dx][y + 0 * dy] == 'N' &&
						B.BoardStatus[x + 1 * dx][y + 1 * dy] == Side &&
						B.BoardStatus[x + 2 * dx][y + 2 * dy] == 'N' &&
						B.BoardStatus[x + 3 * dx][y + 3 * dy] == 'N' &&
						B.BoardStatus[x + 4 * dx][y + 4 * dy] == Side &&
						B.BoardStatus[x + 5 * dx][y + 5 * dy] == 'N'
						)/* Huo 2, ?A??A? */
						Score += ShapeWeight[13];
				}
			}
		}
	}
	return Score;
}

Position GetBestMove(Board B, char Side) {
	if (B.Turn == 0) {
		SetPiece(&B, 8, 8, Side);
		return (Position) { 8, 8, 0 };
	}
	EvaluationCount = 0;
	return DFS(0, &B, INF, -INF, Side, 1);
}

static Position DFS(int Layor, Board *Board, double Alpha, double Beta, char Side, int IsMaxMin) {
	char OppoSide = Side == 'B' ? 'W' : 'B';
	Position Ret, SonRet;
	if (IsMaxMin) Ret.Score = -INF;
	else Ret.Score = INF;

	if (Layor == SEARCHDEPTH) {
		return (Position) { 0, 0, ATTACK * Evaluate(*Board, Side) - DEFENSE * Evaluate(*Board, OppoSide) };
		/* My evaluation - Opponent's evaluation */
	}

	int x = 1, y = 1, head = 0, QueueTail = 0;
	Position ValidPositions[BOARDSIZE*BOARDSIZE + 1];
	for (x = 1; x <= BOARDSIZE; x++) {
		for (y = 1; y <= BOARDSIZE; y++) {
			if (Board->BoardStatus[x][y] != 'N') continue;
			int dx, dy, t;
			for (dx = -1; dx <= 1; dx++) {
				for (dy = -1; dy <= 1; dy++) {
					for (t = 1; t <= DETECTDISTANCE; t++) {
						
						if (x + t * dx <= BOARDSIZE && x + t * dx >= 1 && y + t * dy <= BOARDSIZE && y + t * dy >= 1 &&
							Board->BoardStatus[x + t * dx][y + t * dy] != 'N') {
							ValidPositions[QueueTail++] = (Position) { x, y, 0 };
							break;
						}
					}
				}
			}
		}
	}
	

	/* Heuristic Search */
	if (QueueTail > HSTHERESHOLD) {
		for (head = 0; head < QueueTail; head++) {
			x = ValidPositions[head].x; y = ValidPositions[head].y;
			double PreScore = ATTACK * EvaluatePosition(*Board, Side, x, y) - DEFENSE * EvaluatePosition(*Board, OppoSide, x, y);
			SetPiece(Board, x, y, Side);
			ValidPositions[head].Score = ATTACK * EvaluatePosition(*Board, Side, x, y) - DEFENSE * EvaluatePosition(*Board, OppoSide, x, y) - PreScore;
			SetPiece(Board, x, y, 'N');
			Board->Turn -= 2;
		}
	}
	qsort(ValidPositions, QueueTail, sizeof(Position), CMP);
	if (QueueTail > HSTHERESHOLD) QueueTail = HSTHERESHOLD;

	for (head = 0; head < QueueTail; head++){
		x = ValidPositions[head].x; y = ValidPositions[head].y;

		SetPiece(Board, x, y, Side);

		if (IsMaxMin) {
			SonRet = DFS(Layor + 1, Board, Alpha, Ret.Score, OppoSide, !IsMaxMin);
		}
		else {
			SonRet = DFS(Layor + 1, Board, Ret.Score, Beta, OppoSide, !IsMaxMin);
		}
		SetPiece(Board, x, y, 'N');
		Board->Turn -= 2;

		if (IsMaxMin) {
			if (SonRet.Score > Ret.Score) {
				Ret.Score = SonRet.Score;
				Ret.x = x;
				Ret.y = y;
			}
			if (SonRet.Score >= Alpha) return Ret;/* Alpha-Beta Pruning */
		}
		else {
			if (SonRet.Score < Ret.Score) {
				Ret.Score = SonRet.Score;
				Ret.x = x;
				Ret.y = y;
			}
			if (SonRet.Score <= Beta) return Ret;/* Alpha-Beta Pruning */
		}
	}
	if (IsMaxMin) return Ret;
	else return Ret;
}

static int	CMP(const void *A, const void *B) {
	
	if (((Position*)A)->Score == ((Position*)B)->Score) return rand() % 3 - 1; /* Randomize */
	if (((Position*)A)->Score > ((Position*)B)->Score) return -1;
	if (((Position*)A)->Score < ((Position*)B)->Score) return 1;
}

void InitAI() {
	srand((unsigned)time(NULL));
	int x, y, t;
	for (x = 0; x <= BOARDSIZE; x++) {
		for (y = 0; y <= BOARDSIZE; y++) {
			int i;
			for (i = 1; i <= HASHDIGITS; i++) {
				ZobristHash[x][y][1] = 10 * ZobristHash[x][y][1] + rand() % 10;
				ZobristHash[x][y][2] = 10 * ZobristHash[x][y][2] + rand() % 10;
			}
		}
	}
}

#endif