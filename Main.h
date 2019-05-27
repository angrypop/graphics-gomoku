#ifndef _MAIN_H_
#define _MAIN_H_


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

//Macro for GameStatus
#define GAME_QUIT -1
#define GAME_UNKNOWN 0
#define GAME_WIN 1
#define GAME_LOSE 2
#define GAME_SURRENDER 3
#define GAME_REPLAY 4

// Macro for Setting
// Operation
#define OP_KEYBOARD 1
#define OP_MOUSE 0
// First Move
#define FM_WHITE 1
#define FM_BLACK 0
// User Color
#define UC_WHITE 1
#define UC_BLACK 0

// declaration for timer
void startTimer(int id, int timeinterval);
void cancelTimer(int id);

// structure
struct setting
{
	int Operation;
	int FirstMove;
	int UserColor;
	int Difficulty;/* 2:Easy 4:Hard */
};

#endif



