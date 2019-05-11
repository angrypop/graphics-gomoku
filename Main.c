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
#define QUIT -1
#define UNKNOWN 0
#define WIN 1
#define LOSE 2
#define SUREENDER 3

void Main()
{
	// The loop is to deal with 'playing again '
	while (TRUE)
	{
		int GameStatus = UNKNOWN;
		bool PlayAgain = FALSE;

		//  HomePage function loads the home page
		// if the user presses 'New Game' or 'Load Game'
		// this function initializes a new game or loads existing game data
		// and initializes the default setting of the game
		// if the user presses the 'Setting', a new page should be painted to facilitates the changes
		// and the function returns QUIT iff the user presses 'Quit Game'
		// otherwise returns UNKNOWN
		GameStatus = HomePage();

		// GamePage function loads the game page
		// and return the final game status of the game
		if (GameStatus != QUIT)
			GameStatus = GamePage();

		// The EndGamePage function shows End Game Pagevaries based on different game statuses
		// and returns TRUE if the user chooses to play again 
		// returns FALSE otherwise
		if (GameStatus == QUIT)
			QuitGamePage();
		else
			PlayAgain = EndGamePage(GameStatus);

		if (PlayAgain == FALSE)
			break;

	}
	
}