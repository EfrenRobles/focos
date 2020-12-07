#include "StdAfx.h"
#include "Menu.h"

/**
 * The class destruct.
 *
 * @return void
 */
Menu::Menu(void)
{
    setupConsole();
}

/**
 * Function to setup the screen.
 *
 * @return void
 */
Menu::~Menu(void)
{
}

/**
 * Function to show the main menu.
 *
 * @return byte
 */
void Menu::menuConsole(void)
{
    byte menu_x = 90;
    byte menu_y = 0;

    // control of menu
    byte ctrMenu = menu_y + 4;

    drawMenu(menu_x, menu_y, "MENU        " , "Load room   " , "Solve       " , "About       " , "Quit        ");
    gotoXY(menu_x + 3, ctrMenu);
    cout << "*";

    loadLevel("./rooms/demo.txt");
    printResults(menu_x, menu_y);

    while(ctrMenu > 0) {
        Sleep(50);

        // Checks witch place the spot is on
        if (selectOption(menu_x, menu_y, 4, ctrMenu) != K_ENTER) {
            continue;
        }

        // Load room
        if (ctrMenu == menu_y + 4) {
            loadLevel("./rooms/demoe.txt");
            continue;
        }

        // Solve
        if (ctrMenu == menu_y + 5) {
            loadLevel("./rooms/demoe.txt");
            resolve_step_1();
            printResults(menu_x, menu_y);
            continue;
        }

        // About
        if (ctrMenu == menu_y + 6) {
            continue;
        }

        // Quit
        if (ctrMenu == menu_y + 7) {
            ctrMenu = 0;
        }

    }
}

/**
 * Function to draw the menu in the screen.
 *
 * @param byte menu_x
 * @param byte menu_y
 * @param char *title
 * @param char *option_1
 * @param char *option_2
 * @param char *option_3
 * @param char *option_4
 * @return void
 */
void Menu::drawMenu(
    byte menu_x,
    byte menu_y,
    char *title,
    char *option_1,
    char *option_2,
    char *option_3,
    char *option_4
) {
    gotoXY(menu_x, menu_y); 
    cout << "\311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273";
    gotoXY(menu_x, menu_y + 1);
    cout << "\272    " << title << "\272";
    gotoXY(menu_x, menu_y + 2);
    cout << "\314\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\271";
    gotoXY(menu_x, menu_y + 3);
    cout << "\272                \272";
    gotoXY(menu_x, menu_y + 4);
    cout << "\272    " << option_1 << "\272";
    gotoXY(menu_x, menu_y + 5);
    cout << "\272    " << option_2 << "\272";
    gotoXY(menu_x, menu_y + 6);
    cout << "\272    " << option_3 << "\272";    
    gotoXY(menu_x, menu_y + 7);
    cout << "\272    " << option_4 << "\272";
    gotoXY(menu_x, menu_y + 8);
    cout << "\272                \272";
    gotoXY(menu_x, menu_y + 9);
    cout << "\310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274";
}

/**
 * Function to print the puzzle result.
 *
 * @param byte menu_x
 * @param byte menu_y
 * @return void
 */
void Menu::printResults(byte menu_x, byte menu_y)
{
    drawMenu(menu_x, menu_y + 10, "RESULT      " , "Total Bulbs " , "            ", "Total Dark  " , "            ");

    char buffer_bulbs[12];
    _itoa_s(spaces_with_bulbs, buffer_bulbs, 10);

    char buffer_dark[12];
    _itoa_s(spaces_in_darkness, buffer_dark, 10);

    gotoXY(menu_x + 5, menu_y + 15);
    cout << buffer_bulbs;
    gotoXY(menu_x + 5, menu_y + 17);
    cout << buffer_dark;
}

/**
 * Function to select an option from  the menu.
 *
 * @param byte menu_x
 * @param byte menu_y
 * @param byte numOptions
 * @param byte &ctrMenu
 * @return byte
 */
byte Menu::selectOption(byte menu_x, byte menu_y, byte numOptions, byte &ctrMenu)
{
    byte tempKey = isKey();
    numOptions = menu_y + 3 + numOptions;

    if(tempKey == K_UP && ctrMenu > menu_y + 4) {
        moveSpot(menu_x, menu_y, ctrMenu, -1);
        return tempKey;
    }

    if(tempKey == K_DOWN && ctrMenu < numOptions) {
        moveSpot(menu_x, menu_y, ctrMenu, 1);
    }

    return tempKey;
}

/**
 * Function to move the spot in the menu.
 *
 * @param byte menu_x
 * @param byte menu_y
 * @param byte &ctrMenu
 * @param byte count
 * @return void
 */
void Menu::moveSpot(byte menu_x,byte menu_y, byte &ctrMenu, byte count)
{
    gotoXY(menu_x + 3, ctrMenu);
    cout << " ";
    ctrMenu = ctrMenu + count;
    gotoXY(menu_x + 3, ctrMenu);
    cout << "*";
}

/**
 * Function to get the input from user using the keyboard.
 *
 * @return byte
 */
byte Menu::isKey(void)
{
	DWORD Events;
    DWORD EventsRead = 0;

    // Events that can be read from the console
    GetNumberOfConsoleInputEvents(rHnd, &Events);

    if (Events != 0) {
		INPUT_RECORD *InRec = new INPUT_RECORD[Events];
		ReadConsoleInput(rHnd, InRec, Events, &EventsRead);

        if (InRec[0].EventType == KEY_EVENT){
            if(InRec[0].Event.KeyEvent.bKeyDown == 1) {
				EventsRead = InRec[0].Event.KeyEvent.wVirtualKeyCode;
            }
		}

        delete[] InRec;
	}
    
    FlushConsoleInputBuffer(rHnd);
	return (byte)EventsRead;
}