#pragma once
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
#define CHESSMAN_SIZE 0.2
#define CHESSBOARD_LEFTBOTTOM 0.28
#define CHESSBOARD_BOXSIZE 0.245
//Macro for buttons id
#define GP_ID_UNKNOWN 0
#define GP_ID_UNDO 1
#define GP_ID_SURRENDER 2
#define GP_ID_QUIT 8

// declarations
int GamePage(void);

//structure
struct Information
{
	string turn;
	string side;
	string argument;
	string now;
};
