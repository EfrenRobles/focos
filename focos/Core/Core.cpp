#include "StdAfx.h"
#include "Core.h"

/**
 * The class construct.
 *
 * @return void
 */
Core::Core(void)
{
	console_x = 120;
	console_y = 50;
	console_title = TEXT("Foco App");
}

/**
 * The class destruct.
 *
 * @return void
 */
Core::~Core(void)
{
}

/**
 * Function to setup the screen.
 *
 * @return void
 */
void Core::setupConsole()
{
	// Set up the random number
	srand((unsigned)time(NULL));

	// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(rHnd, ENABLE_PROCESSED_INPUT);

	// Change the window title:
	SetConsoleTitle(console_title);

	// Set up the required window size:
	SMALL_RECT WindowSize = {0, 0, console_x - 1, console_y - 1};
	
	// Change the console window size:
	SetConsoleWindowInfo(wHnd, true, &WindowSize);

	// Create a COORD to hold the buffer size:
	COORD BufferSize = {console_x, console_y};

	// Change the internal buffer size:
	SetConsoleScreenBufferSize(wHnd, BufferSize);

	// Hide cursor
	CONSOLE_CURSOR_INFO HideCursor;
	HideCursor.bVisible = false;
	HideCursor.dwSize = 1;
	SetConsoleCursorInfo(wHnd, &HideCursor);
}
