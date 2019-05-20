/*
    provide a endgamepage,just a end page
*/ 
#ifndef _END_GAME_PAGE_H_
#define _END_GAME_PAGE_H_

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



// global variable
 int GameStatus;
 double winwidth, winheight;   
 int    show_more_buttons = 0; 

//function
void DisplayClear(void); 
void MouseEventProcess(int x, int y, int button, int event);
void display(void); 


#endif 
