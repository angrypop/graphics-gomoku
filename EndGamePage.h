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
#ifndef _END_GAME_PAGE_H_
#define _END_GAME_PAGE_H_

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
static double winwidth, winheight;   
static int    show_more_buttons = 0; 


void DisplayClear(void); 
void startTimer(int id,int timeinterval);
void display(void); 

// mouse event function
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI get mouse
	display(); // refresh diaplay
}

#endif 
