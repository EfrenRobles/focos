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
    w_hnd = GetStdHandle(STD_OUTPUT_HANDLE);
    r_hnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(r_hnd, ENABLE_PROCESSED_INPUT);

    // Change the window title:
    SetConsoleTitle(console_title);

    // Set up the required window size:
    SMALL_RECT window_size = {0, 0, CONSOLE_X - 1, CONSOLE_Y - 1};
    
    // Change the console window size:
    SetConsoleWindowInfo(w_hnd, true, &window_size);

    // Create a COORD to hold the buffer size:
    COORD buffer_size = {CONSOLE_X, CONSOLE_Y};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(w_hnd, buffer_size);

    // Hide cursor
    CONSOLE_CURSOR_INFO hide_cursor;
    hide_cursor.bVisible = false;
    hide_cursor.dwSize = 1;
    SetConsoleCursorInfo(w_hnd, &hide_cursor);

    paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);
}

/**
 * Function to get the input from user using the keyboard.
 *
 * @return byte
 */
byte Core::isKey(void)
{
	DWORD events;
    DWORD events_read = 0;

    // events that can be read from the console
    GetNumberOfConsoleInputEvents(r_hnd, &events);

    if (events != 0) {
		INPUT_RECORD *in_rec = new INPUT_RECORD[events];
		ReadConsoleInput(r_hnd, in_rec, events, &events_read);

        if (in_rec[0].EventType == KEY_EVENT){
            if(in_rec[0].Event.KeyEvent.bKeyDown == 1) {
				events_read = in_rec[0].Event.KeyEvent.wVirtualKeyCode;
            }
		}

        delete[] in_rec;
	}
    
    FlushConsoleInputBuffer(r_hnd);
	return (byte)events_read;
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
    SetConsoleCursorPosition(w_hnd, position);
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
 * @param byte co
 * @return void
 */
void Core::paintDot(byte x, byte y, byte w, byte h, byte co)
{
	SMALL_RECT srct_scroll_rect = {x, y, w, h};

	// set the border color of the line
	COORD coord_dest = {w, h + 1}; 

	// Fill the row with a color. 
	CHAR_INFO chr_info;
	chr_info.Char.UnicodeChar = ' ';
	chr_info.Attributes = co;

	// Scroll up one line or dot
	ScrollConsoleScreenBuffer(w_hnd, &srct_scroll_rect, &srct_scroll_rect, coord_dest, &chr_info);
}

/**
 * Function to draw the new room in screen.
 *
 * @return void
 */
void Core::drawRoom(void)
{
    autoScale();
    Sleep(5);
	byte w = (room_x + 1) * scale;
	byte h = (room_y + 1) * scale;
	paintDot(0, 0, w + scale -1, h + scale -1, DBLUE);

    for (byte y = 0; y < room_y; y ++) { // if that cord is the ground
        for (byte x = 0; x < room_x; x ++) {

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
 * Function to set the autoscale the room in the screen.
 *
 * @return void
 */
void Core::autoScale(void)
{
    if (room_x < 31 && room_y < 16) {
        scale = 3;
        return;
    }

    if (room_x < 44 && room_y < 25) {
        scale = 2;
        return;
    }

    if (room_x < 90 && room_y < 50) {
        scale = 1;
        return;
    }

    MessageBox(0, TEXT("The room is to big..."), TEXT("Error"), MB_ICONERROR);
    scale = 1;

}

/**
 * Function to reset the room.
 *
 * @return void
 */
void Core::resetRoom(void)
{
    for (byte y = 0; y < ROOM_Y; y ++) {
        for (byte x = 0; x < ROOM_X; x ++) {
            room[x][y] = DGREEN;
        }
    }
}

/**
 * Function to make a copy of the room
 *
 * @param char room_a[ROOM_X][ROOM_Y]
 * @param char room_b[ROOM_X][ROOM_Y]
 * @return void
 */
void Core::copyMatrix(char room_a[ROOM_X][ROOM_Y], char room_b[ROOM_X][ROOM_Y])
{
    for (byte y = 0; y < ROOM_Y; y ++) {
        for (byte x = 0; x < ROOM_X; x ++) {
            room_b[x][y] = room_a[x][y];
        }
    }
}

/**
 * Function to count the bulbs and dark place numbers.
 *
 * @return void
 */
void Core::countSpaceInDarkness(void)
{
    spaces_in_darkness = 0;
    spaces_with_bulbs = 0;

    for (byte x = 0; x < room_x; x ++) {
        for (byte y = 0; y < room_y; y ++) {
            if (room[x][y] == ROOM_GROUND) {
                spaces_in_darkness ++;
            }

            if (room[x][y] == ROOM_BULB) {
                spaces_with_bulbs ++;
            }
            
        }
    }
}