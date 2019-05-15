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
#include "GamePage.h"
#include "extrafunc.h"
#include "gomoku.h"
#include "Main.h"
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
static void UpdateInfo();
static void AbsDelay(int interval);


// to do
// ����
// ��Ҫ����ʵ�֣����ӣ�͸����ͼ��

// ��Ϣ��
// ��Ҫ����ʵ�֣��غ���������������ڰ׳ַ�����ǰ�غ�������

// ��ť��
// ���壬 ������?���� Ͷ��

// �˵���
// ���²˵�������ʾ���ఴ���������˵����ָ�Ϊ����˵�
// ���ã����������أ������ͼ�� ������Ϸ, QUIT

//to do :
//1. AI
//3. Mouse operation

int GamePage(void)
{
	InitGamePage();

	while (TRUE)
	{
		GameStatus = GAME_UNKNOWN;

		UpdateInfo();
		Draw();

		if (!UserTurn)
		{
			// AI place the chessman
			// ********************************* todo
			UserTurn = TRUE;
		}

		//absolute delay
		AbsDelay(16);

		//check result
		char Result = CheckWin(B);
		if (Result == 'W')
		{
			GameStatus = GAME_WIN;
		}
		else if (Result == 'L')
		{
			GameStatus = GAME_LOSE;
		}


		if (GameStatus != GAME_UNKNOWN)
			break;
	}
	return GameStatus;
}

static void InitGamePage()
{
	// Initialize a new Windows
	// if the last function doesn't close the window
	// close previous window here
	double ix, iy;
	//temp
	ix = 30;
	iy = 30;
	SetWindowSize(ix, iy);
	InitGraphics();

	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);

	// initialize the information 
	if (Setting.UserColor == UC_BLACK)
		Info.side = "���壺 AI   ���壺 ��  ";
	else
		Info.side = "���壺 ��   ���壺 AI ";
	Info.turn = "��ǰ�غ����� 0 ";
	Info.argument = "��ǰ������ 0.5 ";
	if (Setting.FirstMove == FM_BLACK)
		Info.now = "��ǰ���壺 ����";
	else
		Info.now = "��ǰ���壺 ����";

	if (Setting.UserColor == Setting.FirstMove)
		UserTurn = TRUE;
	else
		UserTurn = FALSE;


	// initialize the gui
	InitGUI();
	DefineColor("LightWood", 0.98, 0.788, 0.486);
	DefineColor("DarkWood", 0.933, 0.6588, 0.388);

	// initialize the linked list tail
	LLTail = LLHead;
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
		0, 0, ScaleXInches(CHESSBOARD_WIDTH), ScaleYInches(CHESSBOARD_HEIGHT), SRCCOPY);

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
}
static void DrawWhite(int i, int j)
{
	double ix, iy;
	// ix, iy is the coordinates of the left-bottom of the chessman
	ix = ScaleXInches(CHESSBOARD_LEFTBOTTOM + (i - 1) * CHESSMAN_SIZE - CHESSMAN_SIZE / 2);
	iy = ScaleYInches(CHESSBOARD_LEFTBOTTOM + (j - 1) * CHESSMAN_SIZE - CHESSMAN_SIZE / 2);

	// Show with transparent background
	ShowBmp(".\\pictures\\WhiteChessman.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCINVERT);
	ShowBmp(".\\pictures\\WhiteChessmanMask.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCAND);
	ShowBmp(".\\pictures\\WhiteChessman.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCINVERT);

}
static void DrawBlack(int i, int j)
{
	double ix, iy;
	// ix, iy is the coordinates of the left-bottom of the chessman
	ix = ScaleXInches(CHESSBOARD_LEFTBOTTOM + (i - 1) * CHESSMAN_SIZE - CHESSMAN_SIZE / 2);
	iy = ScaleYInches(CHESSBOARD_LEFTBOTTOM + (j - 1) * CHESSMAN_SIZE - CHESSMAN_SIZE / 2);

	// Show with transparent background
	ShowBmp(".\\pictures\\BlackChessman.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCINVERT);
	ShowBmp(".\\pictures\\BlackChessmanMask.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCAND);
	ShowBmp(".\\pictures\\BlackChessman.bmp",
		ix, iy, ScaleXInches(CHESSMAN_SIZE), ScaleYInches(CHESSMAN_SIZE), SRCINVERT);
}
static void DrawInfoBoard()
{
	// Draw the rectangle
	SetPenColor("LightWood");
	drawRectangle(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH),
		ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT),
		ScaleXInches(INFO_BOARD_WIDTH), ScaleYInches(INFO_BOARD_HEIGHT), 1);

	// Draw the text
	SetPenColor("White");
	drawBox(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 5),
		ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches(INFO_BOARD_HEIGHT / 6),
		1, Info.turn, 'M', "Black");
	drawBox(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 5),
		ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 2 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches(INFO_BOARD_HEIGHT / 6),
		1, Info.side, 'M', "Black");
	drawBox(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 5),
		ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 3 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches(INFO_BOARD_HEIGHT / 6),
		1, Info.argument, 'M', "Black");
	drawBox(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 5),
		ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 3 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 4 / 5), ScaleYInches(INFO_BOARD_HEIGHT / 6),
		1, Info.now, 'M', "Black");

}
static void DrawButtons()
{
	// Draw the rectangle
	SetPenColor("DarkWood");
	drawRectangle(ScaleXInches(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH),
		0, ScaleXInches(INFO_BOARD_WIDTH), ScaleYInches(GAME_PAGE_HEIGHT - INFO_BOARD_WIDTH), 1);

	// Draw the buttons
	button(GenUIID(GP_ID_UNDO),
		ScaleXInches(CHESSBOARD_WIDTH), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 3 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6),
		"����");
	button(GenUIID(GP_ID_SURRENDER),
		ScaleXInches(CHESSBOARD_WIDTH), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 2 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6),
		"Ͷ��");

}
static void MouseEventProcess(int x, int y, int mbutton, int event)
{
	uiGetMouse(x, y, mbutton, event);
	//*********************** to add menu button
	//check buttons
	if (button(GenUIID(GP_ID_UNDO),
		ScaleXInches(CHESSBOARD_WIDTH), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 3 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6), "����"))
	{
		//UNDO the last step only if it is the user's turn
		if (UserTurn)
		{
			LLTail = LLTail->Pre;
			DeleteNode(LLHead);
		}
	}
	else if (button(GenUIID(GP_ID_SURRENDER),
		ScaleXInches(CHESSBOARD_WIDTH), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 2 / 5),
		ScaleXInches(INFO_BOARD_WIDTH * 3 / 5), ScaleYInches((CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6), "Ͷ��"))
	{
		GameStatus = GAME_SURRENDER;
	}

	//operations
	if (Setting.Operation == OP_MOUSE)
	{
		// ****************************** todo
	}
}
static void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);

	static int x = 10, y = 10; // the coordinates of the current location

	if (B.BoardStatus[x][y] == 'N')
	{
		// Draw the instruction
		SetPenColor("Red");
		MovePen(ScaleXInches(CHESSBOARD_LEFTBOTTOM + (x - 1) * CHESSBOARD_BOXSIZE),
			ScaleYInches(CHESSBOARD_LEFTBOTTOM + (y - 1) * CHESSBOARD_BOXSIZE));
		DrawArc(ScaleXInches(CHESSMAN_SIZE / 2), 0, 60);
		DrawArc(ScaleXInches(CHESSMAN_SIZE / 2), 120, 180);
		DrawArc(ScaleXInches(CHESSMAN_SIZE / 2), 240, 300);
	}
	if (Setting.Operation == OP_KEYBOARD)
	{
		switch (event)
		{
		case KEY_UP:
			break;
		case KEY_DOWN:
			switch (key)
			{
			case VK_RBUTTON:
				if (UserTurn)
				{
					if (B.BoardStatus[x][y] == 'N')
					{
						SetPiece(&B, x, y, (Setting.UserColor == UC_BLACK) ? 'B' : 'W');
						InsertNode(LLHead, B);// Insert the current Board into the Linked List
						LLTail = LLTail->Next;
						UserTurn = FALSE;
					}
				}
			case VK_LEFT:
				if (x >= 1)
					x--;
			case VK_RIGHT:
				if (x <= BOARDSIZE)
					x++;
			case VK_UP:
				if (y <= BOARDSIZE)
					y++;
			case VK_DOWN:
				if (y >= 0)
					y--;
			}
			break;
		}

	}

}
static void UpdateInfo()
{
	// Update UserColor
	if (Setting.UserColor == UC_BLACK)
		Info.side = "���壺 AI   ���壺 ��  ";
	else
		Info.side = "���壺 ��   ���壺 AI ";
	//Update Turns
	Info.turn = Concat("��ǰ�غ�����  ", IntegerToString(B.Turn));
	//Update argument
	//Info.argument = Concat("��ǰ������  ", IntegerToString());
	//Update current turn
	if (UserTurn)
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "��ǰ���壺 ����";
			break;
		case UC_WHITE:
			Info.now = "��ǰ���壺 ����";
			break;
		}
	}
	else
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "��ǰ���壺 ����";
			break;
		case UC_WHITE:
			Info.now = "��ǰ���壺 ����";
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
