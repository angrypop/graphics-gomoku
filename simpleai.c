/*
	A simple Gomoku AI.
	Function definitions go here.
*/

#ifndef PRAGMAONCE_SIMPLEAI_C
#define PRAGMAONCE_SIMPLEAI_C

#include "gomoku.h"
#include "simpleai.h"
#include "stdio.h"

void ReadWeights() {
	freopen("weights.txt", "r", stdin);
	int i = 0;
	for (i = 0; i <= DIMENSION; i++) scanf("%lf", &ShapeWeight[i]);
	freopen("CON", "r", stdin);/* Works for Windows/DOS environment only */
}

double Evaluate(Board B, char Side) {
	ReadWeights();
	double Score = 0;
	int x = 1, y = 1, dx = 0, dy = 0;
	for (x = 1; x <= BOARDSIZE; x++) {
		for (y = 1; y <= BOARDSIZE; y++) {
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
		}
	}
	return Score;
}

Position GetBestMove(Board B, char Side) {
	DTNode Root;
	Root.IsMaxMin = 1;
	Root.Side = Side;
	Root.Value = -INF;
	Root.Board = B;
	Root.FatherValue = INF;
	DFS(0, &Root);
	return Root.BestMove;
}

static double DFS(int Layor, DTNode *CurNode) {
	
	if (Layor == SEARCHDEPTH) {
		char OppoSide = CurNode->Side == 'B' ? 'W' : 'B';
		return Evaluate(CurNode->Board, AISIDE) - Evaluate(CurNode->Board, HUMANSIDE);
		/* My evaluation - Opponent's evaluation */
	}
	int x = 1, y = 1;
	for (x = 1; x <= BOARDSIZE; x++) {
		for (y = 1; y <= BOARDSIZE; y++) {
			if (CurNode->Board.BoardStatus[x][y] != 'N') continue;/* Invalid Move */
			
			int dx, dy, t, IsPieceNearby = 0;
			for (dx = -1; dx <= 1; dx++) {
				for (dy = -1; dy <= 1; dy++) {
					for (t = 1; t <= DETECTDISTANCE; t++) {
						if (x + t * dx <= BOARDSIZE && x + t * dx >= 1 && y + t * dy <= BOARDSIZE && y + t * dy >= 1 &&
							CurNode->Board.BoardStatus[x + t * dx][y + t * dy] != 'N') {
							IsPieceNearby = 1;
							break;
						}
					}
				}
			}
			if (!IsPieceNearby) continue; /* Remote point, ignore */

			DTNode NewNode = *CurNode;
			NewNode.Side = CurNode->Side == 'B' ? 'W' : 'B';
			NewNode.Board.BoardStatus[x][y] = CurNode->Side;
			NewNode.IsMaxMin = !CurNode->IsMaxMin;
			if (NewNode.IsMaxMin) NewNode.Value = -INF;
			else NewNode.Value = INF;
			NewNode.FatherValue = CurNode->Value;/* AlphaBeta */

			double NewValue = DFS(Layor + 1, &NewNode);

			if (CurNode->IsMaxMin) {
				if (NewValue > CurNode->Value) {
					CurNode->Value = NewValue;
					CurNode->BestMove.x = x;
					CurNode->BestMove.y = y;
				}
				if (NewValue > CurNode->FatherValue) return NewValue; /* AlphaBeta */
			}
			else {
				if (NewValue < CurNode->Value) {
					CurNode->Value = NewValue;
					CurNode->BestMove.x = x;
					CurNode->BestMove.y = y;
				}
				if (NewValue < CurNode->FatherValue) return NewValue; /* AlphaBeta */
			}
		}
	}
	/*if (Layor <= 2) {
		PrintBoard(CurNode->Board);
		printf("Layor[%d] bestmove:( %d , %d) for side [%c], and AI get eva sco: %.2lf\n\n",Layor, CurNode->BestMove.x, CurNode->BestMove.y,CurNode->Side, CurNode->Value);

	}*/
		return CurNode->Value;
}
#endif