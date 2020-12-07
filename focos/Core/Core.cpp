#include "StdAfx.h"
#include "Core.h"

/**
 * The class construct.
 *
 * @return void
 */
Core::Core(void)
{
    scale = 3;
    resetRoom();
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
	SMALL_RECT WindowSize = {0, 0, CONSOLE_X - 1, CONSOLE_Y - 1};
	
	// Change the console window size:
	SetConsoleWindowInfo(wHnd, true, &WindowSize);

	// Create a COORD to hold the buffer size:
	COORD BufferSize = {CONSOLE_X, CONSOLE_Y};

	// Change the internal buffer size:
	SetConsoleScreenBufferSize(wHnd, BufferSize);

	// Hide cursor
	CONSOLE_CURSOR_INFO HideCursor;
	HideCursor.bVisible = false;
	HideCursor.dwSize = 1;
	SetConsoleCursorInfo(wHnd, &HideCursor);

	paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);

}

/**
 * Function to set the cursor Coord.
 *
 * @param char x
 * @param char y
 * @return void
 */
void Core::gotoXY(char x, char y)
{
    COORD position = {x, y};
    SetConsoleCursorPosition(wHnd, position);
}

/**
 * Function to set a dot in the screen with scale.
 *
 * @param byte x
 * @param byte y
 * @param COLORES co
 * @return void
 */
void Core::doDot(byte x, byte y, COLORES co)
{
    //Just a dot in scale
	x = (x + 1) * scale;
	y = (y + 1) * scale;
	paintDot(x, y, x + scale -1, y + scale -1, co);
}

/**
 * Function to paint on the screen dots, set a line and their limits to draw.
 *
 * @param byte x
 * @param byte y
 * @param byte w
 * @param byte h
 * @param COLORES co
 * @return void
 */
void Core::paintDot(byte x, byte y, byte w, byte h, byte co)
{
	SMALL_RECT srctScrollRect = {x, y, w, h};

	// set the border color of the line
	COORD coordDest = {w, h + 1}; //x, y 

	// Fill the row with a color. 
	CHAR_INFO chiFill;
	chiFill.Char.UnicodeChar = ' ';
	chiFill.Attributes = co;

	// Scroll up one line or dot
	ScrollConsoleScreenBuffer(wHnd, &srctScrollRect, &srctScrollRect, coordDest, &chiFill);
}

/**
 * Function to draw the new room in screen.
 *
 * @return void
 */
void Core::drawRoom(void)
{
    Sleep(500);
	byte w = (room_x + 1) * scale;
	byte h = (room_y + 2) * scale;
	paintDot(0, 0, w + scale -1, h + scale -1, DBLUE);

    for (byte y = 0; y <= room_y; y++) { // if that cord is the ground
        for (byte x = 0; x < room_x; x++) {

            switch (room[x][y]) {
                case ROOM_WALL:
                    doDot(x, y, DGREEN);
                break;

                case ROOM_BULB:
                    doDot(x, y, DYELLOW);
                break;

                case ROOM_LIGHT:
                    doDot(x, y, DWHITE);
                break;

                case DRED:
                    doDot(x, y, DRED);
                break;

                default:
                    doDot(x, y, BLACK);
                break;
            }
        }
    }
    countSpaceInDarkness();
}

/**
 * Function to reset the room.
 *
 * @return void
 */
void Core::resetRoom(void)
{
    for (byte y = 0; y <= ROOM_Y; y ++) {
        for (byte x = 0; x < ROOM_X; x ++) {
            room[x][y] = DGREEN;
        }
    }
}

/**
 * Function to copy the room.
 *
 * @param char room_a[ROOM_X][ROOM_Y]
 * @param char room_b[ROOM_X][ROOM_Y]
 * @return void
 */
void Core::copyMatrix(char room_a[ROOM_X][ROOM_Y], char room_b[ROOM_X][ROOM_Y])
{
    for (byte y = 0; y <= ROOM_Y; y ++) {
        for (byte x = 0; x < ROOM_X; x ++) {
            room_b[x][y] = room_a[x][y];
        }
    }
}

/**
 * Function to copy the room.
 *
 * @param char room_a[ROOM_X][ROOM_Y]
 * @param char room_b[ROOM_X][ROOM_Y]
 * @return void
 */
void Core::countSpaceInDarkness(void)
{
    spaces_in_darkness = 0;
    spaces_with_bulbs = 0;

    for (byte x = 0; x < room_x; x ++) {
        for (byte y = 0; y <= room_y; y ++) {
            if (room[x][y] == ROOM_GROUND) {
                spaces_in_darkness ++;
            }

            if (room[x][y] == ROOM_BULB) {
                spaces_with_bulbs ++;
            }
            
        }
    }
}