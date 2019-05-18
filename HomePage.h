/*
    provide a homepage,just a start page
*/

#ifndef static double winwidth, winheight;
#define static double winwidth, winheight; 
#define static int    show_more_buttons = 0; 
#define static int    show_model = 0;
#define static int    show_forerunner = 0;
#define static int    show_color = 0;

static void DisplayClear(void);
/*
    provided in libgraphics.
*/

static void startTimer(int id, int timeinterval);
/*
    provided in libgraphics.
*/

static void display1(void);
/*
    functions that the user displays.
	Return    :void
*/

static void display2(void);
/*
	functions that the user displays.
	Return    :void
*/

static void display3(void);
/*
	functions that the user displays.
	Return    :void
*/

static void MouseEventProcess(int x, int y, int button, int event);
/*
    the user's mouse event response function.
	Return   :void
*/

static void DrawButtons1();
/*
    draw four buttons on the start page.
    Arguments:Four buttons
    Return   :void
*/

static void DrawButtons2();
/*
	draw three buttons on the left to show some settings.
	Arguments:six buttons
	Return   :void
*/

static void DrawButtons3();
/*
	show some instructions.
	Return   :void
*/

static bool HomePage(void);
/*
    show the homepage.
	Return   :bool
*/
#endif
