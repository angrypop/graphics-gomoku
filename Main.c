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
#include "Main.h"
#include "gomoku.h"
#include "HomePage.h"

// Global variables
LinkedListNode *LLHead;// the head of the linked list
Board B; // the original chessboard
struct setting Setting = { OP_MOUSE, FM_BLACK, UC_BLACK, 2 }; // the setting of the game and initialize the default 

void Main()
{
	// Go to the Home Page
	HomePage();
}
