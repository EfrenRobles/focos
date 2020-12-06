#include "StdAfx.h"
#include "Menu.h"

/**
 * The class destruct.
 *
 * @return void
 */
Menu::Menu(void)
{
    menu_x = 90;
    menu_y = 0;

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
byte Menu::menuConsole(void)
{
    // control of menu
    byte ctrMenu = menu_y + 4; 
    byte GameOptions;

    loadLevel("./rooms/demo.txt");
    drawMenu("MENU        " , "Load room   " , "Solve       " , "About       " , "Quit        ");

    gotoXY(menu_x + 3, ctrMenu);
    cout << "*";

    while(ctrMenu > 0) {
        Sleep(100);

        // Checks witch place the spot is on
        if (selectOption(4, ctrMenu) != K_ENTER) {
            continue;
        }

        // Load room
        if (ctrMenu == menu_y + 4) {
            continue;
        }

        // Solve
        if (ctrMenu == menu_y + 5) {
            continue;
        }

        // About
        if (ctrMenu == menu_y + 6) {
            continue;
        }

        // Quit
        if (ctrMenu == menu_y + 7) {
            GameOptions = 0;
            ctrMenu = 0;
            continue;
        }

    }

    return GameOptions;
}

/**
 * Function to draw the menu in the screen.
 *
 * @param char *title
 * @param char *option_1
 * @param char *option_2
 * @param char *option_3
 * @param char *option_4
 * @return void
 */
void Menu::drawMenu(char *title, char *option_1, char *option_2, char *option_3, char *option_4)
{
    gotoXY(menu_x, menu_y); 
    cout << "\311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273";
    gotoXY(menu_x, menu_y + 1);
    cout << "\272    " << title <<"\272";
    gotoXY(menu_x, menu_y + 2);
    cout << "\314\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\271";
    gotoXY(menu_x, menu_y + 3);
    cout << "\272                \272";
    gotoXY(menu_x, menu_y + 4);
    cout << "\272    " << option_1 <<"\272";
    gotoXY(menu_x, menu_y + 5);
    cout << "\272    " << option_2 <<"\272";
    gotoXY(menu_x, menu_y + 6);
    cout << "\272    " << option_3 <<"\272";    
    gotoXY(menu_x, menu_y + 7);
    cout << "\272    " << option_4 <<"\272";    
    gotoXY(menu_x, menu_y + 8);
    cout << "\272                \272";
    gotoXY(menu_x, menu_y + 9);
    cout << "\310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274";
}

/**
 * Function to select an option from  the menu.
 *
 * @param byte numOptions
 * @param byte &ctrMenu
 * @return byte
 */
byte Menu::selectOption(byte numOptions, byte &ctrMenu)
{
    byte tempKey = isKey();
    numOptions = menu_y + 3 + numOptions;

    if(tempKey == K_UP && ctrMenu > menu_y + 4) {
        moveSpot(ctrMenu, -1);
        return tempKey;
    }

    if(tempKey == K_DOWN && ctrMenu < numOptions) {
        moveSpot(ctrMenu, 1);
    }

    return tempKey;
}

/**
 * Function to move the spot in the menu.
 *
 * @param byte &ctrMenu
 * @param byte count
 * @return void
 */
void Menu::moveSpot(byte &ctrMenu, byte count)
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
 * @param byte &ctrMenu
 * @param byte count
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