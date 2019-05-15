#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wincon.h>
#include <Windows.h>

#include "genlib.h"
#include "gcalloc.h"
#include "strlib.h"
#include "extgraph.h"

//This header contains the declarations of the function added to the graphics.c

//Added Function by Steven Chen
void StartBatchDraw();
void EndBatchDraw();
void ShowBmp(string address, double x, double y, double width, double height, DWORD dwRop);
bool ReadAllPixels(FILE* fp);

