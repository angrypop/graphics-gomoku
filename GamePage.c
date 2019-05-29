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
#include "simpleai.h"
#include "gomoku.h"
#include "Main.h"
#include "imgui.h"
#include <time.h>
#include "HomePage.h"
#include "EndGamePage.h"


// extern Global variables
extern Board B;
extern LinkedListNode *LLHead;
extern struct setting Setting;

// Local variables
static struct Information Info;
static bool UserTurn;
static int GameStatus;
static LinkedListNode *LLTail = NULL; // the tail of the Linked List
static Position Cur = { 8 ,8 }; // the coordinates of the current position
static bool Undo = FALSE; // store the status of the button UNDO
static bool Surrender = FALSE; // store the status of the button SURRENDER

// Local Functions
static void InitGamePage();
static void Draw();
static void DrawChessboard();
static void DrawWhite(int i, int j);
static void DrawBlack(int i, int j);
static void DrawInfoBoard();
static void DrawButtons();
static void DrawMenu();
static void MouseEventProcess(int x, int y, int mbutton, int event);
static void KeyboardEventProcess(int key, int event);
static void TimerEventProcess(int timerID);
static void UpdateInfo();
static void CheckResult();
static void AbsDelay(int interval);
static void CheckAI();
static void CopyBoard(Board* DesB, Board* OriB);
static void Restart();

void GamePage(int function)
{
	if (function == GAME_PAGE_PLAY)
	{
		// Initialize the GamePage data
		InitGamePage();

		// register the callback function of Game Page
		// start the timer for drawing
		startTimer(PLAY_ID, PLAY_INTERVAL);
		registerTimerEvent(TimerEventProcess);
		registerKeyboardEvent(KeyboardEventProcess);
		registerMouseEvent(MouseEventProcess);

	}
	else if (function == GAME_PAGE_REPLAY)
	{
		LLTail = LLHead;
		startTimer(REPLAY_ID, REPLAY_INTERVAL);
		registerTimerEvent(TimerEventProcess);
	}
	
}

// Function: InitGamePage()
// Usage: initialize the data in Game Page
static void InitGamePage()
{
	// Initialize a new Windows
	// if the last function doesn't close the window
	// close previous window here
	InitAI();
	
	// initialize the information 
	if (Setting.UserColor == UC_BLACK)
		Info.side = "White: AI   Black: You  ";
	else
		Info.side = "White: You   Black: AI ";
	Info.turn = "Turn no. 0 ";
	
	if (Setting.FirstMove == FM_BLACK)
		Info.now = "Black's turn";
	else
		Info.now = "White's turn";

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

	
	Draw();
}

// Function: TimerEventProcess
// Usage: Draw, update the information and check the result 
static void TimerEventProcess(int timerID)
{
	
	switch (timerID)
	{
	case PLAY_ID:
		
		UpdateInfo();
		Draw();
		CheckResult();
		break;
	case REPLAY_ID:
		if (LLTail->Next != NULL)
		{
			UpdateInfo();
			Draw();
			CheckResult();
			LLTail = LLTail->Next;
		}
		else
		{
			// in case the CheckResult fail
			cancelTimer(REPLAY_ID);
			cancelTimerEvent();
			exit(-1);
		}
	default:
		break;
	}
	// if it is AI's turn, then AI will take its turn
	CheckAI();
}

// Function: Draw()
// Usage: Draw the current chessboard, information board, buttons and menu
static void Draw()
{
	StartBatchDraw();

	DrawChessboard();//Draw Chessboard and Chessmen
	DrawInfoBoard();
	DrawButtons();
	DrawMenu();

	EndBatchDraw();
	
}

// Function: DrawChessBoard
// Usage: Draw the chessboard with chessmen and the instruction
static void DrawChessboard()
{
	ShowBmp(".\\pictures\\Chessboard15.bmp",
		0, 0, CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT, SRCCOPY);

	int i, j;
	for (i = 1; i <= BOARDSIZE; i++)
	{
		for (j = 1; j <= BOARDSIZE; j++)
		{
			if ('W' == LLTail->Board.BoardStatus[i][j])
				DrawWhite(i, j);
			else if ('B' == LLTail->Board.BoardStatus[i][j])
				DrawBlack(i, j);
		}
	}

	// Draw the instruction
	
	if (LLTail->Board.BoardStatus[Cur.x][Cur.y] == 'N')
	{
		SetPenColor("Red");
		MovePen(CHESSBOARD_LEFTBOTTOM_X + (Cur.x - 1 + 0.4) * CHESSBOARD_BOXSIZE,
			CHESSBOARD_LEFTBOTTOM_Y + (Cur.y - 1) * CHESSBOARD_BOXSIZE);
		DrawArc(CHESSMAN_SIZE / 2.0, 0, 360);
	}
}
// Function: DrawWhite
// Parameters: 
// i: the x coordinate of the chessman
// j: the y coordinate of the chessman
// Usage: Draw a white chessman
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
// Function: DrawBlack
// Parameters: 
// i: the x coordinate of the chessman
// j: the y coordinate of the chessman
// Usage: draw a black chessman
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

// Function: DrawInfoBoard
// Usage: Draw the information board
static void DrawInfoBoard()
{
	// Draw the rectangle
	SetPenColor("LightWood");
	drawRectangle(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT,
		INFO_BOARD_WIDTH, INFO_BOARD_HEIGHT, 1);

	// Draw the text
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT / 5.0 - MENU_HEIGHT,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.turn, 'M', "Black");
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 2.0 / 5.0 - MENU_HEIGHT,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.side, 'M', "Black");
	drawBox(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH + INFO_BOARD_WIDTH / 10.0,
		GAME_PAGE_HEIGHT - INFO_BOARD_HEIGHT * 3.0 / 5.0 - MENU_HEIGHT,
		INFO_BOARD_WIDTH * 4.0 / 5.0, INFO_BOARD_HEIGHT / 6.0,
		0, Info.now, 'M', "Black");
	
}
// Function: DrawButtons
// Usage: Draw the buttons and process the event of the button
static void DrawButtons()
{
	// Draw the rectangle
	SetPenColor("DarkWood");
	drawRectangle(GAME_PAGE_WIDTH - INFO_BOARD_WIDTH,
		0, INFO_BOARD_WIDTH, GAME_PAGE_HEIGHT - INFO_BOARD_WIDTH, 1);

	// Draw the buttons
	usePredefinedButtonColors(2);
	if (button(GenUIID(GP_ID_UNDO),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 3.5 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"Undo"))
		Undo = TRUE;
	usePredefinedButtonColors(2);
	if (button(GenUIID(GP_ID_SURRENDER),
		CHESSBOARD_WIDTH + INFO_BOARD_WIDTH / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) * 2.0 / 5.0,
		INFO_BOARD_WIDTH * 3.0 / 5.0, (CHESSBOARD_HEIGHT - INFO_BOARD_HEIGHT) / 6.0,
		"Surrender"))
		Surrender = TRUE;

}
// Function: DrawMenu
// Usage: Draw the menu and process the event of the button
static void DrawMenu()
{
	// refer to Prof. Liu's demo
	usePredefinedMenuColors(2);
	static char * menuListMenu[] = { "               Menu",
		"Screenshot   | Ctrl-P", // shortcuts have to use the form of [Ctrl-X] placed at the end of the string
		"Save Game  | Ctrl-S",
		"Main Menu   | Ctrl-B",
		"Help             | Ctrl-H",
		"Restart         | Ctrl-R",
		"Exit              | Ctrl-E" };
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double h = fH * 1.5; // height of controls
	double w = TextStringWidth(menuListMenu[0]) * 2; // width of the controls
	double x = GetWindowWidth() - w;
	double y = GetWindowHeight();
	double wlist = TextStringWidth(menuListMenu[0]) * 2;
	double xindent = GetWindowWidth() / 20; 
	int    selection;
	
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListMenu, sizeof(menuListMenu) / sizeof(menuListMenu[0]));
	if (selection > 0) selectedLabel = menuListMenu[selection];
	// choose to exit
	if (selection == 6)
		exit(-1);
	// read all pixels to .txt file
	else if (selection == 1)
	{
		FILE *fp = NULL;
		fp = fopen(".\\AllPixel.txt", "w");
		if (fp == NULL)
		{
			InitConsole();
			printf("Open file ERROR!");
		}
		else
		{
			ReadAllPixels(fp);
		}
	}
	// Save Game
	else if (selection == 2)
	{
		SaveBoard(LLTail->Board);
	}
	// Go Back to Home Page
	else if (selection == 3)
	{
		// cancel the callback function in Game Page
		cancelTimerEvent();
		cancelKeyboardEvent();
		cancelMouseEvent();
		Restart();
		HomePage();
	}
	// Help
	else if (selection == 4)
	{
		// draw the help
		usePredefinedTexBoxColors(2);
		StartBatchDraw();
		char* text1 = { "Instructions :" };
		char* text2 = { "(keyboard) move the pieces by pressing up and down," };
		char* text3 = { "           and use the Enter key to move the pieces." };
		char* text4 = { "(mouse) move the mouse to determine the position of the chess pieces," };
		char* text5 = { "         using the left key to drop." };
		char* text6 = { "Copyright 2019 Zhejiang University. All rights reserved." };

		textbox(GenUIID(0), 0, 4.5, 5, h, text1, sizeof(text1));
		textbox(GenUIID(0), 0, 4.5 - h, 5, h, text2, sizeof(text2));
		textbox(GenUIID(0), 0, 4.5 - 2 * h, 5, h, text3, sizeof(text3));
		textbox(GenUIID(0), 0, 4.5 - 3 * h, 5, h, text4, sizeof(text4));
		textbox(GenUIID(0), 0, 4.5 - 4 * h, 5, h, text5, sizeof(text5));
		textbox(GenUIID(0), 0, 4.5 - 5 * h, 5, h, text6, sizeof(text6));
		EndBatchDraw();
		// pause a while
		cancelTimerEvent();
		cancelKeyboardEvent();
		cancelMouseEvent();
		Sleep(3000);
		registerTimerEvent(TimerEventProcess);
		registerKeyboardEvent(KeyboardEventProcess);
		registerMouseEvent(MouseEventProcess);
	}
	// Restart
	else if (selection == 5)
	{
		Restart();
	}
}
// Function: MouseEventProcess
// Usage: process the undo and surrender tiding and determine whether the mouse is outside the chessboard
//		  and change the current coordinate of the user if the operation setting is to use mouse
//		  and set piece if the operation setting is to use mouse
static void MouseEventProcess(int x, int y, int mbutton, int event)
{
	
	uiGetMouse(x, y, mbutton, event);

	//Check whether the mouse is outside the chessboard
	static bool OutsideBoard = TRUE;
	if (ScaleXInches(x) >= CHESSBOARD_WIDTH)
		OutsideBoard = TRUE;
	else
		OutsideBoard = FALSE;

	

	if (Undo)
	{
		//UNDO the last step only if it is the user's turn
		if (UserTurn)
		{
			if (LLTail->Pre != NULL)
			{
				if (LLTail->Pre->Pre != NULL)
				{
					LLTail = LLTail->Pre->Pre;
					DeleteNode(LLHead);
					DeleteNode(LLHead);
				}
			}
			
		}
		Undo = FALSE;
	}
	else if (Surrender)
	{
		Surrender = FALSE;
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
				if (UserTurn && !OutsideBoard)
				{
					if (LLTail->Board.BoardStatus[Cur.x][Cur.y] == 'N')
					{
						// User set piece
						Board *pB = NULL;
						pB = (Board *)malloc(sizeof(Board));
						InitBoard(pB);
						// copy the original board to the destination one
						CopyBoard(pB, &LLTail->Board);
						InsertNode(LLHead, *pB);
						LLTail = LLTail->Next;
						SetPiece(&LLTail->Board, Cur.x, Cur.y, (Setting.UserColor == UC_BLACK) ? 'B' : 'W');
						UserTurn = FALSE;

						// Update the screen in time
						UpdateInfo();
						
					}
				}
			}
			break;
		default:
			break;
		}
	}
}
// Function: KeyboardEventProcess
// Usage: operate the current coordinate and set piece if the operation setting is to use keyboard
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
					if (LLTail->Board.BoardStatus[Cur.x][Cur.y] == 'N')
					{
						// User set piece
						Board *pB;
						pB = (Board *)malloc(sizeof(Board));
						InitBoard(pB);
						// copy the original board to the destination one
						CopyBoard(pB, &LLTail->Board);
						InsertNode(LLHead, *pB);
						LLTail = LLTail->Next;
						SetPiece(&LLTail->Board, Cur.x, Cur.y, (Setting.UserColor == UC_BLACK) ? 'B' : 'W');
						UserTurn = FALSE;

						// Update the screen in time
						UpdateInfo();
						
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
// Function: UpdateInfo
// Usage: update the infomation based on the infomation of the current chessboard
static void UpdateInfo()
{

	// Update UserColor
	if (Setting.UserColor == UC_BLACK)
		Info.side = "White: AI   Black: You";
	else
		Info.side = "White: You   Black: AI ";
	//Update Turns
	Info.turn = Concat("Turn no. ", IntegerToString(LLTail->Board.Turn));
	
	//Update current turn
	if (UserTurn)
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "Black's turn";
			break;
		case UC_WHITE:
			Info.now = "White's turn";
			break;
		}
	}
	else
	{
		switch (Setting.UserColor)
		{
		case UC_BLACK:
			Info.now = "White's turn";
			break;
		case UC_WHITE:
			Info.now = "Black's turn";
			break;
		}
	}

	
}
// Function: CheckResult
// Usage: Check whether any side win the game now
//		  and call the EndGamePage with according parameter if yes
static void CheckResult()
{
	char result = CheckWin(LLTail->Board);
	
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
			
		default:
			break;
		}
		break;
	}
}
// Function: AbsDelay
// Usage: delay the current process for a particular interval
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
// Function: CheckAI()
// Usage: if it is AI's turn, AI will set piece
static void CheckAI()
{
	if (LLTail == NULL)
		LLTail = LLHead;
	// AI set piece
	if (!UserTurn)
	{
		
		
		// get the best move
		Position BestMove = GetBestMove(LLTail->Board, (Setting.UserColor == UC_BLACK) ? 'W' : 'B');
		Board *pB;
		pB = (Board *)malloc(sizeof(Board));
		InitBoard(pB);
		// copy the original board to the destination one
		CopyBoard(pB, &LLTail->Board);

		InsertNode(LLHead, *pB);
		LLTail = LLTail->Next;
		SetPiece(&LLTail->Board, BestMove.x, BestMove.y, (Setting.UserColor == UC_BLACK) ? 'W' : 'B');
		UserTurn = TRUE;
	}

}
// Function: CopyBoard
// Parameters:
// DesB: the destination board
// OriB: the original board(source)
// Usage: copy the original board to the destination board
static void CopyBoard(Board* DesB, Board* OriB)
{
	// copy the original board to the destination board
	int i, j;
	for (i = 1; i <= BOARDSIZE; i++)
	{
		for (j = 1; j <= BOARDSIZE; j++)
		{
			if ('W' == OriB->BoardStatus[i][j])
				DesB->BoardStatus[i][j] = 'W';
			else if ('B' == OriB->BoardStatus[i][j])
				DesB->BoardStatus[i][j] = 'B';
		}
	}
	DesB->Turn = OriB->Turn;
	DesB->HashValue = OriB->HashValue;
	DesB->Xmax = OriB->Xmax;
	DesB->Xmin = OriB->Xmin;
	DesB->Ymax = OriB->Ymax;
	DesB->Ymin = OriB->Ymin;
}
// Function: Restart
// Usage: restart the game to the very beginning
static void Restart()
{
	while (LLHead->Next != NULL)
	{
		DeleteNode(LLHead);
	}
	free(LLHead);
	LLHead = NULL;
	// Initialize chessboard
	InitBoard(&B);
	LLHead = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	// Initialize linked list
	LLHead->Next = NULL;
	LLHead->Pre = NULL;
	LLHead->Board = B;
	LLTail = LLHead;
}