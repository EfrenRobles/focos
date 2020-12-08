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
    byte ctr_menu = MENU_Y + 4;

    printMainMenu(ctr_menu);
    loadLevel("./rooms/demo.txt");
    printResults();

    while(ctr_menu > 0) {
        Sleep(50);

        // Checks witch place the spot is on
        if (selectOption(4, ctr_menu) != K_ENTER) {
            continue;
        }

        // Load room
        if (ctr_menu == MENU_Y + 4) {
            menuLoadFile();
            continue;
        }

        // Solve
        if (ctr_menu == MENU_Y + 5) {
            solvePuzzle();
            printResults();
            continue;
        }

        // About
        if (ctr_menu == MENU_Y + 6) {
            printAbout();
            continue;
        }

        // Quit
        if (ctr_menu == MENU_Y + 7) {
            ctr_menu = 0;
        }
    }
}

/**
 * Function to show and handle the load file menu.
 *
 * @return byte
 */
void Menu::menuLoadFile(void)
{
    byte ctr_menu = MENU_Y + 4;

    drawMenu(MENU_X, MENU_Y, "LOAD FILE   " , "Slot 1      " , "Slot 2      " , "Slot 3      " , "Slot 4      ");
    gotoXY(MENU_X + 3, ctr_menu);
    cout << "*";
    
    while(ctr_menu > 0) {
        Sleep(50);

        // Checks witch place the spot is on
        byte key_press = selectOption(4, ctr_menu);

        if (key_press == K_ESC) {
            ctr_menu = MENU_Y + 4;
            printMainMenu(ctr_menu);
            return;
        }

        if (key_press != K_ENTER) {
            continue;
        }

        // Load slot 1
        if (ctr_menu == MENU_Y + 4) {
	        paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);
            loadLevel("./rooms/slot_1.txt");
            ctr_menu = 0;
        }

        // Load slot 2
        if (ctr_menu == MENU_Y + 5) {
	        paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);
            loadLevel("./rooms/slot_2.txt");
            ctr_menu = 0;
        }

        // Load slot 3
        if (ctr_menu == MENU_Y + 6) {
	        paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);
            loadLevel("./rooms/slot_3.txt");
            ctr_menu = 0;
        }

        // Load slot 4
        if (ctr_menu == MENU_Y + 7) {
	        paintDot(0, 0, CONSOLE_X - 1, CONSOLE_Y - 1, BLACK);
            loadLevel("./rooms/slot_4.txt");
            ctr_menu = 0;
        }
    }

    ctr_menu = MENU_Y + 4;
    printMainMenu(ctr_menu);
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
 * Function to print the main menu.
 *
 * @param byte &ctr_menu
 * @return void
 */
void Menu::printMainMenu(byte &ctr_menu)
{
    drawMenu(MENU_X, MENU_Y, "MENU        " , "Load room   " , "Solve       " , "About       " , "Quit        ");
    gotoXY(MENU_X + 3, ctr_menu);
    cout << "*";
}

/**
 * Function to print the puzzle result.
 *
 * @return void
 */
void Menu::printResults(void)
{
    drawMenu(MENU_X, MENU_Y + 10, "RESULT      " , "Total Bulbs " , "            ", "Total Dark  " , "            ");

    char buffer_bulbs[12];
    _itoa_s(spaces_with_bulbs, buffer_bulbs, 10);

    char buffer_dark[12];
    _itoa_s(spaces_in_darkness, buffer_dark, 10);

    gotoXY(MENU_X + 5, MENU_Y + 15);
    cout << buffer_bulbs;
    gotoXY(MENU_X + 5, MENU_Y + 17);
    cout << buffer_dark;
}

/**
 * Function to print the puzzle result.
 *
 * @return void
 */
void Menu::printAbout(void)
{
    byte menu_y = 23;

    gotoXY(MENU_X, menu_y++);
    cout << "\311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 Distribucion de focos    \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 Beta v0.1.445            \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272                          \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 Por:                     \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 Efren Robles             \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272                          \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 email:                   \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\272 efren_robles@hotmail.com \272";
    gotoXY(MENU_X, menu_y++);
    cout << "\310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274";
}

/**
 * Function to select an option from  the menu.
 *
 * @param byte numOptions
 * @param byte &ctr_menu
 * @return byte
 */
byte Menu::selectOption(byte numOptions, byte &ctr_menu)
{
    byte temp_key = isKey();
    numOptions = MENU_Y + 3 + numOptions;

    if(temp_key == K_UP && ctr_menu > MENU_Y + 4) {
        moveSpot(MENU_X, MENU_Y, ctr_menu, -1);
        return temp_key;
    }

    if(temp_key == K_DOWN && ctr_menu < numOptions) {
        moveSpot(MENU_X, MENU_Y, ctr_menu, 1);
    }

    return temp_key;
}

/**
 * Function to move the spot in the menu.
 *
 * @param byte menu_x
 * @param byte menu_y
 * @param byte &ctr_menu
 * @param byte count
 * @return void
 */
void Menu::moveSpot(byte menu_x, byte menu_y, byte &ctr_menu, byte count)
{
    gotoXY(menu_x + 3, ctr_menu);
    cout << " ";
    ctr_menu = ctr_menu + count;
    gotoXY(menu_x + 3, ctr_menu);
    cout << "*";
}