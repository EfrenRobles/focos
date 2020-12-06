#include "StdAfx.h"
#include "Menu.h"

Menu::Menu(void)
{
    menu_x = 25;
    menu_y = 36;

    setupConsole();
}

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
    byte ctrMenu = 40; 
    byte GameOptions;

    drawMenu("MENU        " , "Load room   " , "Solve       " , "About       " , "Quit        ");

    gotoXY(28,ctrMenu);
    cout << "*";

    while(ctrMenu > 0) {
        Sleep(100);

        // Checks witch place the spot is on
        if (selectOption(4, ctrMenu) == K_ENTER) {
            switch (ctrMenu){                    
                case 40:
                    //todo: load a room
                break;

                case 41:
                    //todo: solve the puzzle
                break;

                case 42:
                    //todo: show the about
                break;

                case 43:
                    GameOptions = 0;
                    ctrMenu = 0;
                break;
            }

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
    numOptions = 39 + numOptions;

    if(tempKey == K_UP && ctrMenu > 40) {
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
    gotoXY(28, ctrMenu);
    cout << " ";
    ctrMenu = ctrMenu + count;
    gotoXY(28, ctrMenu);
    cout << "*";
}

/**
 * Function to set the cursor Coord.
 *
 * @param char x
 * @param char y
 * @return void
 */
void Menu::gotoXY(char x, char y)
{
    COORD position = {x, y};
    SetConsoleCursorPosition(wHnd, position);
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