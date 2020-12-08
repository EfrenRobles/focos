#pragma once
#include "File.h"

class Menu : public File
{

public:
    Menu(void);
    ~Menu(void);

protected:
    void menuConsole(void);

private:

    enum MENU {
        MENU_X = 92,
        MENU_Y = 0,
    };

    void drawMenu(
        byte menu_x,
        byte menu_y,
        char *title,
        char *option_1,
        char *option_2,
        char *option_3,
        char *option_4
    );

    void menuLoadFile(void);

    void printMainMenu(byte &ctr_menu);
    void printResults();
    void printAbout(void);

    byte selectOption(byte numOptions, byte &ctrMenu);
    void moveSpot(byte menu_x,byte menu_y, byte &ctrMenu, byte count);

};