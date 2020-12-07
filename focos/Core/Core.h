#pragma once

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

class Core
{

public:
    typedef unsigned char byte;

    Core(void);
	~Core(void);

protected:
    enum CONSOLE {
        CONSOLE_X   = 120, // value max for the screen
        CONSOLE_Y   = 51   // value max for the screen
    };

    enum ROOM {
        ROOM_GROUND = '0', // value for the ground
        ROOM_WALL   = '1', // value for the wall
        ROOM_BULB   = '2', // value for the bulb
        ROOM_LIGHT  = '3', // value for the bulb's light

        ROOM_X      = 90,  // value max for the room
        ROOM_Y      = 50  // value max for the room
    };

    //Colors on the room
    enum COLORES {
        BLACK	= NULL,
        DBLUE	= BACKGROUND_BLUE,
        BLUE	= DBLUE|BACKGROUND_INTENSITY,
        DGREEN	= BACKGROUND_GREEN,
        GREEN	= DGREEN|BACKGROUND_INTENSITY,
        DRED	= BACKGROUND_RED,
        RED		= DRED|BACKGROUND_INTENSITY,
        DYELLOW	= DRED|DGREEN,
        YELLOW	= DYELLOW|DGREEN|BACKGROUND_INTENSITY,
        DWHITE	= DBLUE|DRED|DGREEN,
        WHITE	= DWHITE|BACKGROUND_INTENSITY,
        DCYAN	= DBLUE|DGREEN,
        CYAN	= DCYAN|BACKGROUND_INTENSITY,
        DPINK	= DBLUE|DRED,
        PINK	= DPINK|BACKGROUND_INTENSITY,
        NOCOLOR	= BACKGROUND_INTENSITY
    };

    // Keypress for keyboard
    enum KEYBOARD {
        K_ESC	= 27,
        K_ENTER	= 13,
        K_UP	= 38,
        K_DOWN	= 40,
    };


    HANDLE wHnd; // Handle to write console.
	HANDLE rHnd; // Handle to read console.

	LPCWSTR console_title;

    char room[ROOM_X][ROOM_Y];
    byte room_x;
	byte room_y;
    byte scale;
    byte spaces_in_darkness;
    byte spaces_with_bulbs;


	void setupConsole(void);
    void copyMatrix(char room_a[ROOM_X][ROOM_Y], char room_b[ROOM_X][ROOM_Y]);

    void gotoXY(char x, char y);

    void doDot(byte x, byte y, COLORES co);
    void paintDot(byte x, byte y, byte w, byte h, byte co);
    void drawRoom(void);
    void resetRoom(void);
    void countSpaceInDarkness(void);

private:
};
