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


/***************************************************************
 VisualStudio 2010 用户注意：
    将Character Set设置为 Use Multibyte Character Set
	否则中文显示不正常
***************************************************************/

// 全局变量
static int GameStatus;
static double winwidth, winheight;   // 窗口尺寸
static int    show_more_buttons = 0; // 显示更多按钮

// 清屏函数，provided in libgraphics
void DisplayClear(void); 
// 计时器启动函数，provided in libgraphics
void startTimer(int id,int timeinterval);

// 用户的显示函数
void display(void); 

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}


// 用户主程序入口
// 仅初始化执行一次
bool EndGamePage (int gameStatus) 
{
	// 初始化窗口和图形系统
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();

    
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    GameStatus=gameStatus;

	// 注册时间响应函数
	registerMouseEvent(MouseEventProcess);      // 鼠标

	// 打开控制台，方便输出变量信息，便于调试
	// InitConsole(); 

}




// 按钮演示程序
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/5; // 控件宽度

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
	// 清屏
	DisplayClear();
			
	// 按钮
	drawButtons();
}
