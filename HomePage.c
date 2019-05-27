/*
    provide a homepage,just a start page
*/ 

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

#include "imgui.h"
#include "extrafunc.h"
#include "gomoku.h"
#include "simpleai.h"
#include "HomePage.h"
#include "GamePage.h"
#include "Main.h"

// extern Global variables
extern Board B;
extern LinkedListNode* LLHead;
extern struct setting Setting;

// Local variables
static double winwidth, winheight; 
static int    show_strating = 0;
static int    show_setting = 0;
static int    show_helping = 0;
static int    show_model = 0;
static int    show_forerunner = 0;
static int    show_color = 0; 
static int    show_level = 0;

// Function: DisplayClear
// Usage:clean screen
void DisplayClear(void);

// Local Functions
static void displayhomepage(void);
static void displaysetting(void);
static void displayhelping(void);
static void MouseEventProcess(int x, int y, int button, int event);
static void DrawButtonsHomepage(void);
static void DrawButtonsSetting(void);
static void WriteTextHelping(void);

bool HomePage()
{
	// set the button style of homepage
	usePredefinedButtonColors(0);
	// Initialize chessboard
	InitBoard(&B);
	LLHead = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	// Initialize linked list
	LLHead->Next = NULL;
	LLHead->Pre = NULL;
	LLHead->Board = B;

	// get window size
	SetWindowSize(7, 5);
	InitGraphics();
	SetWindowTitle("Graphics Gomoku");
	winwidth = GetWindowWidth() - 2;
	winheight = GetWindowHeight();

	// register mouse event function
	registerMouseEvent(MouseEventProcess);

	StartBatchDraw();
	ShowBmp(".\\pictures\\HomePageBackground_5x7.bmp", 0, 0, winwidth + 2, winheight, SRCCOPY);
	EndBatchDraw();

	DrawButtonsHomepage();

	// open the console for easy output of variable information and debug
	// InitConsole(); 
}

// Function: MouseEventProcess
// Usage:determine the next event activity to be performed by clicking the mouse button 
static void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);

	//Check which button was pressed
	if (show_strating == 1) {
		cancelMouseEvent(MouseEventProcess);
		show_strating = 0;
		show_setting = 0;
		show_helping = 0;
		GamePage(GAME_PAGE_PLAY);
		return;
	}
	if (show_setting == 1) {
		displaysetting();
		return;
	}
	if (show_helping == 1) {
		displayhelping();
		return;
	}
	//No button is pressed to display the initial interfac
	displayhomepage();
}

// Function: displayhomepage
// Usage:display homepage
static void displayhomepage()
{
	DisplayClear();
	ShowBmp(".\\pictures\\HomePageBackground_5x7.bmp", 0, 0, winwidth + 2, winheight, SRCCOPY);
	DrawButtonsHomepage();
}

// Function: displaysetting
// Usage:display setting
static void displaysetting()
{
	DisplayClear();
	ShowBmp(".\\pictures\\SettingBackground.bmp", 0, 0, winwidth + 2, winheight, SRCCOPY);
	DrawButtonsSetting();
}

// Function: displayhelping
// Usage:display helping
static void displayhelping()
{
	DisplayClear();
	WriteTextHelping();
}

// Function: DrawButtonsHomepage
// Usage:draw the buttons on the home screen and define their functions
static void DrawButtonsHomepage()
{
	double fH = GetFontHeight();
	double h = fH * 2;// conrtol height
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5;// conrtol width
	usePredefinedButtonColors(4);
	if (button(GenUIID(0), x + 3.5 * w, y + 7 * h, w, h, "Play"))
		show_strating = 1;
	if (button(GenUIID(0), x + 3.5 * w, y + 5 * h, w, h, "Setting")) {
		show_setting = 1;
	}
	if (button(GenUIID(0), x + 3.5 * w, y + 3 * h, w, h, "Help"))
		show_helping = 1;
	if (button(GenUIID(0), x + 3.5 * w, y + 1 * h, w, h, "Exit"))
		exit(-1);
}

// Function: DrawButtonsSetting
// Usage:draw the buttons on the setting screen and define their functions
static void DrawButtonsSetting()
{
	double fH = GetFontHeight();
	double h = fH * 2;// conrtol height
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5;// conrtol width
	usePredefinedButtonColors(2);
	if (button(GenUIID(0), x + w * 2, y + 5 * h, w, h, show_level ? "Easy" : "Hard")) {
		show_level = !show_level;
	}
	if (button(GenUIID(0), x + w * 2, y + 3 * h, w, h, !show_model ? "Mouse" : "KeyBoard")) {
		if (show_model)
			Setting.Operation = OP_MOUSE;
		else
			Setting.Operation = OP_KEYBOARD;
		show_model = !show_model;
	}
	if (button(GenUIID(0), x + w * 2, y + 1 * h, w, h, !show_forerunner ? "You" : "A.I.")) {
		if (show_forerunner)
			Setting.FirstMove = (Setting.UserColor == UC_BLACK) ? FM_BLACK : FM_WHITE;
		else
			Setting.FirstMove = (Setting.UserColor == UC_WHITE) ? FM_BLACK : FM_WHITE;
		show_forerunner = !show_forerunner;
	}
	if (button(GenUIID(0), x + w * 2, y - 1 * h, w, h, show_color ? "White" : "Black")) {
		if (!show_color)
			Setting.UserColor = UC_WHITE;
		else
			Setting.UserColor = UC_BLACK;
		show_color = !show_color;
		
	}
	usePredefinedButtonColors(4);
	button(GenUIID(0), x - w * 0.5, y + 5 * h, 2 * w, h, "Difficulty");
	button(GenUIID(0), x - w * 0.5, y + 3 * h, 2 * w, h, "Input Method");
	button(GenUIID(0), x - w * 0.5, y + 1 * h, 2 * w, h, "Forerunner");
	button(GenUIID(0), x - w * 0.5, y - 1 * h, 2 * w, h, "Your Side");

	usePredefinedButtonColors(2);
	if (button(GenUIID(0), x + w * 3, y - 3 * h, w, h, "Back")) {
		show_strating = 0;
		show_setting = 0;
		show_helping = 0;
		HomePage();
	}

}

// Function: DrawButtonsHelping
// Usage:write the texts on the helping screen 
static void WriteTextHelping()
{
	double fH = GetFontHeight();
	double h = fH * 2;// conrtol height
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5;// conrtol width

	if (button(GenUIID(0), x + w * 1.6, y - 6 * h, w, h, "Back")) {
		show_strating = 0;
		show_setting = 0;
		show_helping = 0;
		HomePage();
	}

	usePredefinedTexBoxColors(0);
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
}


