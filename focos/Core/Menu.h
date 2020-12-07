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
    //byte menu_x;
    //byte menu_y;

    void drawMenu(
        byte menu_x,
        byte menu_y,
        char *title,
        char *option_1,
        char *option_2,
        char *option_3,
        char *option_4
    );

    void printResults(byte menu_x, byte menu_y);

    byte selectOption(byte menu_x, byte menu_y, byte numOptions, byte &ctrMenu);
    void moveSpot(byte menu_x,byte menu_y, byte &ctrMenu, byte count);
    byte isKey(void);

};
