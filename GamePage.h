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
#define GAME_PAGE_WIDTH 700
#define GAME_PAGE_HEIGHT 500
#define CHESSBOARD_WIDTH 500
#define CHESSBOARD_HEIGHT 500
#define INFO_BOARD_WIDTH 200
#define INFO_BOARD_HEIGHT 200
#define CHESSMAN_SIZE 20
#define CHESSBOARD_LEFTBOTTOM 28
#define CHESSBOARD_BOXSIZE 25
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
