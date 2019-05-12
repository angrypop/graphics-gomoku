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
 VisualStudio 2010 �û�ע�⣺
    ��Character Set����Ϊ Use Multibyte Character Set
	����������ʾ������
***************************************************************/

// ȫ�ֱ���
static int GameStatus;
static double winwidth, winheight;   // ���ڳߴ�
static int    show_more_buttons = 0; // ��ʾ���ఴť

// ����������provided in libgraphics
void DisplayClear(void); 
// ��ʱ������������provided in libgraphics
void startTimer(int id,int timeinterval);

// �û�����ʾ����
void display(void); 

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
}


// �û����������
// ����ʼ��ִ��һ��
bool EndGamePage (int gameStatus) 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	//SetWindowSize(10, 10); // ��λ - Ӣ��
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics();

    
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    GameStatus=gameStatus;

	// ע��ʱ����Ӧ����
	registerMouseEvent(MouseEventProcess);      // ���

	// �򿪿���̨���������������Ϣ�����ڵ���
	// InitConsole(); 

}




// ��ť��ʾ����
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // �ؼ��߶�
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/5; // �ؼ����

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
    
	if (button(GenUIID(0), x, y, w, h,  "����")){
		show_more_buttons = ! show_more_buttons;
		PlayAgain=TRUE;
	}
		
	
	if( button(GenUIID(0), x, y-2*h, w, h, "�˳�")){
		exit(-1);
		PlayAgain=FALSE;
	}
	
}

void display()
{
	// ����
	DisplayClear();
			
	// ��ť
	drawButtons();
}
