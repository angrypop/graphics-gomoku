#ifndef _GAME_PAGE_H_
#define _GAME_PAGE_H_

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

//Macro
#define GAME_PAGE_WIDTH 7.0
#define GAME_PAGE_HEIGHT 5.0
#define CHESSBOARD_WIDTH 5.0
#define CHESSBOARD_HEIGHT 5.0
#define INFO_BOARD_WIDTH 2.0
#define INFO_BOARD_HEIGHT 2.0
#define CHESSMAN_SIZE 0.25
#define CHESSBOARD_LEFTBOTTOM_X 0.175
#define CHESSBOARD_LEFTBOTTOM_Y 0.185
#define CHESSBOARD_BOXSIZE 0.33
#define MENU_HEIGHT ((GetFontHeight())*(1.5))

//Macro for buttons id
#define GP_ID_UNKNOWN 0
#define GP_ID_UNDO 1
#define GP_ID_SURRENDER 2
#define GP_ID_QUIT 8

// declarations
void GamePage(void);

//structure
struct Information
{
	string turn;
	string side;
	string now;
};

#endif 
