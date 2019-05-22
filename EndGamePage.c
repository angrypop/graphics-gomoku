/*
    provide a endgamepage,just a end page
*/

#ifndef END_GAME_PAGE_C
#define END_GAME_PAGE_C
#include "EndGamePage.h"

// User main program entry
// Initialize once
 bool EndGamePage (int gameStatus) 
{
	// Initialization window and graphics system
	//SetWindowSize(10, 10); // unit - inch
	//SetWindowSize(20, 10);
	//SetWindowSize(10, 20);  // If the screen size is not enough ,scale it down
    InitGraphics();

    
	// get window size
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    GameStatus=gameStatus;

	// register mouse event function
	registerMouseEvent(MouseEventProcess);      // mouse

	// open the console for easy output of variable information and debug
	// InitConsole(); 

}


// mouse event function
 void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI get mouse
	display(); // refresh diaplay
}

//Buttons demonstration program
 void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // conrtol height
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/5; // conrtol width

	MovePen(winwidth/3,winheight/3*2);
	switch (GameStatus){
	 case GAME_WIN:
         DrawTextString("you are  WINNING!");
         break;
	 case GAME_LOSE:
	     DrawTextString("you are  LOSING!");
	     break;
	 case GAME_SUREENDER: 
	     DrawTextString("you are  SUREENDER!"); 
	     break;
	 }
    
	if (button(GenUIID(0), x, y, w, h,  "复盘")){
		show_more_buttons = ! show_more_buttons;
		HomePage();
	}
		

	if( button(GenUIID(0), x, y-2*h, w, h, "退出")){
		exit(-1);
	}
	
}

// mouse event function
 void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI get mouse
	display(); // refresh diaplay
}

 void display()
{
	// clearscreen
	DisplayClear();
			
	// button
	drawButtons();
}

#endif
