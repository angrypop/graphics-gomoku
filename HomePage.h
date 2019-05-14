/*
    provide a homepage,just a start page
*/

#ifdef static double winwidth, winheight; 
#define static int    show_more_buttons = 0; 

void DisplayClear(void);
/*
    provided in libgraphics.
*/

void startTimer(int id, int timeinterval);
/*
    provided in libgraphics.
*/

void display(void);
/*
    functions that the user displays.
	Return    :void
*/
void MouseEventProcess(int x, int y, int button, int event);
/*
    the user's mouse event response function.
	Return   :void
*/

void DrawButtons();
/*
    draw four buttons on the start page.
    Arguments:Four buttons
    Return   :void
*/

#endif
