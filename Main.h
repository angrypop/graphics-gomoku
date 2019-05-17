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

// Macro for timer
#define DRAW_INTERVAL 16
#define DRAW_ID 1

// declaration for timer
void startTimer(int id, int timeinterval);

#endif



