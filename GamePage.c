#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "newGamePage.h"
#include "extrafunc.h"
#include "gomoku.h"
#include "newMain.h"
#include "imgui.h"
#include <time.h>


// extern Global variables
extern Board B;
extern LinkedListNode *LLHead;
// extern Setting S;
// temp: use local
static struct setting
{
	int Operation;
	int FirstMove;
	int UserColor;
}Setting;
#define OP_KEYBOARD 1
#define OP_MOUSE 0
#define FM_WHITE 1
#define FM_BLACK 0
#define UC_WHITE 1
#define UC_BLACK 0

// Local variables
static struct Information Info;
static bool UserTurn;
static int GameStatus;
static LinkedListNode *LLTail;
static Position Cur = { 8 ,8 }; // the coordinates of the current position

// Local Functions
static void InitGamePage();
static void Draw();
static void DrawChessboard();
static void DrawWhite(int i, int j);
static void DrawBlack(int i, int j);
static void DrawInfoBoard();
static void DrawButtons();
static void MouseEventProcess(int x, int y, int mbutton, int event);
static void KeyboardEventProcess(int key, int event);
static void TimerEventProcess(int timerID);
static void UpdateInfo();
static void CheckResult();
static void AbsDelay(int interval);

void newGamePage()
{
	InitGamePage();
	// register the callback function of Game Page
	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);

}


static void InitGamePage()
{
	// Initialize a new Windows
	// if the last function doesn't close the window
	// close previous window here
	double ix, iy;
	ix = 30;
	iy = 30;
	SetWindowSize(ix, iy);
	InitGraphics();

	// initialize the information 
	if (Setting.UserColor == UC_BLACK)
		Info.side = "白棋： AI   黑棋： 你  ";
	else
		Info.side = "白棋： 你   黑棋： AI ";
	Info.turn = "当前回合数： 0 ";
	Info.argument = "当前参数： 0.5 ";
	if (Setting.FirstMove == FM_BLACK)
		Info.now = "当前走棋： 黑棋";
	else
		Info.now = "当前走棋： 白棋";

	if (Setting.UserColor == Setting.FirstMove)
		UserTurn = TRUE;
	else
		UserTurn = FALSE;


	// initialize the gui
	InitGUI();

	// initicalize the newly defined color
	DefineColor("LightWood", 0.98, 0.788, 0.486);
	DefineColor("DarkWood", 0.933, 0.6588, 0.388);

	// initialize the linked list tail
	LLTail = LLHead;
}
static void TimerEventProcess(int timerID)
{
	switch (timerID)
	{
	case DRAW_ID:
		UpdateInfo();
		Draw();
		CheckResult();
		break;
	default:
		break;
	}
}

static void Draw()
{
	StartBatchDraw();

	DrawChessboard();//Draw Chessboard and Chessmen
	DrawInfoBoard();
	DrawButtons();

	EndBatchDraw();
}

static void DrawChessboard()
{
	ShowBmp(".\\pictures\\Checkboard.bmp",
		0, 0, CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT, SRCCOPY);

	int i, j;
	for (i = 1; i <= BOARDSIZE; i++)
	{
		for (j = 1; j <= BOARDSIZE; j++)
		{
			if ('W' == B.BoardStatus[i][j])
				DrawWhite(i, j);
			else if ('B' == B.BoardStatus[i][j])
				DrawBlack(i, j);
		}
	}

	if (B.BoardStatus[Cur.x][Cur.y] == 'N')
	{
		// Draw the instruction
		SetPenColor("Red");
		MovePen(CHESSBOARD_LEFTBOTTOM_X + (Cur.x - 1) * CHESSBOARD_BOXSIZE,
			CHESSBOARD_LEFTBOTTOM_Y + (Cur.y - 1) * CHESSBOARD_BOXSIZE);
		DrawArc(CHESSMAN_SIZE / 2.0, 0, 360);
	}
}
static void DrawWhite(int i, int j)
{
	double ix, iy;
	// ix, iy is the coordinates of the left-bottom of the chessman
	ix = CHESSBOARD_LEFTBOTTOM_X + (i - 1) * CHESSBOARD_BOXSIZE - CHESSMAN_SIZE / 2.0;
	iy = CHESSBOARD_LEFTBOTTOM_Y + (j - 1) * CHESSBOARD_BOXSIZE - CHESSMAN_SIZE / 2.0;

	// Show with transparent background
	ShowBmp(".\\pictures\\WhiteChessman.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCINVERT);
	ShowBmp(".\\pictures\\WhiteChessmanMask.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCAND);
	ShowBmp(".\\pictures\\WhiteChessman.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCINVERT);

}
static void DrawBlack(int i, int j)
{
	double ix, iy;
	// ix, iy is the coordinates of the left-bottom of the chessman
	ix = CHESSBOARD_LEFTBOTTOM_X + (i - 1) * CHESSBOARD_BOXSIZE - CHESSMAN_SIZE / 2.0;
	iy = CHESSBOARD_LEFTBOTTOM_Y + (j - 1) * CHESSBOARD_BOXSIZE - CHESSMAN_SIZE / 2.0;

	// Show with transparent background
	ShowBmp(".\\pictures\\BlackChessman.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCINVERT);
	ShowBmp(".\\pictures\\BlackChessmanMask.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCAND);
	ShowBmp(".\\pictures\\BlackChessman.bmp",
		ix, iy, CHESSMAN_SIZE, CHESSMAN_SIZE, SRCINVERT);
}
static void DrawInfoBoard()
{
	// Draw the rectangle
	SetPenColor("LightWood");
	drawRectangle(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT,
		INFO_BOARD_WIDTH, INFO_BOARD_HEIGHT, 1);

	// Draw the text
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT / 5.0,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.turn, 'M', "Black");
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 2.0 / 5.0,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.side, 'M', "Black");
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 3.0 / 5.0,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.argument, 'M', "Black");
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 4.0 / 5.0,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.now, 'M', "Black");
}
static void DrawButtons()
{
	// Draw the rectangle
	SetPenColor("DarkWood");
	drawRectangle(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH,
		0, INFO_BOARD_WIDTH, GAME_PAGE_HEIGHT - INFO_BOARD_WIDTH, 1);

	// Draw the buttons
	usePredefinedButtonColors(2);
	button(GenUIID(GP_ID_UNDO),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 3.5 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"悔棋");
	usePredefinedButtonColors(2);
	button(GenUIID(GP_ID_SURRENDER),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 2.0 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"投降");

}
static void MouseEventProcess(int x, int y, int mbutton, int event)
{
	uiGetMouse(x, y, mbutton, event);

	//*********************** to add menu button

	//check buttons
	if (button(GenUIID(GP_ID_UNDO),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 3.5 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"悔棋"))
	{
		//UNDO the last step only if it is the user's turn
		if (UserTurn)
		{
			LLTail = LLTail->Pre;
			DeleteNode(LLHead);
		}
	}
	else if (button(GenUIID(GP_ID_SURRENDER),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 2.0 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"投降"))
	{
		// cancel the callback function in Game Page
		cancelTimerEvent();
		cancelKeyboardEvent();
		cancelMouseEvent();
		// Go to End Game Page with the infomation of surrender
		EndGamePage(GAME_SURRENDER);
	}

	//operations
	if (Setting.Operation == OP_MOUSE)
	{
		// determine the coordinate of the position that the mouse is at
		double ix, iy;
		ix = ScaleXInches(x);
		iy = ScaleYInches(y);

		Cur.x = (ix - CHESSBOARD_LEFTBOTTOM_X) / CHESSBOARD_BOXSIZE + 1.5;
		Cur.y = (iy - CHESSBOARD_LEFTBOTTOM_Y) / CHESSBOARD_BOXSIZE + 1.5;
		if (Cur.x > 15)
			Cur.x = 15;
		else if (Cur.x < 0)
			Cur.x = 0;
		if (Cur.y > 15)
			Cur.y = 15;
		else if (Cur.y < 0)
			Cur.y = 0;

		switch (event)
		{
		case BUTTON_DOWN:
			if (mbutton == LEFT_BUTTON)
			{
				if (UserTurn)
				{
					if (B.BoardStatus[Cur.x][Cur.y] == 'N')
					{
						// User set piece
						SetPiece(&B, Cur.x, Cur.y, (Setting.UserColor == UC_BLACK) ? 'B' : 'W');
						InsertNode(LLHead, B);// Insert the current Board into the Linked List
						LLTail = LLTail->Next;
						UserTurn = FALSE;
					}
				}
			}
			break;
		default:
			break;
		}
	}
}
static void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);


	if (Setting.Operation == OP_KEYBOARD)
	{
		switch (event)
		{
		case KEY_UP:
			break;
		case KEY_DOWN:
			switch (key)
			{
			case VK_RETURN:
				if (UserTurn)
				{
					if (B.BoardStatus[Cur.x][Cur.y] == 'N')
					{
						// User set piece
						SetPiece(&B, Cur.x, Cur.y, (Setting.UserColor == UC_BLACK) ? 'B' : 'W');
						InsertNode(LLHead, B);// Insert the current Board into the Linked List
						LLTail = LLTail->Next;
						UserTurn = FALSE;
					}
				}
				break;
			case VK_LEFT:
				if (Cur.x > 1)
					Cur.x--;
				break;
			case VK_RIGHT:
				if (Cur.x <= BOARDSIZE)
					Cur.x++;
				break;
			case VK_UP:
				if (Cur.y <= BOARDSIZE)
					Cur.y++;
				break;
			case VK_DOWN:
				if (Cur.y > 1)
					Cur.y--;
				break;
			}
			break;
		}

	}

}
static void UpdateInfo()
{
	// Update UserColor
	if (Setting.UserColor == UC_BLACK)
		Info.side = "白棋： AI   黑棋： 你  ";
	else
		Info.side = "白棋： 你   黑棋： AI ";
	//Update Turns
	Info.turn = Concat("当前回合数：  ", IntegerToString(B.Turn));
	//Update argument
	//Info.argument = Concat("当前参数：  ", IntegerToString());
	//Update current turn
	if (UserTurn)
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "当前走棋： 黑棋";
			break;
		case UC_WHITE:
			Info.now = "当前走棋： 白棋";
			break;
		}
	}
	else
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "当前走棋： 白棋";
			break;
		case UC_WHITE:
			Info.now = "当前走棋： 黑棋";
			break;
		}
	}
}
static void CheckResult()
{
	char result = CheckWin(B);
	switch (result)
	{
	case 'W':
		switch (Setting.UserColor)
		{
		case UC_WHITE:
			// cancel the callback function in Game Page
			cancelTimerEvent();
			cancelKeyboardEvent();
			cancelMouseEvent();
			// Go to End Game Page with the infomation of winning
			EndGamePage(GAME_WIN);
			break;
		case UC_BLACK:
			// cancel the callback function in Game Page
			cancelTimerEvent();
			cancelKeyboardEvent();
			cancelMouseEvent();
			// Go to End Game Page with the infomation of lost
			EndGamePage(GAME_LOSE);
			break;
		}
		break;
	case 'B':
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			// cancel the callback function in Game Page
			cancelTimerEvent();
			cancelKeyboardEvent();
			cancelMouseEvent();
			// Go to End Game Page with the infomation of winning
			EndGamePage(GAME_WIN);
			break;
		case UC_WHITE:
			// cancel the callback function in Game Page
			cancelTimerEvent();
			cancelKeyboardEvent();
			cancelMouseEvent();
			// Go to End Game Page with the infomation of lost
			EndGamePage(GAME_LOSE);
			break;
			break;
		default:
			break;
		}
	}
}
static void AbsDelay(int interval)
{
	static int flag = 0;
	static int CurTime;
	static int PreTime;
	if (!flag)
	{
		CurTime = GetTickCount();
		PreTime = GetTickCount();
		flag = 1;
	}
	while (CurTime - PreTime < interval)
	{
		CurTime = GetTickCount();
		Sleep(1);
	}
	PreTime = CurTime;
}
