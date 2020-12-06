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
	HANDLE wHnd;																			// Handle to write console.
	HANDLE rHnd;																			// Handle to read console.

    char console_x;
	char console_y;
	LPCWSTR console_title;

	void setupConsole(void);

private:

    //=============================== Valors for keypress ============================================================

    #define K_ESC   27
    #define K_ENTER	13
    #define K_UP	38
    #define K_DOWN	40

};
