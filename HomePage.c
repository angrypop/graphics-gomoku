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

// extern Global variables
extern Board B;
extern LinkedListNode* LLHead;
extern struct setting Setting;


double winwidth, winheight; 
int    show_more_buttons = 0; 
int    show_model = 0;
int    show_forerunner = 0;
int    show_color = 0;

void DisplayClear(void);
void startTimer(int id, int timeinterval);
void display1(void);
void display2(void);
void display3(void);
void MouseEventProcess(int x, int y, int button, int event);
void DrawButtons1(void);
void DrawButtons2(void);
void DrawButtons3(void);

#include "HomePage.h"

static void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	switch (show_more_buttons)
	{
	case 0:
	case 1:display1(); break;
	case 2:display2(); break;
	case 3:display3(); break;
	}
}

static void display1()
{
	DisplayClear();
	ShowBmp("HomePageBackground.bmp", 0, 0, winwidth, winheight, SRCCOPY);
	DrawButtons1();
}

static void display2()
{
	DisplayClear();
	ShowBmp("SettingBackground.bmp", 0, 0, winwidth, winheight, SRCCOPY);
	DrawButtons2();
}

static void display3()
{
	DisplayClear();
	DrawButtons3();
}

static void DrawButtons1()
{
	double fH = GetFontHeight();
	double h = fH * 2;  
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5; 

	if (button(GenUIID(0), x, y, w, h, "Level")) 
		show_more_buttons = 1;
	if (button(GenUIID(0), x, y - 2 * h, w, h, "Strating"))
		exit(-1);
	if (button(GenUIID(0), x, y - 4 * h, w, h, "Setting")) 
		show_more_buttons = 2;
	if (button(GenUIID(0), x, y - 6 * h, w, h, "Helping"))
		show_more_buttons = 3;

	if (show_more_buttons==1) {
		int k;

		for (k = 0; k < 3; k++) {
			char name[128]; 
			switch (k)
			{
			case 0:
				sprintf(name, "Easy");
				button(GenUIID(k), x + w * 1.2, y - k * h * 2, w, h, name);
				if (button(GenUIID(0), x + w * 1.2, y - k * h * 2, w, h, name))
					exit(-1);
				break;
			case 1:
				sprintf(name, "Medium");
				button(GenUIID(k), x + w * 1.2, y - k * h * 2, w, h, name);
				if (button(GenUIID(0), x + w * 1.2, y - k * h * 2 ,w, h, name))
					exit(-1);
				break;
			case 2:
				sprintf(name, "Difficult");
				button(GenUIID(k), x + w * 1.2, y - k * h * 2, w, h, name);
				if (button(GenUIID(0), x + w * 1.2, y - k * h * 2, w, h, name))
					exit(-1);
				break;
			}
		}

	}
}

static void DrawButtons2()
{
	double fH = GetFontHeight();
	double h = fH * 2;
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5;

	if (button(GenUIID(0), x + w * 1.2, y + 3 * h, w, h, show_model ? "Mouse" : "KeyBoard")) {
		show_model = !show_model;
	}
	if (button(GenUIID(0), x + w * 1.2, y + 1 * h, w, h, show_forerunner ? "You" : "Opponent")) {
		show_forerunner = !show_forerunner;
	}
	if (button(GenUIID(0), x + w * 1.2, y - 1 * h, w, h, show_color ? "White" : "Black")) {
		show_color = !show_color;
	}

	button(GenUIID(0), x - w * 1.2, y + 3 * h, w, h, "Model");
	button(GenUIID(0), x - w * 1.2, y + 1 * h, w, h, "Forerunner");
	button(GenUIID(0), x - w * 1.2, y - 1 * h, w, h, "Color");

	if (button(GenUIID(0), x + w * 1.6, y - 3 * h, w, h, "Back")) {
		show_more_buttons = 0;
		HomePage();
	}
}

static void DrawButtons3()
{
	double fH = GetFontHeight();
	double h = fH * 2;
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5;

	if (button(GenUIID(0), x + w * 1.6, y - 6 * h, w, h, "Back")) {
		show_more_buttons = 0;
		HomePage();
	}
	char* text1 = { "Instructions :" };
	char* text2 = { "(keyboard) move the pieces by pressing up and down," };
	char* text3 = { "           and use the Enter key to move the pieces." };
	char* text4 = { "(mouse) move the mouse to determine the position of the chess pieces," };
	char* text5 = { "         using the left key to drop." };
	char* text6 = { "Copyright 2019 zhejiang university. All rights reserved." };

	textbox(GenUIID(0), 0, 4.5, 5, h, text1, sizeof(text1));
	textbox(GenUIID(0), 0, 4.5 - h, 5, h, text2, sizeof(text2));
	textbox(GenUIID(0), 0, 4.5 - 2 * h, 5, h, text3, sizeof(text3));
	textbox(GenUIID(0), 0, 4.5 - 3 * h, 5, h, text4, sizeof(text4));
	textbox(GenUIID(0), 0, 4.5 - 4 * h, 5, h, text5, sizeof(text5));
	textbox(GenUIID(0), 0, 4.5 - 5 * h, 5, h, text6, sizeof(text6));
}

bool HomePage()
{
	// Initialize chessboard
	InitBoard(&B);
	LLHead = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	// Initialize linked list
	LLHead->Next = NULL;
	LLHead->Pre = NULL;
	LLHead->Board = B;

	SetWindowSize(5, 5);
	InitGraphics();

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerMouseEvent(MouseEventProcess);

	StartBatchDraw();
	ShowBmp("HomePageBackground.bmp", 0, 0, winwidth, winheight, SRCCOPY);
	EndBatchDraw();
	
	DrawButtons1();	
}

#endif