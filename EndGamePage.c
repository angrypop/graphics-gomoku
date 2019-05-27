/*
    provide a endgamepage,just a end page
*/

#ifndef END_GAME_PAGE_C
#define END_GAME_PAGE_C
#include "EndGamePage.h"
#include "extrafunc.h"
#include "gomoku.h"

// global variable
extern LinkedListNode *LLHead;
static int GameStatus;
static double winwidth, winheight;
static int    show_more_buttons = 0;

static void MouseEventProcess(int x, int y, int button, int event);

static void MouseEventProcess(int x, int y, int button, int event);
static void display(void);
// User main program entry
// Initialize once
 void EndGamePage (int gameStatus) 
{
	// Initialization window and graphics system
	//SetWindowSize(10, 10); // unit - inch
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // If the screen size is not enough ,scale it down
    InitGraphics();

    
	// get window size
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    GameStatus=gameStatus;

	// register mouse event function
	registerMouseEvent(MouseEventProcess);      // mouse

	// open the console for easy output of variable information and debug
	// InitConsole(); 

}

//Buttons demonstration program
  static void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // conrtol height
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/5; // conrtol width

	MovePen(winwidth/3,winheight/3*2);
	switch (GameStatus){
	 case GAME_WIN:
		 ShowBmp(".\\pictures\\YouWin.bmp",
			 0, 0, GetWindowWidth(), GetWindowHeight(), SRCCOPY);
         break;
	 case GAME_LOSE:
		 ShowBmp(".\\pictures\\YouLose.bmp",
			 0, 0, GetWindowWidth(), GetWindowHeight(), SRCCOPY);
	     break;
	 case GAME_SURRENDER: 
		 ShowBmp(".\\pictures\\Surrender.bmp",
			 0, 0, GetWindowWidth(), GetWindowHeight(), SRCCOPY);
	     break;
	 }
	
	if (button(GenUIID(0), x, y, w, h, "New Game")) {
		show_more_buttons = !show_more_buttons;
		cancelMouseEvent();
		LLHead->Pre = NULL;
		LLHead->Next = NULL;
		InitBoard(&LLHead->Board);
		GamePage(GAME_PAGE_PLAY);
	}
	if (button(GenUIID(1), x, y - 1.5 * h, w, h,  "Review")){
		show_more_buttons = !show_more_buttons;
		cancelMouseEvent();
		GamePage(GAME_PAGE_REPLAY);
	}
	if (button(GenUIID(3), x, y - 3 * h, w, h, "Main Menu")) {
		show_more_buttons = !show_more_buttons;
		cancelMouseEvent();
		HomePage();
	}
	if (button(GenUIID(2), x, y - 4.5 * h, w, h, "Exit")) {
		exit(-1);
	}
}

// mouse event function
static  void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI get mouse
	display(); // refresh diaplay
}

 static void display()
{
	// clearscreen
	DisplayClear();
	// button
	drawButtons();
}

#endif
