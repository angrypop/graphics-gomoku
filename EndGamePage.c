/*
    provide a endgamepage,just a end page
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
#include "EndGamePage.h"


// global variable
static int GameStatus;
static double winwidth, winheight;   // window size
static int    show_more_buttons = 0; // show more button

// clear sceen function，provided in libgraphics
void DisplayClear(void); 
// timer function，provided in libgraphics
void startTimer(int id,int timeinterval);

// display function
void display(void); 

// mouse event function
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI get mouse
	display(); // refresh diaplay
}


// User main program entry
// Initialize once
bool EndGamePage (int gameStatus) 
{
	// 初始化窗口和图形系统
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
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
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // conrtol height
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/5; // conrtol width

	MovePen(winwidth/3,winheight/3*2);
	switch (GameStatus){
	 case WIN:
         DrawTextString("you are  WINNING!");
         break;
	 case LOSE:
	     DrawTextString("you are  LOSING!");
	     break;
	 case SUREENDER: 
	     DrawTextString("you are  SUREENDER!"); 
	     break;
	 }
    
	if (button(GenUIID(0), x, y, w, h,  "复盘")){
		show_more_buttons = ! show_more_buttons;
		PlayAgain=TRUE;
	}
		
	
	if( button(GenUIID(0), x, y-2*h, w, h, "退出")){
		exit(-1);
		PlayAgain=FALSE;
	}
	
}

void display()
{
	// clearscreen
	DisplayClear();
			
	// button
	drawButtons();
}
