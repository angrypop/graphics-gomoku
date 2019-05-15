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

#ifndef static double winwidth, winheight;
#define static double winwidth, winheight; 
#define static int    show_more_buttons = 0; 

#include "HomePage.h"

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); 
	display(); 
}

void display()
{
	DisplayClear();
	ShowBmp("HomePageBackground.bmp", 0, 0, winwidth, winheight, SRCCOPY);
	DrawButtons();
}

void DrawButtons()
{
	double fH = GetFontHeight();
	double h = fH * 2;  
	double x = winwidth / 2.5;
	double y = winheight / 2 - h;
	double w = winwidth / 5; 

	if (button(GenUIID(0), x, y, w, h, "Grade of Difficulty"))
		show_more_buttons = !show_more_buttons;
	if (button(GenUIID(0), x, y - 2 * h, w, h, "Strating"))
		exit(-1);
	if (button(GenUIID(0), x, y - 4 * h, w, h, "Setting"))
		exit(-1);
	if (button(GenUIID(0), x, y - 6 * h, w, h, "Helping"))
		exit(-1);

	if (show_more_buttons) {
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

bool HomePage()
{
	SetWindowSize(16.7, 14.8);
	InitGraphics();

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerMouseEvent(MouseEventProcess);

	StartBatchDraw();
	ShowBmp("HomePageBackground.bmp", 0, 0, winwidth, winheight, SRCCOPY);
	EndBatchDraw();
	
	DrawButtons();	
}

#endif